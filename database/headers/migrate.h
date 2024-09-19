///
/// \file migrate.h
///

#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <set>

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

	std::set<std::filesystem::path> sorted_by_name;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
		sorted_by_name.insert(entry.path());

		counter++;
	}

	for (auto &filename : sorted_by_name) {
		addSchema(conn, filename.c_str());
	}

	std::cout << "finished migrating up, " << counter << " files processed." << std::endl;
}

void migratedown(pqxx::connection* conn) {
	std::string currpath = std::filesystem::current_path();

	std::string path = currpath + "/database/migration/down";

	int counter = 0;

	std::set<std::filesystem::path> sorted_by_name;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
		sorted_by_name.insert(entry.path());

		counter++;
	}

	 for (auto rit = sorted_by_name.rbegin(); rit != sorted_by_name.rend(); rit++)  {
		deleteSchema(conn, (*rit).c_str());
	}

	std::cout << "finished migrating down, " << counter << " files processed." << std::endl;
}