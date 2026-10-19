#include "SearchServer.h"

int main()
{
	ConverterJSON converterJSON;
	EngineStart engineStart;
	Configuration configuration;
	RequestsJSON requestsJSON;
	AnswersJSON answersJSON;
	SearchServer searchServer;
	InvertedIndex invertedIndex;
	try
	{
		engineStart.start(configuration);
	}
	catch (const std::exception& x)
	{
		std::cerr << "\nConfiguration file is not found. Fix the problem.";
		return 1;
	}
	if (engineStart.isJSONValid("requests.json"))
	{
		std::cout << "\nrequests.json is correct!";
	}
	else
	{
		std::cout << "\nrequests.json contains errors!\n";
	}
	if (engineStart.isJSONValid("answers.json"))
	{
		std::cout << "\nanswers.json is correct!\n";
	}
	else
	{
		std::cout << "\nanswers.json contains errors!\n";
	}
	engineStart.openFile("requests.json");
	engineStart.openFile("answers.json");
	searchServer.getRequestsFunction(requestsJSON.getRequests);
    requestsJSON.requerInputFunction(requestsJSON.getRequests);
	requestsJSON.writeMapToFileFunction(requestsJSON.getRequests);
	auto startTime = std::chrono::high_resolution_clock::now();
	searchServer.getWordDataFunction(invertedIndex.countWordsMap, configuration, invertedIndex.wordsFromFilesVector, invertedIndex.getCountWords);
	converterJSON.searchAnswerFunction(invertedIndex.countWordsMap, requestsJSON.getRequests);
	searchServer.getAnswerFunction();
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> serial_duration = endTime - startTime;
	std::cout << "\nQuery execution time: " << serial_duration.count() << " seconds";
	return 0;
}
