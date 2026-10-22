project(Examples)
add_executable(Examples example.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../worldCinemaInfoSearchEngine/src/InvertedIndex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}"/../worldCinemaInfoSearchEngine/src/EngineStart.cpp"
	${CMAKE_CURRENT_SOURCE_DIR}"/../worldCinemaInfoSearchEngine/src/RequestsJSON.cpp"
	${CMAKE_CURRENT_SOURCE_DIR}"/../worldCinemaInfoSearchEngine/src/AnswersJSON.cpp"
	${CMAKE_CURRENT_SOURCE_DIR}"/../worldCinemaInfoSearchEngine/src/ConverterJSON.cpp"
	${CMAKE_CURRENT_SOURCE_DIR}"/../worldCinemaInfoSearchEngine/src/SearchServer.cpp"
)
target_include_directories(Examples PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../worldCinemaInfoSearchEngine
	${CMAKE_CURRENT_SOURCE_DIR}/../worldCinemaInfoSearchEngine/include
)
target_link_libraries(Examples PRIVATE
	nlohmann_json::nlohmann_json
)