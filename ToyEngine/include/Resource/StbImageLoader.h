#pragma once
#include "ImageLoader.h"

namespace ToyEngine {
    class StbImageLoader :public ImageLoader
    {
    public:
        static unsigned char*  getImageFrom (std::string path, int* width, int* height, int* channelNum, bool shouldFlip);
    };

}

