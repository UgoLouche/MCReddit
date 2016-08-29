#include "stdafx.h"
#include "Ngram.h"
#include "NgramNode.h"
#include <assert.h>
#include <chrono>
#include "conf.h"

const size_t Ngram::range = NGRAM_SIZE;

Ngram::~Ngram()
{
	//Check if vector is not yet destroyed
	if(vect.size() > ID) vect[ID] = NULL;

	if (distri != NULL) delete(distri);
}

const NgramNode& Ngram::getTree()
{
	return tree;
}

const std::vector<Ngram*>& Ngram::getVect()
{
	return vect;
}

void Ngram::cleanup()
{
	//Simply go through vect and delete everything. Every created node is in Vect
	std::vector<Ngram*>::iterator it;

	for (it = vect.begin(); it != vect.end(); ++it)
	{
		if (*it != NULL) delete(*it);
		--count;
	}
}

//it is an iterator to the first char of suffix
Ngram* Ngram::registerNgram(std::string::iterator it, Ngram* current, bool isFirst)
{
	Ngram* ngram_suffix;

	if (isFirst)
	{
		current = getVect()[0];
	}

	ngram_suffix = tree.addNgram(it);

	current->getSuffix().push_back(ngram_suffix);
	return ngram_suffix;

}

Ngram* Ngram::rollNext()
{
	//Catch terminal Ngram first
	if (suffixes.size() == 0) return NULL;

	//a new distri is needed
	if (distri != NULL && distri->max() != suffixes.size() - 1)
	{
		delete(distri);
		distri = NULL;
	}

	if (distri == NULL)
		distri = new std::uniform_int_distribution<int>(0, suffixes.size() - 1);

	return suffixes[(*distri)(Ngram::generator)];
}

size_t Ngram::getID()
{
	return ID;
}

std::string Ngram::getVal()
{
	return val;
}

std::vector<Ngram*>& Ngram::getSuffix()
{
	return suffixes;
}


//Private
size_t Ngram::count = 0;
NgramNode Ngram::tree = NgramNode('\0', -1, NULL, NULL);
std::vector<Ngram*> Ngram::vect = std::vector<Ngram*>(1, new Ngram("")); //Special case, epsilon


std::mt19937 Ngram::generator(std::chrono::system_clock::now().time_since_epoch().count());

Ngram::Ngram()
	: Ngram("")
{
}

Ngram::Ngram(std::string val)
	: val(val), ID(Ngram::count++), suffixes(std::vector<Ngram*>(0)), distri(NULL)
{
	vect.push_back(this);
	assert(vect[ID] == this);
}

