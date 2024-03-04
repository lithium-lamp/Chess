#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "chess.h"

using namespace std;

//remove passwords, server data
const string server = xxxxxxxxx;
const string username = xxxxxx;
const string password = xxxxxxxx;



int main()
{
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

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
    return 0;
}