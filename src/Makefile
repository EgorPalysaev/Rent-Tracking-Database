CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c23
LDLIBS = -lsqlite3 -lm

HEADERS = $(wildcard *.h)

DB = database/local.db
SCHEMA = database/schema.sql

SOURCES = main.c menu.c registration.c \
          services/utils.c \
          services/add_premise.c \
          repositories/registration_repo.c \
          repositories/show_all_data.c \
          repositories/auth_repo.c \
          repositories/add_premise_repo.c \
          database/database.c \
	  repositories/delete.c \
	  repositories/update_repo.c \
	  services/update_service.c \
	  repositories/rent_repo.c \
	  repositories/close_rent_repo.c

create-db: $(SCHEMA)
	touch database/local.db

refresh-db: $(DB)
	sqlite3 $(DB) < $(SCHEMA)
	
app: $(HEADERS) | $(DB)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDLIBS)
clean-app:
	rm -f app
clean-db:
	rm -f $(DB)
