#include <string>
#include <iostream>
#include "crow_all.h"
#include <stdlib.h>
#include <iostream>
#include <pqxx/pqxx>
#include "dotenv.h"
#include "dbconn.h"
#include "chess.h"


int main () {
    dotenv::init();

    char const* caught_dsn = std::getenv("DB_DSN");

    if (!caught_dsn)
        return 1;

    const char* DSN[] {caught_dsn};

    DBConn conn(DSN);

    /*
    int user_id1 = 1;
    int user_id2 = 2;

    int game_id = 1;

    std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    game_id = conn.createGame(user_id1, user_id2);

    conn.insertMove(game_id, defaultFen);
    
    bool inPlay = true;
    */

    crow::SimpleApp app;

    CROW_ROUTE(app, "/games")([&conn](){
        std::ostringstream os;

        std::vector<int> vec = conn.getAllGamesId();

        for (const int& val : vec) {
            os << val << std::endl;
        }

        return crow::response(os.str());
    });

    CROW_ROUTE(app, "/games/<int>")([&conn](int game_id){
        if (game_id > 100)
            return crow::response(400);

        std::ostringstream os;

        std::vector<std::string> vec = conn.getAllMovesFromGame(game_id);

        os << "viewing game number" << game_id << std::endl;

        for (const std::string& s : vec) {
            os << s << std::endl;
        }

        return crow::response(os.str());
    });

    CROW_ROUTE(app, "/games/<int>")
    .methods("POST"_method)
    ([&conn](const crow::request& req, int game_id){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(crow::status::BAD_REQUEST);

        std::string fen = conn.getFenMostRecentMove(game_id);
        int movecount = conn.getMoveCountMostRecentMove(game_id);
        bool iscompleted = conn.getIsCompletedMostRecentMove(game_id);

        Chess c { fen, movecount, iscompleted };

        int result = c.playMove(x["move"].s());

        fen = c.getFen();

        if (result == 0) {
            conn.insertMove(game_id, fen);
        }

        std::ostringstream os;
        os << "result: " << result << ", move: " << x["move"].s() << ", game id: " << game_id;
        return crow::response{os.str()};
    });

    CROW_ROUTE(app, "/games/creategame")
    .methods("POST"_method)
    ([&conn](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(crow::status::BAD_REQUEST);

        int game_id = conn.createGame(x["userid1"].i(), x["userid2"].i());

        conn.insertMove(game_id, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

        std::ostringstream os;

        os << "creating game number" << game_id << std::endl;

        return crow::response(os.str());
    });

    app.port(4000).multithreaded().run();

    return 0;
}