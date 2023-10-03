#include "Resource/StbImageLoader.h"
#include "Resource/stb_image.h"
#include<iostream>

// Guarunteed to produce a non-null pointer to the image.
// Otherwise it throws an exception.
unsigned char* ToyEngine::StbImageLoader::getImageFrom(std::string path, int* width, int* height, int* channelNum, bool shouldFlip)
{
    const std::string DEFAULT_PATH_PREFIX = "";

    // We probably don't need to flip the image here because the texture coordinate will be flipped when setting up the assimp.
    // But for those images that is not a texture, we still need to flip it.
    stbi_set_flip_vertically_on_load(shouldFlip);
    unsigned char* data = stbi_load((DEFAULT_PATH_PREFIX + path).c_str(), width, height, channelNum, 0);

    if (!data) {
        throw std::exception("Image data is not properly loaded from path.");
    }

    return data;
}

// Guarunteed to produce a non-null pointer to the image.
// Otherwise it throws an exception.
unsigned char* ToyEngine::StbImageLoader::getImageFrom(stbi_uc const* buffer, int len, bool shouldFlip, int& width, int& height, int& channels)
{
    stbi_set_flip_vertically_on_load(shouldFlip);
    unsigned char* data = stbi_load_from_memory(buffer, len, &width, &height, &channels, 0);
    if (!data) {
        throw std::exception("Image data is not properly loaded from buffer.");
    }

    return data;
}


