#include "Utils/RenderHelper.h"
#include <Utils/Logger.h>

ToyEngine::TextureType ToyEngine::RenderHelper::ConvertTextureType(aiTextureType type)
{
	{
		switch (type)
		{
		case aiTextureType_NONE:
			break;
		case aiTextureType_DIFFUSE:
			return TextureType::Diffuse;
			break;
		case aiTextureType_SPECULAR:
			return TextureType::Specular;
			break;
		case aiTextureType_AMBIENT:
			return TextureType::Ambient;
			break;
		case aiTextureType_EMISSIVE:
			break;
		case aiTextureType_HEIGHT:
			return TextureType::Height;
			break;
		case aiTextureType_NORMALS:
			return TextureType::Normal;
			break;
		case aiTextureType_SHININESS:
			break;
		case aiTextureType_OPACITY:
			break;
		case aiTextureType_DISPLACEMENT:
			break;
		case aiTextureType_LIGHTMAP:
			break;
		case aiTextureType_REFLECTION:
			break;
		case aiTextureType_BASE_COLOR:
			break;
		case aiTextureType_NORMAL_CAMERA:
			break;
		case aiTextureType_EMISSION_COLOR:
			break;
		case aiTextureType_METALNESS:
			break;
		case aiTextureType_DIFFUSE_ROUGHNESS:
			break;
		case aiTextureType_AMBIENT_OCCLUSION:
			break;
		case aiTextureType_SHEEN:
			break;
		case aiTextureType_CLEARCOAT:
			break;
		case aiTextureType_TRANSMISSION:
			break;
		case aiTextureType_UNKNOWN:
			break;
		case _aiTextureType_Force32Bit:
			break;
		default:
			break;
		}
		Logger::DEBUG_ERROR("Unknown texture type: " + type);
		return TextureType::UNKNOWN;
	}
}

std::string ToyEngine::RenderHelper::getTextureTypeString(aiTextureType type)
{
	switch (type)
	{
	case aiTextureType_NONE:
		return "None";
		break;
	case aiTextureType_DIFFUSE:
		return "Diffuse";
		break;
	case aiTextureType_SPECULAR:
		return "Specular";
		break;
	case aiTextureType_AMBIENT:
		return "Ambient";
		break;
	case aiTextureType_EMISSIVE:
		return "Emissive";
		break;
	case aiTextureType_HEIGHT:
		return "Height";
		break;
	case aiTextureType_NORMALS:
		return "Normals";
		break;
	case aiTextureType_SHININESS:
		return "Shininess";
		break;
	case aiTextureType_OPACITY:
		return "Opacity";
		break;
	case aiTextureType_DISPLACEMENT:
		break;
	case aiTextureType_LIGHTMAP:
		return "LightMap";
		break;
	case aiTextureType_REFLECTION:
		return "Reflection";
		break;
	case aiTextureType_BASE_COLOR:
		return "Base Color";
		break;
	case aiTextureType_NORMAL_CAMERA:
		break;
	case aiTextureType_EMISSION_COLOR:
		break;
	case aiTextureType_METALNESS:
		break;
	case aiTextureType_DIFFUSE_ROUGHNESS:
		break;
	case aiTextureType_AMBIENT_OCCLUSION:
		break;
	case aiTextureType_SHEEN:
		break;
	case aiTextureType_CLEARCOAT:
		break;
	case aiTextureType_TRANSMISSION:
		break;
	case aiTextureType_UNKNOWN:
		break;
	case _aiTextureType_Force32Bit:
		break;
	default:
		Logger::DEBUG_ERROR("Trying to convert unknown texture type to string!");
	}
		
	
}
