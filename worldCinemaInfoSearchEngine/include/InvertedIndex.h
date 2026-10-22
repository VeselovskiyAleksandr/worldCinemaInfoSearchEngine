#pragma once
#include "Configuration.h"
#include "Entry.h"
#include "RequestsJSON.h"

class InvertedIndex
{
	public: InvertedIndex() = default;
	  Configuration configuration;
	  Entry entry;
	  RequestsJSON requestsJSON;
         //wordsFromFilesVector[DOCUMENT_NUMBER] содержит слова из документа и его номер
	  std::vector<std::string> wordsFromFilesVector[DOCUMENT_NUMBER];
        //Вектор содержит структуру с данными для данного слова.
	  std::vector<Entry> getCountWords[DOCUMENT_NUMBER];
	  //карта содержит в качестве ключа слово из документа, в качестве значения - структуру с данными для данного слова.
	  std::multimap<std::string, std::vector< Entry>> countWordsMap;

	  	  //функция обхода вектора
			void vectorTraversalFunction(std::vector<std::string>& sentence, std::vector<std::string>& setWords, std::string word);

			//функция проверки условий для записи слова в поиск
			template<typename Iterator>
			void wordEntryConditionFunction(std::string& word, std::vector<std::string>& sentence, std::vector<std::string>& setWords, Iterator& ir, Iterator& n);
			
			//функция выделения слов
			void wordSplitFunction(std::vector<std::string>& sentence, std::vector<std::string>& setWords);

			//функция заполнения вектора Entry. Содержит структуру Entry для каждого слова.
			void vectorEntryFillFunction(std::vector<std::string> vectWord[DOCUMENT_NUMBER], int n, std::vector<Entry> getCountWords[DOCUMENT_NUMBER]);

			//функция поиска документов, в которых встречается слово с расчётом абсолютной релевантности
			void relevanceIncreasingFunction(std::vector <size_t> dIDVector, std::multimap < std::string, std::multimap <size_t, size_t >>& dataWord, int& i, size_t& requestAbsoluteRelevance);

			//функция наождения максимального релеванса
			void maxRelevanceFindingFunction(std::vector <size_t> dIDVector, std::multimap < std::string, std::multimap <size_t, size_t >>& dataWord, size_t& requestAbsoluteRelevance,
				                             size_t& maxRequestAbsoluteRelevance, std::multimap <size_t, size_t >& searchRequestResult);

			//функция заполнения структуры Entry
			template<typename Iterator>
			void fillEntryFunction(size_t& countPosition, int& i, std::vector<Entry> getCountWords[DOCUMENT_NUMBER], Iterator& it, size_t& count, Entry& entry);

			//функция подсчёта повторяемости слова (внутренни цикл)
			template <typename Iterator>
			void matchSearchInnerLoopFunction(int& i, std::vector<Entry> getCountWords[DOCUMENT_NUMBER], Iterator& it, size_t& count);

			//функция подсчёта повторяемости слова (внешний цикл)
			void matchSearchOuterLoopFunction(std::vector<Entry> getCountWords[DOCUMENT_NUMBER], std::vector <Entry>& vectEntry, std::multimap<std::string, std::vector< Entry>>& countWordsMap);

			//функция записи оставшихся элементов при нахождении общих документов для слов с разной повторяемостью из одного вектора в другой
			void transferElementsFunction(std::vector <size_t>& docIDVector, std::vector <size_t>& dIDVector);
	  };