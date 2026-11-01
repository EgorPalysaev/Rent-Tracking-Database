#include "../rentrack.h"


enum ERR show_all_data(sqlite3 *db, const char *table, char key, unsigned int user_id){
    
    char sql[128];

/* USER YOURSELF */

    if (strcmp(table, "user_yourself") == 0){
	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, "SELECT * FROM user_name WHERE UserID = ? LIMIT 1;", -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    return ERROR;
	}
	if (sqlite3_bind_int(stmt, 1, user_id) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    sqlite3_finalize(stmt);
	    return ERROR;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW){
	    printf("┏━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┓\n");
	    printf("┃ %-8s┃  %-10s┃  %-16s┃  %-16s┃", "UserID", "Role", "login", "password");
	    fflush(stdout);
	    printf("  %-18s┃  %-16s┃  %-16s┃\n", "Name", "Surname", "Patronymic");
	    fflush(stdout);
	    printf("┣━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━┫\n");
	    printf("┃ %-6d  ┃  %-10s┃  %-16s┃  %-16s┃", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1) == 1 ? "Tenant" : "Landlord", (char *)sqlite3_column_text(stmt, 2), (char *)sqlite3_column_text(stmt, 3));
	    fflush(stdout);
	    printf("  %-18s┃  %-16s┃  %-16s┃\n", (char *)sqlite3_column_text(stmt, 4), (char *)sqlite3_column_text(stmt, 5), (char *)sqlite3_column_text(stmt, 6));
	    fflush(stdout);
	    printf("┗━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┛\n");
	    fflush(stdout);
	    sqlite3_finalize(stmt);
	    return OK;
	    }
	else if (sqlite3_step(stmt) == SQLITE_DONE){
	    sqlite3_finalize(stmt);
	    printf("ID does not exist\n");
	    fflush(stdout);
	    return ERROR;
	}
	else {
	    fprintf(stderr, "ERROR: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    sqlite3_finalize(stmt);
	    return ERROR;
	}
    }

/* USER_NAME */
    
    if (strcmp(table, "user_name") == 0){
	snprintf(sql, sizeof sql, "SELECT * FROM \"%s\";", table);

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    return ERROR;
	}

	printf("┏━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┓\n");
	    fflush(stdout);
	printf("┃ %-8s┃  %-10s┃  %-16s┃  %-16s┃", "UserID", "Role", "login", "password");
	    fflush(stdout);
	printf("  %-18s┃  %-16s┃  %-16s┃\n", "Name", "Surname", "Patronymic");
	    fflush(stdout);
	while (sqlite3_step(stmt) == SQLITE_ROW){
	    printf("┣━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━┫\n");
	    fflush(stdout);
	    printf("┃ %-6d  ┃  %-10s┃  %-16s┃  %-16s┃", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1) == 1 ? "Tenant" : "Landlord", (char *)sqlite3_column_text(stmt, 2), (char *)sqlite3_column_text(stmt, 3));
	    fflush(stdout);
	    printf("  %-18s┃  %-16s┃  %-16s┃\n", (char *)sqlite3_column_text(stmt, 4), (char *)sqlite3_column_text(stmt, 5), (char *)sqlite3_column_text(stmt, 6));
	    fflush(stdout);
	}
	printf("┗━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┛\n");
	fflush(stdout);
	sqlite3_finalize(stmt);
	return OK;
    }

/* PREMISE */

    else if (strcmp(table, "premise") == 0){
	if (key == 0) snprintf(sql, sizeof sql, "SELECT * FROM \"%s\";", table);
	else if (key == 1) snprintf(sql, sizeof sql, "SELECT * FROM \"%s\" WHERE \"StatusID\" = 1;", table);

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stdout);
	    return ERROR;
	}
	char links_c[32] = "Comment";
	char links_a[32] = "Address";
	const char *const Status_array[] = {"Active", "Inactive", "In rent"};
	printf("┏━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n");
	fflush(stdout);
	printf("┃ %-10s┃  %-48s┃  %-16s┃  %-16s┃  %-18s┃\n", "PremiseID", "Address", "Area", "Comment", "Status");
	fflush(stdout);
	while (sqlite3_step(stmt) == SQLITE_ROW){
	    printf("┣━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
	    fflush(stdout);
	    printf("┃ %-8d  ┃  %-48s┃  %-16d┃  %-16s┃  %-18s┃\n", sqlite3_column_int(stmt, 0), strlen((char *)sqlite3_column_text(stmt, 1)) < 46 ? (char *)sqlite3_column_text(stmt, 1) : strcat(links_a, decimal_to_string(sqlite3_column_int(stmt, 0))), sqlite3_column_int(stmt, 2), strcmp((char *)sqlite3_column_text(stmt, 3), "NONE") ? strcat(links_c, decimal_to_string(sqlite3_column_int(stmt, 0))) : "NONE", Status_array[sqlite3_column_int(stmt, 4)-1]);
	    fflush(stdout);
	    fill_zero_for_links(links_a);
	    fill_zero_for_links(links_c);
	}
	printf("┗━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n");
	fflush(stdout);
	sqlite3_finalize(stmt);
	printf("Show comment and address? (y)es, (n)o  ");
	fflush(stdout);
	switch(choice()){
	    case 'Y': case 'y': goto COMMENT_ADDRESS;
	    case 'n': case 'N': default: printf("\nDon't show comment and address\n"); fflush(stdout);
	}
	return OK;
    }

/* COMMENT AND ADDRESS */
    else if (strcmp(table, "comment") == 0){
	COMMENT_ADDRESS:
	snprintf(sql, sizeof sql, "SELECT * FROM premise WHERE PremiseID = ?;");

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    return ERROR;
	}
	unsigned int premise_id = 0;
	printf("\nEnter a premise ID to view comment and address: ");
	fflush(stdout);
	if (scanf("%d", &premise_id) != 1){
	    if (feof(stdin)){
		printf("EOF reached");
		fflush(stdout);
		exit(1);
	    }
	    printf("Error corupted while entering the premise ID");
	    fflush(stdout);
	    return ERROR;
	} else {
	    int temp;
	    while((temp = getchar()) != '\n' && temp != EOF)
		;
	}
	sqlite3_bind_int(stmt, 1, premise_id);
	if (sqlite3_step(stmt) == SQLITE_ROW) printf("Address:\n%s\nComment:\n%s\n", sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 3));
	fflush(stdout);
	sqlite3_finalize(stmt);
	return OK;
    }
/* ALL USER RENT */

    else if (strcmp(table, "user_rent") == 0){
	snprintf(sql, sizeof sql, "SELECT * FROM \"%s\";", table);

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    return ERROR;
	}

	printf("┏━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	fflush(stdout);
	printf("┃ %-8s┃  %-8s┃  %-10s┃  %-24s┃  %-24s┃\n", "RentID", "UserID", "PremiseID", "Start_rent", "End_rent");
	fflush(stdout);
	while (sqlite3_step(stmt) == SQLITE_ROW){
	    printf("┣━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	    fflush(stdout);
	    printf("┃ %-6d  ┃  %-6d  ┃  %-8d  ┃  %-24s┃  %-24s┃\n", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2), (char *)sqlite3_column_text(stmt, 3), (char *)sqlite3_column_text(stmt, 4));
	    fflush(stdout);
	}
	printf("┗━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	fflush(stdout);
	sqlite3_finalize(stmt);
	return OK;
    }

/* YOURSELF RENT */

    else if (strcmp(table, "rent_yourself") == 0){
	snprintf(sql, sizeof sql, "SELECT * FROM \"user_rent\" WHERE UserID = ?;");

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	    fprintf(stderr, "SQLite error: %s\n", sqlite3_errmsg(db));
	    fflush(stderr);
	    return ERROR;
	}
	sqlite3_bind_int64(stmt, 1, user_id);

	printf("┏━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	fflush(stdout);
	printf("┃ %-8s┃  %-8s┃  %-10s┃  %-24s┃  %-24s┃\n", "RentID", "UserID", "PremiseID", "Start_rent", "End_rent");
	fflush(stdout);
	while (sqlite3_step(stmt) == SQLITE_ROW){
	    printf("┣━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	    fflush(stdout);
	    printf("┃ %-6d  ┃  %-6d  ┃  %-8d  ┃  %-24s┃  %-24s┃\n", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2), (char *)sqlite3_column_text(stmt, 3), (char *)sqlite3_column_text(stmt, 4));
	    fflush(stdout);
	}
	printf("┗━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	fflush(stdout);
	sqlite3_finalize(stmt);
	return OK;
    }
    return ERROR;
}
