#pragma once
#include "ImageLoader.h"
#include "stb_image.h"

namespace ToyEngine {
    class StbImageLoader :public ImageLoader
    {
    public:
        static unsigned char*  getImageFrom (std::string path, int* width, int* height, int* channelNum, bool shouldFlip);
        static unsigned char* getImageFrom (stbi_uc const* buffer, int len, bool shouldFlip, int& width, int& height, int& channels);
    };

}

