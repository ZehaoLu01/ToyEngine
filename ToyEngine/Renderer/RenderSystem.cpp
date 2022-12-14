#include <iostream>
#include <sstream>
#include <fstream>
#include "Renderer/RenderSystem.h"
#include "Resource/StbImageLoader.h"
#include "Resource/Texture.h"
#include <Resource/stb_image.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/RenderComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ImGuiMenu.h"

namespace ToyEngine {
	const glm::vec3 LIGHT_BULB_POSITION(5.0f, 5.0f, 5.0f);

	const glm::vec3 PHONG_TESTING_POSITION(0.f, 0.f, 2.f);
	const glm::vec3 PHONG_AMBIENT_COLOR(0.2f, 0.2f, 0.2f);
	const glm::vec3 PHONG_DIFFUSE_COLOR(1.0f, 0.0f, 0.0f);
	const glm::vec3 PHONG_SPECULAR_COLOR(1.0f, 1.0f, 1.0f);



	const glm::vec3 BLINN_PHONG_TESTING_POSITION(2.f, 0.f, 0.f);
	const glm::vec3 BLINN_PHONG_AMBIENT_COLOR(0.2f, 0.2f, 0.2f);
	const glm::vec3 BLINN_PHONG_DIFFUSE_COLOR(0.0f, 1.0f, 0.0f);
	const glm::vec3 BLINN_PHONG_SPECULAR_COLOR(1.0f, 1.0f, 1.0f);


	GLenum convertChannelsToFormat(unsigned int channels) {
		GLenum format = GL_NONE;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile("path", aiProcess_Triangulate | aiProcess_FlipUVs);
		return format;
	}

	void RenderSystem::tick()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto component : mRenderComponents) {
			component->tick();
		}

		ImGuiMenu::tick();

		glfwSwapBuffers(mWindow.get());
		glfwPollEvents();
	}

	void RenderSystem::init(WindowPtr window, std::shared_ptr<Camera> camera) {
		mWindow = window;
		mCamera = camera;
		glEnable(GL_DEPTH_TEST);

		std::vector<Texture> textureVec;

		auto vertexDataPtr = std::make_unique<std::vector<float>>();

		auto indicesDataPtr = std::make_unique<std::vector<unsigned int>>();

		auto shaderPtr = std::make_shared<Shader>("Shaders/BlinnPhong.vs.glsl", "Shaders/BlinnPhong.fs.glsl");

		Texture processedTextureData;

		// ========================================================


		// light bulb
		// ========================================================
		vertexDataPtr = std::make_unique<std::vector<float>>();
		*vertexDataPtr = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f
		};

		shaderPtr = std::make_shared<Shader>("Shaders/VertexShader.glsl", "Shaders/LightFragmentShader.glsl");
		shaderPtr->use();
		shaderPtr->setUniform("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderPtr->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		indicesDataPtr.reset();
		processedTextureData = Texture();

		textureVec.clear();

		auto lightBulb = std::make_shared<RenderComponent>(std::move(vertexDataPtr), std::move(indicesDataPtr), textureVec, shaderPtr, mWindow, mCamera);
		lightBulb->init();
		lightBulb->setWorldPosition(LIGHT_BULB_POSITION);
		lightBulb->setSpotLight(true);
		mRenderComponents.push_back(lightBulb);


		shaderPtr = std::make_shared<Shader>("Shaders/BlinnPhong.vs.glsl", "Shaders/BlinnPhong.fs.glsl");
		shaderPtr->use();
		shaderPtr->setUniform("spherePosition", LIGHT_BULB_POSITION);
		shaderPtr->setUniform("ambientColor", BLINN_PHONG_AMBIENT_COLOR);
		shaderPtr->setUniform("diffuseColor", BLINN_PHONG_DIFFUSE_COLOR);
		shaderPtr->setUniform("specularColor", BLINN_PHONG_SPECULAR_COLOR);
		shaderPtr->setUniform("kAmbient", 0.3f);
		shaderPtr->setUniform("kDiffuse", 0.6f);
		shaderPtr->setUniform("kSpecular", 1.0f);
		shaderPtr->setUniform("shininess", 10.0f);
		// Complex model
		loadModel("D:/Repo/ToyEngine/ToyEngine/Resources/model/backpack.obj", shaderPtr);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(mWindow.get(), true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void RenderSystem::loadModel(std::string path, std::shared_ptr<Shader> shader)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return;
		}
		mDirectory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene, shader);
	}

	void RenderSystem::processNode(aiNode* node, const aiScene* scene, std::shared_ptr<Shader> shader)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			mRenderComponents.push_back(processMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, shader);
		}
	}

	std::shared_ptr<RenderComponent> RenderSystem::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			// process vertex positions, normals and texture coordinates
			//...
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}
		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		
		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// 1. diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			//// 3. normal maps
			//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			//// 4. height maps
			//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}

		std::shared_ptr<Shader> shaderPtr = std::make_shared<Shader>("Shaders/phong.vs.glsl", "Shaders/phong.fs.glsl");
		shaderPtr->use();
		shaderPtr->setUniform("spherePosition", LIGHT_BULB_POSITION);
		shaderPtr->setUniform("ambientColor", PHONG_AMBIENT_COLOR);
		shaderPtr->setUniform("diffuseColor", PHONG_DIFFUSE_COLOR);
		shaderPtr->setUniform("specularColor", PHONG_SPECULAR_COLOR);
		shaderPtr->setUniform("kAmbient", 0.3f);
		shaderPtr->setUniform("kDiffuse", 0.6f);
		shaderPtr->setUniform("kSpecular", 1.0f);
		shaderPtr->setUniform("shininess", 10.0f);

		auto retPtr = std::make_shared<RenderComponent>(vertices, indices, textures, shaderPtr, mWindow, mCamera);
		retPtr->setNormalAvailability(true);
		retPtr->init();

		return retPtr;
	}

	std::vector<Texture> RenderSystem::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{

			bool skip = false;
			aiString str;
			mat->GetTexture(type, i, &str);
			std::string str_cpp(str.C_Str());
			for (unsigned int j = 0; j < mLoadedTextures.size(); j++)
			{
				if (std::strcmp(mLoadedTextures[j].getPath().data(), str.C_Str()) == 0)
				{
					textures.push_back(mLoadedTextures[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				int width;
				int height;
				int channels;
				auto textureData = StbImageLoader::getImageFrom(str_cpp, &width, &height, &channels);
				auto format = convertChannelsToFormat(channels);
				TextureType textureType = ConvertTextureType(type);
				Texture texture(textureData, width, height, format, format, 0, textureType);
				texture.setPath(str_cpp);
				textures.push_back(texture);
				mLoadedTextures.push_back(texture);
			}
		}
		return textures;
	}

	TextureType RenderSystem::ConvertTextureType(aiTextureType type)
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
			break;
		case aiTextureType_EMISSIVE:
			break;
		case aiTextureType_HEIGHT:
			break;
		case aiTextureType_NORMALS:
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
		return TextureType::Diffuse;
	}

	GLenum RenderSystem::convertChannelsToFormat(unsigned int channels) {
		GLenum format = GL_NONE;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile("path", aiProcess_Triangulate | aiProcess_FlipUVs);
		return format;
	}

	// Update All the render components from imgui menu.
	void RenderSystem::updateComponentsProperties() {
		for (auto c : mRenderComponents) {
			if (!c->isSpotLight()) {
				c->updateProperties();
			}
		}
	}
}
