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

	void addSchema() {
		std::cout << "adding schema ..." << std::endl;
	}

	void deleteSchema() {
		std::cout << "deleting schema ..." << std::endl;
	}

	pqxx::connection conn;
};