#pragma once

#include <string>
#include <list>
#include <vector>
#include <random>
#include "NgramNode.h"

class Ngram
{
public:
	static const size_t range;

	~Ngram();
	friend class NgramNode;

	//Getter(ish)
	static const NgramNode& getTree();
	static const std::vector<Ngram*>& getVect();

	static void cleanup();
	static Ngram* registerNgram(std::string::iterator it, Ngram* current, bool isFirst);

	//Locals
	Ngram* rollNext();

	//Getter
	size_t getID();
	std::string getVal();
	std::vector<Ngram*>& getSuffix();

private:
	static size_t count;
	static NgramNode tree;
	static std::vector<Ngram*> vect;

	static std::mt19937 generator;

	Ngram();
	Ngram(std::string val);

	std::string val;
	size_t ID;
	std::vector<Ngram*> suffixes;
	std::uniform_int_distribution<int>* distri;
};

