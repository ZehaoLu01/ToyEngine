#pragma once
#include<memory>
#include<vector>
#include"Resource/stb_image.h"
#include "glad/glad.h"
#include <string>
#include <memory>
namespace ToyEngine {
	using VertexDataElementType = float;
	using VertexData = std::vector<VertexDataElementType>;
	using VertexDataPtr = std::shared_ptr<VertexData>;

	using IndexDataElementType = unsigned int;
	using IndexData = std::vector<IndexDataElementType>;
	using IndexDataPtr = std::shared_ptr<IndexData>;

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

		GLuint getTextureIndex() {
			return mTextureIndex;
		}
		unsigned int getWidth() {
			return mWidth;
		}
		unsigned int getHeight() {
			return mHeight;
		}
	private:

		int id;
		unsigned int mWidth;
		unsigned int mHeight;
		
		// the format(color chanals) we want to store.
		GLenum mInternalFormat;
		
		// Image Data
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


