#pragma once

#include <unordered_map>
#include <string>
#include <Resource/Texture.h>

namespace ToyEngine{
	using std::unordered_map;
	using std::string;
	class ResourceManager
	{
	public:
		Texture getTexture(const string& fileName) {
			if (tMap.find(fileName) == tMap.end()) {
				return Texture();
			}
			return tMap[fileName];
		}

		void addTexture(const string& fileName, Texture texture) {
			tMap[fileName] = texture;
		}

	private:
		unordered_map<string, Texture> tMap;
	};

}

