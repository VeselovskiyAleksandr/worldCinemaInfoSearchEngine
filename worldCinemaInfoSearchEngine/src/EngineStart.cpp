#include "EngineStart.h"

bool EngineStart::isJSONValid(const std::string& filepath)
{
	try
	{
		std::ifstream file(filepath);
		nlohmann::json data = nlohmann::json::parse(file);
		return true;
	}
	catch (const nlohmann::json::parse_error& err)
	{
		std::cerr << "JSON Error: " << err.what();
		return false;
	}
}

void EngineStart::start(Configuration& configuration)
{
	std::cout << "                              Launching a search engine... " << "\n";
	nlohmann::json config;
	std::ifstream cnfile("config.json");
	if (!cnfile)
	{
		throw std::exception();
	}
	if (cnfile.peek() != EOF)
	{
		cnfile >> config;
		cnfile.close();
		config["config"]["maxResponses"] = { MAX_RESPONS };
		std::cout << config["config"] << "\n";
		for (const auto& item : config["config"].items())
		{
			if (item.key() == "name")
			{
				configuration.name = item.value();
			}
			else if (item.key() == "version")
			{
				configuration.version = item.value();
			}
		}
		for (const auto& item : config["files"].items())
		{
			int id = stoi(item.key());
			std::pair<int, std::string> oPair(id, item.value());
			configuration.movieTitles.insert(oPair);
		}
	}
};

void EngineStart::openFile(std::string path)
{
	if (std::filesystem::exists(path))
	{
		if (path == "answers.json")
		{
			std::ofstream file("answers.json", std::ios::out | std::ios::trunc);
			file.close();
		}
	}
	else
	{
		std::ofstream file;
		file.close();
	}
};