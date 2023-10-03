#pragma once
#include <assimp/material.h>
#include <Resource/Texture.h>
#include <iostream>
namespace ToyEngine {
	class RenderHelper
	{
	public:
		static TextureType ConvertTextureType(aiTextureType type);

		static std::string getTextureTypeString(aiTextureType);
	};

}

