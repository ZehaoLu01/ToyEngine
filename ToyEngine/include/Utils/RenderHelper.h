#pragma once
#include <assimp/material.h>
#include <Resource/Texture.h>
#include <iostream>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

namespace ToyEngine {
	class RenderHelper
	{
	public:
		static TextureType ConvertTextureType(aiTextureType type);

		static std::string getTextureTypeString(aiTextureType);

		static GLenum convertChannelsToFormat(unsigned int channels);

		static std::string getVec3String(glm::vec3 vec);
	};

}

