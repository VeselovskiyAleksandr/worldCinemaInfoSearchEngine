#pragma once
#include "InvertedIndex.h"

class AnswersJSON
{
public: AnswersJSON() = default;
	  InvertedIndex invertedIndex;

	  //функция заполняет структуру Entry в карте для каждого слова
	  void searchIdenticalWordsFunction(std::multimap<std::string, std::vector< Entry>>& countWordsMap, std::multimap<size_t, size_t>& searchResult,
		    std::vector<std::string>& requestWord, size_t& absoluteRelevance, size_t& maxAbsoluteRelevance, size_t& maxAbsoluteRelevanceDoc, int& i,
		    std::multimap < size_t, std::vector <size_t>> & getDataRequest, std::multimap < std::string, std::multimap <size_t, size_t>>& dataWord);

	  //функция записи содержимого в JSON в файл
	  void writingDataFileFunction(std::vector< nlohmann::json>& resultVectorConfig);

	  //функция вывода ответов
	   void responseOutputFunction(std::vector<std::string>& vecAnswer);
};