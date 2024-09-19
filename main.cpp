#include <stdlib.h>
#include <iostream>
#include <pqxx/pqxx>
#include "dotenv.h"
#include "dbconn.h"
#include "chess.h"

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

    int user_id1 = 1;
    int user_id2 = 2;

    // if users do not exist, create them
    // user_id1 = conn.createUser("matt");
    // user_id2 = conn.createUser("jeff");

    int game_id = 1;

    std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    game_id = conn.createGame(user_id1, user_id2);

    conn.insertMove(game_id, defaultFen);
    
    bool inPlay = true;

    Chess c { defaultFen };
    
    c.printBoard();
    c.printRefBoard();

    while (inPlay) {
        c.playMove();

        conn.insertMove(game_id, c.getFen());

        c.printBoard();
        c.printRefBoard();
    }

    return 0;
}