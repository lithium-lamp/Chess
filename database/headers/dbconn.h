///
/// \file dbconn.h
///

#pragma once

class DBConn {
public:
	DBConn(const char* DSN[]) : conn {*DSN} {
		
	}

	int getUser(const std::string& username) {
		pqxx::work w(conn);

		pqxx::row r = w.exec1("SELECT id FROM users WHERE name='" + username + "'");

		w.commit();

		return r[0].as<int>();
	}

	int createUser(const std::string& username) {
		pqxx::work w(conn);

		pqxx::row r = w.exec1("INSERT INTO users(name) VALUES ('" + username + "') RETURNING id");

		w.commit();

		return r[0].as<int>();
	}

	std::vector<std::string> getAllMovesFromGame(int game_id) {
		pqxx::work w(conn);

		std::string s = std::to_string(game_id);

		pqxx::result r { w.exec("SELECT fen FROM chess_game WHERE all_games_id=" + s) };
		
		std::vector<std::string> outvec;
		outvec.reserve(std::size(r));

		for (auto row: r) {
			outvec.push_back(row["fen"].c_str());
		}

		w.commit();

		return outvec;
	}

	std::vector<int> getAllGamesId() {
		pqxx::work w(conn);

		pqxx::result r { w.exec("SELECT id FROM chess_game") };
		
		std::vector<int> outvec;
		outvec.reserve(std::size(r));

		for (auto row: r) {
			outvec.push_back(std::stoi(row["id"].c_str()));
		}

		w.commit();

		return outvec;
	}

	std::string getFenMostRecentMove(int game_id) {
		pqxx::work w(conn);

		std::string s = std::to_string(game_id);

		pqxx::row r = w.exec1("SELECT fen FROM chess_game WHERE all_games_id=" + s + " ORDER BY id DESC LIMIT 1;");
		
		w.commit();

		return r[0].as<std::string>();
	}

	int getMoveCountMostRecentMove(int game_id) {
		pqxx::work w(conn);

		std::string s = std::to_string(game_id);

		pqxx::row r = w.exec1("SELECT COUNT(id) FROM chess_game WHERE all_games_id=" + s);
		
		w.commit();

		return r[0].as<int>() - 1;
	}

	bool getIsCompletedMostRecentMove(int game_id) {
		pqxx::work w(conn);

		std::string s = std::to_string(game_id);

		pqxx::row r = w.exec1("SELECT concluded FROM all_chess_games WHERE id=" + s);
		
		w.commit();

		return r[0].as<bool>();
	}

	int createGame(int user_id1, int user_id2) {
		pqxx::work w(conn);

		std::string s = std::to_string(user_id1) + ", " + std::to_string(user_id2);

		pqxx::row r = w.exec1("INSERT INTO all_chess_games(user_id1, user_id2, version) VALUES (" + s + ", 1) RETURNING id");

		w.commit();

		return r[0].as<int>();
	}

	void insertMove(int all_games_id, const std::string& fen) {
		pqxx::work w(conn);

		std::string s = std::to_string(all_games_id) + ", '" + fen + "'";

		w.exec("INSERT INTO chess_game(all_games_id, fen, version) VALUES (" + s + ", 1)");

		w.commit();
	}

	pqxx::connection conn;
};