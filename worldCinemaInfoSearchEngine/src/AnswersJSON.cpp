#include "AnswersJSON.h"

void AnswersJSON::searchIdenticalWordsFunction(std::multimap<std::string, std::vector< Entry>>& countWordsMap, std::multimap<size_t, size_t>& searchResult,
	                                           std::vector<std::string>& requestWord, int& i, std::multimap < size_t, std::vector <size_t>>& getDataRequest,
	                                           std::multimap < std::string, std::multimap <size_t, size_t>>& dataWord)
{
	size_t wordRepetition = 0;
	std::vector <size_t> docWord;
	auto itr = countWordsMap.equal_range(requestWord[i]);
	for (auto it = itr.first; it != itr.second; ++it)
	{
		for (auto m : it->second)
		{
			searchResult.insert({ m.freqWordsCount, m.docId });
			size_t wordRepetition = m.wordFrequency;
			docWord.push_back(m.docId);
		}
	}
	getDataRequest.insert({ wordRepetition, docWord });
	dataWord.insert({ requestWord[i],searchResult });
	wordRepetition = 0;
	docWord.clear();
}

void AnswersJSON::writingDataFileFunction(std::vector< nlohmann::json>& resultVectorConfig)
{
	std::ofstream ansfile("answers.json", std::ios::out | std::ios::trunc);
	if (!ansfile)
		std::cout << "\n " << "Answers file is not found.";
	ansfile << resultVectorConfig;
	ansfile.close();
	resultVectorConfig.clear();
}
void AnswersJSON::responseOutputFunction(std::vector<std::string>& vecAnswer)
{
	for (int i = 0; i < vecAnswer.size(); ++i)
	{
		std::cout << "\n " << vecAnswer[i];
	}
}