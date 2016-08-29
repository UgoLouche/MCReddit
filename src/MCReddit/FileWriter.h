#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Ngram.h"
#include "conf.h"

class FileWriter
{
public:
	FileWriter();
	~FileWriter();

	bool openFile(std::string path);
	bool closeFile();

	void write(std::string str);
	void write(char c);
	void write(std::list<std::string> list);

	void writeText(Ngram* start, int max_ite);

	std::ofstream file;
};

