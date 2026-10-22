#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "EngineStart.h"
#include "RequestsJSON.h"
#include "AnswersJSON.h"
#include "ConverterJSON.h"

int main()
{
	ConverterJSON converterJSON;
	EngineStart engineStart;
	Configuration configuration;
	RequestsJSON requestsJSON;
	AnswersJSON answersJSON;
	SearchServer searchServer;
	InvertedIndex invertedIndex;

	engineStart.start(configuration);
	engineStart.openFile("answers.json");
	size_t n = 0;
	std::vector< std::string>requre;
	requre.push_back("namemovie");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	n = 1;
	requre.push_back("Etush Vysotskiy Kuravlyov");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	n = 2;
	requre.push_back("tank this other");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	n = 3;
	requre.push_back("zoya zinaida captain");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	n = 4;
	requre.push_back("zinaida Demyanenko Gaidai");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	n = 5;
	requre.push_back("Ruslan Akhmetov");
	requestsJSON.getRequests.emplace(n, requre);
	requre.clear();
	auto startTime = std::chrono::high_resolution_clock::now();
	searchServer.getWordDataFunction(invertedIndex.countWordsMap, configuration, invertedIndex.wordsFromFilesVector, invertedIndex.getCountWords);
	converterJSON.searchAnswerFunction(invertedIndex.countWordsMap, requestsJSON.getRequests);
	searchServer.getAnswerFunction();
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> serial_duration = endTime - startTime;
	std::cout << "\nQuery execution time: " << serial_duration.count() << " seconds";
	return 0;
}