#pragma once

#include "NgramNode.h"
#include <string>
#include <vector>
#include <list>

class NgramParser
{
public:
	NgramParser();
	~NgramParser();

	void parseString(std::string str);

	void parseList(std::list<std::string> list);



private:

	//NgramNode& tree;
	//std::vector<Ngram> vect;

	//size_t getPrefixIndex(std::vector<Ngram> ngramVect, std::string prefix);
};

