#pragma once
#include<memory>
#include<vector>
#define out
namespace ToyEngine {
	// Right now only support unsigned char data.
	using TextureDataType = unsigned char;
	using std::shared_ptr;
	class Texture
	{
	public:
		Texture(TextureDataType* data, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int mSourceFormat, unsigned int mipmapLevel)
			:mData(data),
			mWidth(width),
			mHeight(height),
			mInternalFormat(internalFormat),
			mSourceFormat(mSourceFormat),
			mMipmapLevel(mipmapLevel)
		{
			
		}

		TextureDataType* const getData() {
			return mData;
		}


	private:
		unsigned int mWidth;
		unsigned int mHeight;
		
		// the format(color chanals) we want to store.
		unsigned char mInternalFormat;
		
		// Image Data
		// Can we use smart pointer for this?
		// Picture formats have a specific sequence to stand for beginning and ending.
		TextureDataType* mData;
		
		// the mipmap level for which we want to create a texture for if you want to set each mipmap level manually
		unsigned int mMipmapLevel = 0;
		
		// the format(color chanals) of the source image
		unsigned char mSourceFormat;

	};
}


