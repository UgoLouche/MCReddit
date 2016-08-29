#pragma once

#include <vector>

class Ngram;

class NgramNode
{
public:
	NgramNode(char val, int depth, Ngram* leaf, NgramNode*  parent);
	NgramNode();
	~NgramNode();

	Ngram* addNgram(std::string::iterator it);
	Ngram* searchNgram(std::string::iterator it);

private:
	char val;
	int depth;
	size_t subNgram;
	NgramNode* parent;
	std::vector<NgramNode*> childrens; //Index are uint8_t value of corresponding char
	Ngram* leaf;

	Ngram* getNgram(std::string::iterator it, bool newOccur);

	//Occur Counting
	void noticeNewOccur();
};

