#include "stdafx.h"
#include "NgramParser.h"
#include "Ngram.h"
#include <iterator>
#include <iostream>


NgramParser::NgramParser()
{
}

NgramParser::~NgramParser()
{
	//if (adjMatrixCache != NULL) delete(adjMatrixCache);
}

void NgramParser::parseString(std::string str)
{
	Ngram* last = NULL;

	for (size_t i = 0; i < Ngram::range; ++i) str += '\0'; //Padding

	std::string::iterator start = str.begin();

	while (start != str.end() - Ngram::range)
	{
		if (start == str.begin()) last = Ngram::registerNgram(start++, NULL, true);
		else last = Ngram::registerNgram(start++, last, false);
	}
}

void NgramParser::parseList(std::list<std::string> list)
{
	std::list<std::string>::iterator it;

	size_t i = 0;
	for (it = list.begin(); it != list.end(); ++it)
	{

		parseString(*it);
		
		//Add some interactivity
		++i;
		if ((i * 100 / list.size()) % 10 == 0)
			std::cout << (i * 100 / list.size()) << "% done\n";
	}
}

/*
void NgramParser::generateVect()
{
	vect = tree.getSortedNgrams();
}
*/


/*
std::vector<Ngram>& NgramParser::getVect()
{
	return vect;
}

size_t NgramParser::getPrefixIndex(std::vector<Ngram> ngramVect, std::string prefix)
{
	std::vector<Ngram>::iterator it = ngramVect.begin();

	while (!( (*it) == prefix)) ++it;

	return it - ngramVect.begin();
}
*/
