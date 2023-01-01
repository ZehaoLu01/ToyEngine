#pragma once
#include<memory>
#include<vector>
#include"Resource/stb_image.h"
#include "glad/glad.h"
#include <string>
#include <memory>
namespace ToyEngine {
	enum TextureType {
		Specular,
		Diffuse,
		Color,
	};

	// Right now only support unsigned char data.
	using TextureDataType = unsigned char;
	using std::shared_ptr;

	class Texture
	{
		friend class RenderComponent;

	public:
		Texture()
			:mData(nullptr,stbi_image_free)
		{

		}

		Texture(TextureDataType* data, unsigned int width, unsigned int height, GLenum internalFormat, GLenum mSourceFormat, unsigned int mipmapLevel, TextureType type)
			:mData(data,stbi_image_free),
			mWidth(width),
			mHeight(height),
			mInternalFormat(internalFormat),
			mSourceFormat(mSourceFormat),
			mMipmapLevel(mipmapLevel),
			mTextureType(type)
		{

			init();
		}

		~Texture() = default;

		TextureDataType* const getData() {
			return mData.get();
		}

		void init();

		std::string getTypeName();

		void setId(int id);
		void setType(const std::string& type);
		void setPath(const std::string& path);
		void setData(std::shared_ptr<TextureDataType> textureDataPtr);

		std::string getPath() {
			return mPath;
		}
	private:

		int id;
		unsigned int mWidth;
		unsigned int mHeight;
		
		// the format(color chanals) we want to store.
		GLenum mInternalFormat;
		
		// Image Data
		// Can we use smart pointer for this?
		// Picture formats have a specific sequence to stand for beginning and ending.
		std::shared_ptr<TextureDataType> mData;
		
		// the mipmap level for which we want to create a texture for if you want to set each mipmap level manually
		unsigned int mMipmapLevel = 0;
		
		// the format(color chanals) of the source image
		GLenum mSourceFormat;

		GLuint mTextureIndex;

		TextureType mTextureType;

		std::string mPath;
	};
}


