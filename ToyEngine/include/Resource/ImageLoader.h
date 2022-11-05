#pragma once
#include <string>

namespace ToyEngine{
	
	class ImageLoader
	{
	protected:
		const std::string DEFAULT_IMAGE_PATH_PREFIX = "Resources/Images/";
	public:
		virtual unsigned char* getImageFrom(std::string path, int* width, int* height, int* channelNum) = 0;
	};
}

