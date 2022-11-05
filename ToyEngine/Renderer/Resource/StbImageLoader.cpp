#include "Resource/StbImageLoader.h"
#include "Resource/stb_image.h"
#include<iostream>

unsigned char* ToyEngine::StbImageLoader::getImageFrom(std::string path, int* width, int* height, int* channelNum)
{
    unsigned char* data = stbi_load(path.c_str(), width, height, channelNum, 0);

    if (!data) {
        std::cerr << "Resource::StbImageLoader: Image data is not properly loaded. The path is: " << path << "." << std::endl;
        return nullptr;
    }

    return data;
}
