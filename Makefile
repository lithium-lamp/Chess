# ==================================================================================== #
# HELPERS
# ==================================================================================== #

## help: print this help message
.PHONY: help
help:
	@echo 'Usage:'
	@sed -n 's/^##//p' ${MAKEFILE_LIST} | column -t -s ':' | sed -e 's/^/ /'

.PHONY: confirm
confirm:
	@echo -n 'Are you sure? [y/N] ' && read ans && [ $${ans:-N} = y ]

# ==================================================================================== #
# START
# ==================================================================================== #

## start/code: Initialize code
.PHONY: start/code
start/code:
	@echo 'Initializing code'
	g++ -std=c++20 -o output/program/main.o main.cpp game/functions/chess.cpp game/functions/chess_moves.cpp `pkg-config --cflags --libs libpqxx` -I include/laserpants/dotenv -I database/headers -I game/headers && clear && ./output/program/main.o

## start/database: Initialize database
.PHONY: start/database
start/database:
	@echo 'Initializing database'
	docker compose up

## start/reset: Reset everything and start code
.PHONY: start/reset
start/reset: confirm
	@echo 'RESETTING EVERYTHING'
	make data/migratedown
	make data/migrateup
	make data/createusers
	make start/code

# ==================================================================================== #
# DATA
# ==================================================================================== #

## data/createusers: Create test users
.PHONY: data/createusers
data/createusers:
	@echo 'Creating test users'
	g++ -std=c++20 -o output/program/createusers.o database/testing/createusers.cpp `pkg-config --cflags --libs libpqxx` -I include/laserpants/dotenv -I database/headers && clear && ./output/program/createusers.o

## data/migrateup: Migrate up
.PHONY: data/migrateup
data/migrateup: confirm
	@echo 'Migrating up'
	g++ -std=c++20 -o output/program/migrationup.o database/migration/up.cpp `pkg-config --cflags --libs libpqxx` -I include/laserpants/dotenv -I database/headers && clear && ./output/program/migrationup.o

## data/migratedown: Migrate down
.PHONY: data/migratedown
data/migratedown: confirm
	@echo 'Migrating migratedown'
	g++ -std=c++20 -o output/program/migrationdown.o database/migration/down.cpp `pkg-config --cflags --libs libpqxx` -I include/laserpants/dotenv -I database/headers && clear && ./output/program/migrationdown.o