#include <stdlib.h>
#include <iostream>
#include <pqxx/pqxx>
#include "dotenv.h"
#include "dbconn.h"
#include "migrate.h"

/* .env variables

DB_HOST
DB_PORT
DB_USERNAME
DB_PASSWORD
DB_NAME
DB_DSN
PGADMIN_EMAIL
PGADMIN_PASSWORD
PGADMIN_HOST

*/

int main() {
    dotenv::init();

    char const* caught_dsn = std::getenv("DB_DSN");

    if (!caught_dsn)
        return 1;

    const char* DSN[] {caught_dsn};

    DBConn conn(DSN);

    migratedown(&conn.conn);
}