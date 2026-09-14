#pragma once
#include "ConverterJSON.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono> 

class SearchServer
{
public: SearchServer() = default;
	  ConverterJSON converterJSON;
	  AnswersJSON answersJSON;
	  InvertedIndex invertedIndex;
	  std::mutex film_mutex;
	  std::condition_variable cond;

	  //функции потоков
	  void readingFromDatabaseFunction(std::queue<std::string>& q, std::mutex& mtx, std::condition_variable& cond, std::atomic<bool>& fileComplete);
	  void ProcessData(const std::string& line);

	  //функция открытия файлов с документами
	  void openFilesFunction(Configuration& configuration, std::string moviePath[DOCUMENT_NUMBER], std::ifstream file[DOCUMENT_NUMBER]);

	  //функция получения данных о словах
	  void getWordDataFunction(std::multimap<std::string, std::vector< Entry>>& countWordsMap, Configuration& configuration, std::vector<std::string> wordsFromFilesVector[DOCUMENT_NUMBER],
		  std::vector<Entry> getCountWords[DOCUMENT_NUMBER]);

	  //функция чтения из файлов
	  void readFromFilesFunction(std::vector<std::string> wordsFromFilesVector[DOCUMENT_NUMBER], std::string strWord[DOCUMENT_NUMBER], std::ifstream file[DOCUMENT_NUMBER], std::queue<std::string> lines);

	  template<typename JsonIterator>
	  void conditionCheckingFunction(std::map<size_t, std::vector<std::string>>& getRequests, std::vector<std::string>& vecRequest, size_t& nReq, const JsonIterator& element);

	  template<typename JsonType>
	  void JsonTraversalFunction_1(std::map<size_t, std::vector<std::string>>& getRequests, std::vector<std::string>& vecRequest, size_t& nReq, const JsonType& data);

	  //функция получения запросов
	  void getRequestsFunction(std::map<size_t, std::vector<std::string>>& getRequests);

	  //функция заполнения вектора ответов
	  template<typename JsonType>
	  void fillingAnswerVectorFunction(JsonType& it, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer);

	  //функция обхода nlohmann::JSON 
	  template<typename JsonType>
	  void JsonTraversalFunction_2(const JsonType& data, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer);

	  //функция получения данных из файла
	  template<typename JsonType>
	  void extractDataFileFunction(JsonType& ansconfig, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer);

	  //функция вывода результатов поиска
	  void getAnswerFunction();
};
