#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DB="$SCRIPT_DIR/src/database/local.db"
OUT="$SCRIPT_DIR/tables"

mkdir -p "$OUT"

if [[ ! -f "$DB" ]]; then
    echo "Error: database not found: $DB" >&2
    exit 1
fi

if ! sqlite3 "$DB" "SELECT * FROM "$1";" >/dev/null 2>&1; then
    echo "Error: no such table" >&2
    exit 1
fi

# Export JSON and CSV with sqlite3
sqlite3 "$DB" ".mode json" ".once $OUT/"$1".json" "SELECT * FROM "$1";"
sqlite3 "$DB" ".mode csv"  ".once $OUT/"$1".csv"  "SELECT * FROM "$1";"

# Convert JSON -> YAML and XML with Python
python3 - "$OUT/"$1".json" "$OUT/"$1".yaml" "$OUT/"$1".xml" <<'PY'
import json, sys, yaml
import xml.etree.ElementTree as ET

src, yml, xml = sys.argv[1:4]
data = json.load(open(src))

yaml.safe_dump(data, open(yml, "w"), sort_keys=False, allow_unicode=True)

root = ET.Element("rows")
for item in data:
    row = ET.SubElement(root, "row")
    for k, v in item.items():
        ET.SubElement(row, k).text = "" if v is None else str(v)
ET.ElementTree(root).write(xml, encoding="utf-8", xml_declaration=True)
PY

echo "Export complete:"
ls -l "$OUT"
