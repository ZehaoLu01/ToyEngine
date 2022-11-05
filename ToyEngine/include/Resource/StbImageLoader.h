#pragma once
#include "ImageLoader.h"

namespace ToyEngine {
    class StbImageLoader :public ImageLoader
    {
    public:
        unsigned char* getImageFrom (std::string path, int* width, int* height, int* channelNum) override;
    };

}

