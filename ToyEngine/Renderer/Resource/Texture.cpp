#include <iostream>
#include "Resource/Texture.h"
#include "glad/glad.h"
#include <Resource/StbImageLoader.h>
#include <Utils/Logger.h>
#include <Utils/RenderHelper.h>

namespace ToyEngine {
	Texture::Texture(const Texture& other): mPath(other.mPath), mWidth(other.mWidth),mHeight(other.mHeight),mInternalFormat(other.mInternalFormat), mSourceFormat(other.mSourceFormat), mMipmapLevel(other.mMipmapLevel), mTextureIndex(other.mTextureIndex), mTextureType(other.mTextureType)
	{
	}
	Texture& Texture::operator=(Texture other)
	{
		std::swap(mPath, other.mPath);
		std::swap(mWidth, other.mWidth);
		std::swap(mHeight, other.mHeight);
		std::swap(mInternalFormat, other.mInternalFormat);
		std::swap(mSourceFormat, other.mSourceFormat);
		std::swap(mMipmapLevel, other.mMipmapLevel);
		std::swap(mTextureIndex, other.mTextureIndex);
		std::swap(mTextureType, other.mTextureType);
		return *this;
	}

	void Texture::loadFromPath(bool flip){
		try {
			if (mPath == "") {
				throw("Invalid texture path: " + mPath);
			}
			int channels = 0;
			auto textureData = StbImageLoader::getImageFrom(mPath, &mWidth, &mHeight, &channels, flip);

			mSourceFormat = RenderHelper::convertChannelsToFormat(channels);
			mInternalFormat = RenderHelper::convertChannelsToFormat(channels);

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

			glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mSourceFormat, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		catch (const std::string& err) {
			std::cerr << err << std::endl;
		}	
	}

	void Texture::loadFromBuf(stbi_uc const* buffer, int len, bool shouldFlip)
	{
		try {
			int channels = 0;

			auto textureData = StbImageLoader::getImageFrom(buffer, len, shouldFlip, mWidth, mHeight, channels);
			
			mSourceFormat = RenderHelper::convertChannelsToFormat(channels);
			mInternalFormat = RenderHelper::convertChannelsToFormat(channels);

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

			glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mSourceFormat, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(textureData);
		}
		catch (const std::string& err) {
			std::cerr << err << std::endl;
		}
		catch (const std::exception& e) {
			Logger::DEBUG_WARNING(e.what());
		}
	}

	// TODO: Move it to render helper.
	std::string Texture::getTypeName() {
		switch (mTextureType)
		{
		case ToyEngine::Specular:
			return "specular";
			break;
		case ToyEngine::Diffuse:
			return "diffuse";
			break;
		case ToyEngine::Ambient:
			return "ambient";
			break;
		case ToyEngine::Height:
			return "height";
			break;
		case ToyEngine::Normal:
			return "normal";
			break;
		default:
			std::cerr << "TextureType string is not defined";
			return "";
		}
	}
}