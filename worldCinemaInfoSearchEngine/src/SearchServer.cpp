#include "SearchServer.h"

void SearchServer::readingFromDatabaseFunction(std::queue<std::string>& q, std::mutex& mtx, std::condition_variable& cond, std::atomic<bool>& fileComplete)
{
	while (fileComplete)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cond.wait(lock, [&] { return !q.empty() || !fileComplete; });
		if (q.empty())
		{
			continue;
		}
		std::string line = q.front();
		q.pop();
		lock.unlock();
		ProcessData(line);
	}
}

void SearchServer::ProcessData(const std::string& line)
{
	std::lock_guard< std::mutex > lk(film_mutex);
}

void SearchServer::openFilesFunction(Configuration& configuration, std::string moviePath[DOCUMENT_NUMBER], std::ifstream file[DOCUMENT_NUMBER])
{
	for (int i = 0; i < DOCUMENT_NUMBER; ++i)
	{
		moviePath[i] = configuration.movieTitles.at(i + 1);
		file[i].open(moviePath[i]);
		if (!file[i].is_open())
		{
			std::cerr << "\n" << "The file " << configuration.movieTitles.at(i + 1) << " is not found." << "\n";
		}
		file[i].seekg(0);
	}
}

void SearchServer::getWordDataFunction(Configuration& configuration, std::vector<std::string> wordsFromFilesVector[DOCUMENT_NUMBER])
{
	std::vector<std::string> vectorWord[DOCUMENT_NUMBER];
	std::string strWord[DOCUMENT_NUMBER], moviePath[DOCUMENT_NUMBER];
	std::ifstream file[DOCUMENT_NUMBER];
	std::mutex mtx;
	std::queue<std::string> lines;
	std::atomic<bool> fileComplete = true;
	openFilesFunction(configuration, moviePath, file);
	readFromFilesFunction(wordsFromFilesVector, strWord, file, lines);
	for (int i = 0; i < DOCUMENT_NUMBER; ++i)
	{
	    std::vector<std::thread>threads;
		for (int i = 0; i < configuration.numberProcessorCores; ++i)
		{
			threads.emplace_back(&SearchServer::readingFromDatabaseFunction, this, ref(lines), ref(mtx), ref(cond), ref(fileComplete));
		}
		invertedIndex.wordSplitFunction(wordsFromFilesVector[i], vectorWord[i]);
		wordsFromFilesVector[i].clear();
		invertedIndex.vectorEntryFillFunction(vectorWord, i);
		fileComplete = false;
		cond.notify_all();
		for (auto& thread : threads)
		{
			thread.join();
		}
		std::vector <Entry> vectEntry;
		invertedIndex.matchSearchOuterLoopFunction(vectEntry);
		vectorWord[i].clear();
		invertedIndex.getCountWords[i].clear();
	}
}

void SearchServer::readFromFilesFunction(std::vector<std::string> wordsFromFilesVector[DOCUMENT_NUMBER], std::string strWord[DOCUMENT_NUMBER], std::ifstream file[DOCUMENT_NUMBER], std::queue<std::string> lines)
{
	for (int i = 0; i < DOCUMENT_NUMBER; ++i)
	{
		std::string key = std::to_string(i);
		wordsFromFilesVector[i].push_back("\ndoc_id: ");
		wordsFromFilesVector[i].push_back(key);
		wordsFromFilesVector[i].push_back("\n ");
		key = "";
		while (getline(file[i], strWord[i]))
		{
			lines.push(strWord[i]);
			wordsFromFilesVector[i].push_back(strWord[i]);
			strWord[i] = "";
		}
		file[i].close();
	}
}

template <typename JsonIterator>
void SearchServer::conditionCheckingFunction(std::map <size_t, std::vector<std::string>>& getRequests, std::vector<std::string>& vecRequest, size_t& nReq, const JsonIterator& itr)
{
	std::string strValue = itr.value().is_string() ? itr.value().get<std::string>() : to_string(itr.value());
	if (!strValue.empty() && strValue != "Req")
	{
		strValue = strValue.substr(4, strValue.size() - 6);
		vecRequest.push_back(strValue);
		getRequests.emplace(nReq, vecRequest);
		nReq++;
	}
	vecRequest.clear();
}

template<typename JsonType>
void SearchServer::JsonTraversalFunction_1(std::map<size_t, std::vector<std::string>>& getRequests, std::vector<std::string>& vecRequest, size_t& nReq, const JsonType& data)
{
	for (const auto& item : data.items())
	{
		for (const auto& itr : item.value().items())
		{
			conditionCheckingFunction(getRequests, vecRequest, nReq, itr);
		}
	}
}

void SearchServer::getRequestsFunction(std::map<size_t, std::vector <std::string>>& getRequests)
{
	std::ifstream reqfile("requests.json");
	if (!reqfile)
		std::cout << "\n " << "Requests file is not found.";
	if (reqfile.peek() != EOF)
	{
		nlohmann::json reqconfig;
		reqfile.seekg(0);
		reqfile >> reqconfig;
		reqfile.close();
		size_t nReq = 0;
		std::vector<std::string> vecRequest;
		JsonTraversalFunction_1(getRequests, vecRequest, nReq, reqconfig);
	}
}

template<typename JsonType>
 void SearchServer::fillingAnswerVectorFunction(JsonType& it, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer)
{
	for (const auto& im : it.value().items())
	{
			val = to_string(im.value());
			vecAnswer.push_back(val);
			val = "";
	}
}

template<typename JsonType>
 void SearchServer::JsonTraversalFunction_2(const JsonType& ir, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer)
{
	for (const auto& iq : ir.value().items())
	{
		for (const auto& it : iq.value().items())
		{
			fillingAnswerVectorFunction(it, nReq, val, key, vecAnswer);
		}
	}
}

template<typename JsonType>
 void SearchServer::extractDataFileFunction(JsonType& ansconfig, size_t& nReq, std::string& val, std::string& key, std::vector<std::string>& vecAnswer)
{
	for (const auto& item : ansconfig.items())
	{
		for (const auto& ir : item.value().items())
		{
			JsonTraversalFunction_2(ir, nReq, val, key, vecAnswer);
		}
	}
}

void SearchServer::getAnswerFunction()
{
	std::ifstream ansfile("answers.json");
	if (!ansfile)
		std::cout << "\n " << "Requests file is not found.";
	if (ansfile.peek() != EOF)
	{
		nlohmann::json ansconfig;
		size_t nReq = 0;
		std::string val = "", key = "";
		std::vector<std::string> vecAnswer;
		if (ansfile.peek() != EOF)
		{
			ansfile.seekg(0);
			ansfile >> ansconfig;
			ansfile.close();
			extractDataFileFunction(ansconfig, nReq, val, key, vecAnswer);
		}
		answersJSON.responseOutputFunction(vecAnswer);
	}
}