#include "../rentrack.h"

enum ERR add_premise_repo(sqlite3* db, char * address, char* area, char* comment){
    const char *sql =
    "INSERT INTO premise "
    "(Address, Area, Comment, StatusID) "
    "VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc == SQLITE_OK) {

	sqlite3_bind_text(stmt, 1, address, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, area, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, comment, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 4, 2);

	rc = sqlite3_step(stmt);
    }

    if (rc != SQLITE_DONE) {
	fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	fflush(stderr);
    }

    sqlite3_finalize(stmt);
    return OK;
}

