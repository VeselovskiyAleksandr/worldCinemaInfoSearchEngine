#include "RequestsJSON.h"

template<typename Iterator, typename vectorJSON>
void RequestsJSON::selectingWordsMinimumLength(const Iterator &iter, Configuration& configuration, vectorJSON& strConfig, size_t& requestNumber)
{
	std::string requerie = iter;
	if (requerie.size() > configuration.minWordLength)
	{
		strConfig.push_back({ requestNumber, requerie });
		requerie = "";
	}
	else
		requerie = "";
}

template<typename vectorJSON>
void RequestsJSON::mapTraversalFunction(std::map<size_t, std::vector<std::string>>& getRequests, vectorJSON& strConfig)
{
	size_t nReq=1;
	for (auto& it = getRequests.begin(); it != getRequests.end(); it ++ )
	{
		for (const auto& iter : it->second)
		{
			selectingWordsMinimumLength(iter, configuration, strConfig, nReq);
		}
		nReq++;
	}
}

void RequestsJSON::requerInputFunction(std::map<size_t, std::vector<std::string>>& getRequests)
{
	if (getRequests.size() < configuration.maxRequest)
	{
		std::cout << "\n" << "                                      Information about domestic and foreign films" << "\n" << "\n";
		std::cout << "               Search query field" << "\n" << "\n";
		std::vector<std::string> vectorRequest;
		std::string requerie = "";
		size_t requestNumber = 0;
		std::getline(std::cin, requerie);
		if (requerie.length() > configuration.maxStrRequestLength)
		 requerie.erase(requerie.length() - configuration.maxStrRequestLength);
		requestNumber = getRequests.size();
		vectorRequest.push_back(requerie);
		requerie = "";
		getRequests.emplace(requestNumber, vectorRequest);
		vectorRequest.clear();
	}
}
void RequestsJSON::writeMapToFileFunction(std::map<size_t, std::vector<std::string>>& getRequests)
{
	nlohmann::json requerConfig;
	std::vector< nlohmann::json>strConfig;
	mapTraversalFunction(getRequests, strConfig);
	requerConfig = { "Req", strConfig };
	strConfig.clear();
	std::ofstream reqfile("requests.json", std::ios::out | std::ios::trunc);
	if (!reqfile)
		std::cout << "\n " << "Requests file is not found.";
	reqfile << requerConfig;
	requerConfig.clear();
	reqfile.close();
}

