///
/// \file migratedown.h
///

#pragma once

#include <string>
#include <iostream>
#include <filesystem>

void addSchema(pqxx::connection* conn, const std::string& path) {
	std::ifstream MyReadFile(path);

	std::string total;
	std::string r;

	while (std::getline(MyReadFile, r)) {
		total += r;
	}
	
	pqxx::work w(*conn);

	w.exec(total);

	w.commit();
}

void deleteSchema(pqxx::connection* conn, const std::string& path) {
	std::ifstream MyReadFile(path);

	std::string total;
	std::string r;

	while (std::getline(MyReadFile, r)) {
		total += r;
	}
	
	pqxx::work w(*conn);

	w.exec(total);

	w.commit();
}

void migrateup(pqxx::connection* conn) {
	std::string currpath = std::filesystem::current_path();

	std::string path = currpath + "/database/migration/up";

	int counter = 0;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
		std::string s = entry.path();
		addSchema(conn, s);
		counter++;
	}

	std::cout << "finished migrating up, " << counter << " files processed." << std::endl;
}

void migratedown(pqxx::connection* conn) {
	std::string currpath = std::filesystem::current_path();

	std::string path = currpath + "/database/migration/down";

	int counter = 0;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
		std::string s = entry.path();
		deleteSchema(conn, s);
		counter++;
	}

	std::cout << "finished migrating down, " << counter << " files processed." << std::endl;
}