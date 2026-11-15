#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DB="$SCRIPT_DIR/src/database/local.db"
OUT="$SCRIPT_DIR/tables"
TABLE="${1:?usage: $0 <table>}"

[[ "$TABLE" =~ ^[A-Za-z_][A-Za-z0-9_]*$ ]] \
    || { echo "invalid table name: $TABLE" >&2; exit 1; }

[[ -f "$DB" ]] || { echo "Error: database not found: $DB" >&2; exit 1; }
python3 -c 'import yaml' 2>/dev/null \
    || { echo "install python-yaml: sudo pacman -S python-yaml" >&2; exit 1; }

mkdir -p "$OUT"

if ! sqlite3 "$DB" "SELECT 1 FROM \"$TABLE\" LIMIT 1;" >/dev/null 2>&1; then
    echo "Error: no such table: $TABLE" >&2
    exit 1
fi

# Build "key", value pairs.
# Text columns go through json_quote() so newlines/tabs/quotes are escaped.
# Numeric columns are emitted as-is to keep their JSON type.
build_cols() {
    sqlite3 "$DB" "PRAGMA table_info('$1');" | awk -F'|' '
        $3 ~ /CHAR|TEXT|CLOB/ { printf "'\''%s'\'', json_quote(\"%s\"), ", $2, $2; next }
        { printf "'\''%s'\'', \"%s\", ", $2, $2 }
    ' | sed 's/, $//'
}

parent_cols=$(build_cols "$TABLE")

# Find direct children (tables whose FK points at $TABLE) and build aggregation
children_parts=""
for child in $(sqlite3 "$DB" \
    "SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';"); do
    while IFS='|' read -r _ _ ptab from to _ _ _; do
        [[ "$ptab" == "$TABLE" ]] || continue
        child_cols=$(build_cols "$child")
        children_parts+=",
        '${child}s', coalesce(
            json((SELECT json_group_array(json_object(${child_cols}))
                  FROM \"$child\" c WHERE c.\"$from\" = p.\"$to\")),
            json('[]')
        )"
    done < <(sqlite3 -separator '|' "$DB" "PRAGMA foreign_key_list('$child');")
done

sql="SELECT json_group_array(json_object(${parent_cols}${children_parts}))
     FROM \"$TABLE\" p;"

echo "$sql" >&2   # debug: see what's generated

# Raw output — no .mode json (which would re-encode the JSON string)
sqlite3 -noheader "$DB" "$sql" > "$OUT/$TABLE.json"

# CSV: separate query with its own mode
sqlite3 -header -csv "$DB" "SELECT * FROM \"$TABLE\";" > "$OUT/$TABLE.csv"

# Convert JSON -> YAML and XML
python3 - "$OUT/$TABLE.json" "$OUT/$TABLE.yaml" "$OUT/$TABLE.xml" <<'PY'
import json, sys, yaml
import xml.etree.ElementTree as ET

src, yml, xml = sys.argv[1:4]

with open(src, "rb") as f:
    raw = f.read()
try:
    text = raw.decode("utf-8")
except UnicodeDecodeError:
    text = raw.decode("utf-8", errors="replace")

data = json.loads(text)

with open(yml, "w") as f:
    yaml.safe_dump(data, f, sort_keys=False, allow_unicode=True,
                   default_flow_style=False, width=120)

def build(el, obj):
    for k, v in obj.items():
        tag = k[:-1] if k.endswith("s") else k
        if isinstance(v, list):
            lst = ET.SubElement(el, k)
            for item in v:
                if item is None:
                    continue
                if isinstance(item, dict):
                    build(ET.SubElement(lst, tag), item)
                else:
                    ET.SubElement(lst, tag).text = str(item)
        else:
            ET.SubElement(el, k).text = "" if v is None else str(v)

root = ET.Element("rows")
for item in data:
    build(ET.SubElement(root, "row"), item)
tree = ET.ElementTree(root)
ET.indent(tree, space="  ")
tree.write(xml, encoding="utf-8", xml_declaration=True)
PY

echo "Export complete:"
ls -l "$OUT"
