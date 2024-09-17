///
/// \file dbconn.h
///

#pragma once

class DBConn {
public:
	DBConn(const char* DSN[]) : conn {*DSN} {
		
	}

	void createTransaction() {
		pqxx::work w(conn);

		pqxx::row r = w.exec1("SELECT 1");

		w.commit();
	
		std::cout << r[0].as<int>() << std::endl;
	}

	pqxx::connection conn;
};