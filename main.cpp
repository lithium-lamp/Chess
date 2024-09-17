#include <stdlib.h>
#include <iostream>
#include <pqxx/pqxx>
#include "dotenv.h"
#include "dbconn.h"

#include "game/headers/chess.h"

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
    conn.createTransaction();

    

    /*

    con->setSchema("chess_board");

    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS board_data_server");
    stmt->execute("CREATE TABLE board_data_server (id serial PRIMARY KEY, board_state VARCHAR(50), time_stamp VARCHAR(50));");

    string timestamp = "";

    res = stmt->executeQuery("SELECT UTC_TIMESTAMP");
    while (res->next()) {
        timestamp = res->getString("UTC_TIMESTAMP");
    }

    pstmt = con->prepareStatement("INSERT INTO board_data_server(board_state, time_stamp) VALUES(?,?)");
    pstmt->setString(1, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    pstmt->setString(2, timestamp);
    pstmt->execute();
    
    string current_board_state = "";

    res = stmt->executeQuery("SELECT board_state FROM board_data_server");
    while (res->next()) {
        current_board_state = res->getString("board_state");
    }

    Chess c { current_board_state };

    c.printBoard();
    c.printRefBoard();

    while (true) { //play game
        c.playMove();

        //push to server

        timestamp = "";

        res = stmt->executeQuery("SELECT UTC_TIMESTAMP");
        while (res->next()) {
            timestamp = res->getString("UTC_TIMESTAMP");
        }

        pstmt->setString(1, c.getFen());
        pstmt->setString(2, timestamp);
        
        pstmt->execute();

        c.printBoard();
        c.printRefBoard();
    }
    
    //delete res;
    delete stmt;
    delete pstmt;
    delete con;
    system("pause");

    */

    return 0;
}