#include "stdafx.h"
#include "FileReader.h"
#include "conf.h"



FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

bool FileReader::openFile(std::string path)
{
	file.open(path, std::ios::in);

	return file.is_open();
}

bool FileReader::closeFile()
{
	file.close();

	return !file.is_open();
}

std::list<std::string> FileReader::convertFile()
{
	std::string str = "";
	std::string finalStr = "";
	std::list<std::string> list;

	while (std::getline(file, str))
	{
		if (str != POST_DELIM)  finalStr += str + '\n';
		else
		{
			list.push_back(finalStr);
			finalStr = "";
		}
	}

	if (finalStr != "")
		list.push_back(finalStr);

	return list;
}
