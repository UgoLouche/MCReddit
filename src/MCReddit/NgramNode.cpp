#include "stdafx.h"
#include "NgramNode.h"
#include "Ngram.h"
#include <assert.h>

NgramNode::NgramNode(char val, int depth, Ngram* leaf, NgramNode* parent)
	: val(val),
	depth(depth),
	subNgram(0),
	parent(parent),
	childrens(std::vector<NgramNode*>(255, NULL)),
	leaf(leaf)
{
}

NgramNode::NgramNode()
	: NgramNode('\0', -1, NULL, NULL)
{
}

NgramNode::~NgramNode()
{
}

Ngram* NgramNode::addNgram(std::string::iterator it)
{
	return getNgram(it, true);
}

Ngram* NgramNode::searchNgram(std::string::iterator it)
{
	return getNgram(it, false);
}

Ngram* NgramNode::getNgram(std::string::iterator it, bool newOccur)
{
	//Check for terminal node
	if (depth + 1 == Ngram::range)
	{
		//Update occurence count
		if (newOccur)
		{
			if (leaf == NULL) //A new Ngram will be created
				noticeNewOccur();
		}

		//newly created node
		if (leaf == NULL) leaf = new Ngram(std::string(it - Ngram::range, it));

		return leaf;
	}
	//Non Terminal Node
	else
	{
		uint8_t index = (uint8_t)(*it);

		//Does the next children already exist ?
		if (childrens[index] == NULL)
		{
			if (newOccur)
			{
				childrens[index] =
					new NgramNode(*(it), depth + 1, NULL, this);
			}
			else return NULL;
		}

		assert((char)index == childrens[index]->val); //logic check please ignore
		return childrens[index]->getNgram(it+1, newOccur);
	}
}

/*
Ngram* NgramNode::getNgram(std::string val, bool newOccur)
{
	//Catch epsilon node
	if (val == "") return Ngram::getVect()[0];

	//Check string size, just in case
	assert(val.size() == Ngram::range);

	//Check for terminal node
	if (depth + 1 == Ngram::range)
	{
		//Update occurence count
		if (newOccur)
		{
			if (leaf == NULL) //A new Ngram will be created
				noticeNewOccur();
		}

		//newly created node
		if (leaf == NULL) leaf = new Ngram(val);

		return leaf;
	}
	//Non Terminal Node
	else
	{
		uint8_t index = (uint8_t)val[depth + 1];

		//Does the next children already exist ?
		if (childrens[index] == NULL)
		{
			if (newOccur)
			{
				childrens[index] =
					new NgramNode(val[depth + 1], depth + 1, NULL, this);
			}
			else return NULL;
		}

		assert((char)index == childrens[index]->val); //logic check please ignore
		return childrens[index]->getNgram(val, newOccur);
	}
}
*/

void NgramNode::noticeNewOccur()
{
	subNgram++;

	if (parent != NULL) parent->noticeNewOccur();
}