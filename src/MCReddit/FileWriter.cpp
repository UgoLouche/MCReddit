#include "stdafx.h"
#include "FileWriter.h"


FileWriter::FileWriter()
{
}


FileWriter::~FileWriter()
{
}

bool FileWriter::openFile(std::string path)
{
	file.open(path, std::ios::out|std::ios::trunc);

	return file.is_open();
}

bool FileWriter::closeFile()
{
	file.close();

	return !file.is_open();
}

void FileWriter::write(std::string str)
{
	file << str;
}

void FileWriter::write(char c)
{
	file << c;
}

void FileWriter::write(std::list<std::string> list)
{
	std::list<std::string>::iterator it;

	for (it = list.begin(); it != list.end(); ++it)
	{
		write(*it);
		write('\n');
		write(POST_DELIM);
		write('\n');
	}
}

void FileWriter::writeText(Ngram* start, int max_ite)
{
	start = start->rollNext();

	int it = 0;
	while (start != NULL)
	{
		if (it == 0) write(start->getVal()); //First iteration, print the full value
		else write(start->getVal()[Ngram::range - 1]);

		start = start->rollNext();

		if (++it > max_ite && max_ite != -1) break;
	}
}
