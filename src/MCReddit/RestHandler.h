#pragma once

#include <string>
#include <list>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions

class RestHandler
{
public:
	std::list<std::string> posts;

	RestHandler();
	~RestHandler();

	//void test();

	void getMessages();

private:
	time_t time_limit;

	std::string cache_after;

	string_t convertURI(time_t startTime, std::string after);
};

