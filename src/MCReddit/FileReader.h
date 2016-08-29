#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>

class FileReader
{
public:
	FileReader();
	~FileReader();

	bool openFile(std::string path);
	bool closeFile();

	std::list<std::string> convertFile();

	std::ifstream file;
};

