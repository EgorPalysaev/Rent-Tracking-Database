#include "../rentrack.h"
sqlite3 *setupDB(){
    char *errMsg = NULL;
    sqlite3 *db = NULL;
    int result = sqlite3_open("database/local.db", &db);
    if (result != SQLITE_OK){
	fprintf(stderr, "Can not open database: %s\n", db ? sqlite3_errmsg(db) : sqlite3_errstr(result));
	fflush(stderr);
        if (db != NULL) sqlite3_close(db);
	return NULL;
    }
    int rc = sqlite3_exec(db, "PRAGMA FOREIGN_KEYS = ON;", 0, 0, &errMsg);
    if (rc != SQLITE_OK){
	fprintf(stderr, "Can not set PRAGMA FOREIGN_KEYS %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
	fflush(stderr);
	sqlite3_free(errMsg);
	sqlite3_close(db);
	return NULL;
    }
    return db;
}
