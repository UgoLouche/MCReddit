#include "stdafx.h"
#include "RestHandler.h"
#include <iostream>
#include "FileWriter.h"
#include "conf.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::json;                                  // JSON library

RestHandler::RestHandler()
{
}

RestHandler::~RestHandler()
{
}

void RestHandler::getMessages()
{	
	FileWriter writer;
	http_response response;

	http_client client(U("http://reddit.com"));
	time_limit = TIMELIMIT; 
	time_limit -= 3600 * 24 * 30; //Go a little later to catch an out of time for loop exit
	time_t startTime = std::time(0);

	string_t query = convertURI(startTime, "");

	writer.openFile(REDDIT_FILENAME);


	bool keepParsing = true;
	int request_number = 0;

	while (keepParsing)
	{
		std::cout << "Request #" << ++request_number << "...";
		std::cout << conversions::to_utf8string( query ) << "\n";

		//Launch task, then process previous return value
		pplx::task<http_response> requestTask =
			client.request(methods::GET, query);
		
		response = requestTask.get();
		while (response.status_code() != status_codes::OK)
		{
			//wait a little a try again
			std::cout << "Something went wrong : ";
			std::cout << response.status_code();
			std::cout << "... Next try in 5 seconds\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		}

		value json_response = response.extract_json().get();

		//Update "after" field for next query
		try //return NULL sometime, in that case update timestamp and go for another round
		{
			string_t tmp = json_response[U("data")][U("after")].as_string();
			cache_after = "&after=" + conversions::to_utf8string(tmp);
		}
		catch (json_exception e)
		{
			array posts_array = json_response[U("data")][U("children")].as_array();
			startTime =
				posts_array[posts_array.size()-1][U("data")][U("created")].as_integer();
			cache_after = "";
		}

		query = convertURI(startTime, cache_after);

		//Get and parse the array of posts
		array posts_array = json_response[U("data")][U("children")].as_array();

		array::iterator it;
		for (it = posts_array.begin(); it != posts_array.end(); ++it)
		{
			object curr = (*it)[U("data")].as_object();

			//Catch only self post
			if (curr[U("domain")].as_string() == U("self.lifeisstrange"))
			{
				posts.push_back(
					conversions::to_utf8string(curr[U("selftext")].as_string()));
			}

			//Check creation time to know when to stop
			if (curr[U("created")].as_integer() < TIMELIMIT)
			{
				it = posts_array.end() - 1;
				keepParsing = false;
			}

		}
	}

	writer.write(posts);
	writer.closeFile();
}

string_t RestHandler::convertURI(time_t startTime, std::string after)
{
	std::ostringstream tmpURI;

	tmpURI << SUBREDDIT_BASE
		<< "&q=timestamp%3A"
		<< time_limit
		<< ".."
		<< startTime;

	if (after.size() != 0)
		tmpURI << after;

	return conversions::to_string_t(tmpURI.str());
}
