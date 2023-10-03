#include <iostream>
#include <string>
#include "Utils/Logger.h"

void ToyEngine::Logger::DEBUG(std::string& msg)
{
	std::cout << "DEBUG:" << msg << std::endl;
}
