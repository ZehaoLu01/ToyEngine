#include <iostream>
#include "Resource/Texture.h"
#include "glad/glad.h"

namespace ToyEngine {
	void Texture::init(){
		glGenTextures(1, &mTextureIndex);
		glBindTexture(GL_TEXTURE_2D, mTextureIndex);
		// Add more texture here.


		//Configuration
		//=================================================================================
		// what if the texture coordinate is over 1.0?
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// For GL_CLAMP_TO_BORDER
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		//=================================================================================
		// filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//=================================================================================

		if (mData) {
			unsigned char* data_c = mData.get();

			glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mSourceFormat, GL_UNSIGNED_BYTE, data_c);

			glGenerateMipmap(GL_TEXTURE_2D);

			// Remember to set the uniform!!
		}
		else {
			std::cerr << "????????????????" << std::endl;
		}
	}

	std::string Texture::getTypeName() {
		switch (mTextureType)
		{
		case ToyEngine::Specular:
			return "specular";
			break;
		case ToyEngine::Diffuse:
			return "diffuse";
			break;
		default:
			std::cerr << "TextureType string is not defined";
			return "";
		}
	}

	void Texture::setId(int id) {
		id = id;
	}
	void Texture::setType(const std::string& type) {
		if (type == "texture_diffuse") {
			mTextureType = ToyEngine::Diffuse;
		}
		else if (type == "texture_specular") {
			mTextureType = ToyEngine::Specular;
		}
	}

	void Texture::setPath(const std::string& path)
	{
		mPath = path;
	}

	void Texture::setData(std::shared_ptr<TextureDataType> textureDataPtr)
	{
		mData = textureDataPtr;
	}

}