#pragma once
#include <string>

namespace ToyEngine {

	class Logger
	{
	public:
		static void DEBUG_INFO(std::string msg);

		static void DEBUG_WARNING(std::string msg);

		static void DEBUG_ERROR(std::string msg);
	};

}

