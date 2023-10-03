#include <iostream>
#include <string>
#include "Utils/Logger.h"

void ToyEngine::Logger::DEBUG_INFO(std::string msg)
{
	std::cout << "DEBUG:" << msg << std::endl;
}

void ToyEngine::Logger::DEBUG_WARNING(std::string msg)
{
	std::cout << "WARNING:" << msg << std::endl;
}

void ToyEngine::Logger::DEBUG_ERROR(std::string msg)
{
	std::cout << "ERROR:" << msg << std::endl;
}
