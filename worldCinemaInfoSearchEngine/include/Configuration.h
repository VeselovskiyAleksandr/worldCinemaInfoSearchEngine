#pragma once
#include <iostream>
#include <string>
#include <map>

#define MAX_SIZE 10000 //наибольшее общее количество слов в документах
#define MAX_RESPONS 5 //наибольщее число ответов
#define DOCUMENT_NUMBER 10 //количество документов в базе

struct Configuration
{
	std::string name; //cодержит название движка
	std::string version; //версия движка
	std::map<int, std::string> movieTitles; //содержит пути к файлам с документами
	static const int maxRequest = 1000; //максимальное количество зпросов
	static const int maxStrRequestLength = 80; //наибольшее количество знаков в запросе
	static const int numberProcessorCores = 4; //количество ядер процессора
	static const int minWordLength = 3; //нечитаемые слова до указанной длины включительно
};