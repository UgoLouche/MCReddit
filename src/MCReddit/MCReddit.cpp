//Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileReader.h"
#include "NgramNode.h"
#include "Ngram.h"
#include "NgramParser.h"
#include "FileWriter.h"
#include <vector>
#include <list>
#include "conf.h"
#include "RestHandler.h"


int main()
{
	FileReader reader;
	FileWriter out;
	std::list<std::string> posts_list;
	NgramParser parser;
	RestHandler redditHandler;

	//Execution flags
	bool redditParse = true;
	bool NgramAnalysis = true;

	std::cout << "Hello World" << "\n";

	if (redditParse)
	{
		std::cout << "Parsing Reddit (this may take a while)...\n";
		redditHandler.getMessages();
		std::cout << "Done ! \n";
	}

	if (NgramAnalysis)
	{
		if (redditParse)//Don't bother reading from file, everything already in memory
		{
			posts_list = redditHandler.posts;
		}
		else
		{
			//Read file and store in a string
			std::cout << "File Parsing mode ...\n";
			std::cout << "Open Input: " << REDDIT_FILENAME << "...";
			if (!reader.openFile("redditParse.txt")) std::cout << "Error opening input";
			else std::cout << "ok\n";

			std::cout << "Reading from file...";
			posts_list = reader.convertFile();
			if (!reader.closeFile()) std::cout << "Error closing input";
			else std::cout << "ok\n";
		}

		//Parse the whole thing
		std::cout << "parsing Ngram (this may take a while, and a lot of memory)...\n";
		parser.parseList(posts_list);
		std::cout << "ok \n";

		//Write Stuff
		std::cout << "Open output: " << OUTPUT_FILENAME << "...";
		if (!out.openFile("out.txt")) std::cout << "Error opening output";
		else std::cout << "ok\n";

		std::cout << "Writing " << WRITE_ITERATION << " texts...";
		for (int i = 0; i < WRITE_ITERATION; ++i)
		{
			out.writeText(Ngram::getVect()[0], TEXT_SIZE);
			out.write('\n');
			out.write(POST_DELIM);
			out.write('\n');
		}
		std::cout << "ok\n";

		if (!out.closeFile()) std::cout << "Error closing output";
		else std::cout << "Output Closed, deleting data and closing...\n";
		Ngram::cleanup();
	}

	return 0;
}

