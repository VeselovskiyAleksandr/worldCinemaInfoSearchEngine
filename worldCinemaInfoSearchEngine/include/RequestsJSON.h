#pragma once
#include "EngineStart.h"

class RequestsJSON
{
public: RequestsJSON() = default;
public:
     Configuration configuration;
	 std::map <size_t, std::vector< std::string>> getRequests;

	 //функция отбора слов превышающих минимальную длину
	 template<typename Iterator, typename vectorJSON>
	 void selectingWordsMinimumLength(const typename Iterator& iter, Configuration& configuration, vectorJSON& strConfig, size_t& requestNumber);
	 
	 //функция обхода карты map
	 template<typename vectorJSON>
	 void mapTraversalFunction(std::map<size_t, std::vector<std::string>>& getRequests, vectorJSON& strConfig);

	  //функция ввода запроса
	  void requerInputFunction(std::map<size_t, std::vector<std::string>>& getRequests);

	  //функция записи запросов в файл
	  void writeMapToFileFunction(std::map<size_t, std::vector<std::string>>& getRequests);
};