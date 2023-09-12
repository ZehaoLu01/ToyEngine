// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <sstream>
#include <fstream>
#include <Renderer/RenderSystem.h>
#include <Resource/StbImageLoader.h>
#include <Resource/Texture.h>
#include <Resource/stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include <Engine/Component.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <entt/entity/registry.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UI/View/ImGuiMenu.h"
#include <Renderer/Line.h>
#include <UI/Controller/PropertiesScreenController.h>

#define SELF_ROTATION 0

namespace ToyEngine {
	RenderSystem RenderSystem::instance = RenderSystem();

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

	void RenderSystem::afterDraw()
	{
		glfwSwapBuffers(mWindow.get());
		glfwPollEvents();
	}

	void RenderSystem::preDraw()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderSystem::drawGridLine()
	{
		glm::mat4 projection = glm::perspective(glm::radians(mCamera->mZoom), 1920.0f / 1080.0f, 0.1f, 100.0f);

		glUseProgram(mGridShader->ID);
		glm::highp_mat4 mvp = projection * mCamera->GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mGridShader->ID, "MVP"), 1, GL_FALSE, &mvp[0][0]);
		glUniform3fv(glGetUniformLocation(mGridShader->ID, "color"), 1, &mGridLineColor[0]);
		glBindVertexArray(mGridVAOIndex);
		glDrawArrays(GL_LINES, 0, mGridPoints.size());

	}

	void RenderSystem::drawCoordinateIndicator(glm::vec3 position)
	{
		glm::mat4 projection = glm::perspective(glm::radians(mCamera->mZoom), 1920.0f / 1080.0f, 0.1f, 100.0f);

		Line lineX = Line(position, position + glm::vec3(1, 0, 0));
		lineX.setMVP(projection * mCamera->GetViewMatrix());
		lineX.setColor(vec3(255, 0, 0));
		lineX.draw();
		Line lineY = Line(position, position + glm::vec3(0, 1, 0));
		lineY.setMVP(projection * mCamera->GetViewMatrix());
		lineY.setColor(vec3(0, 0, 255));
		lineY.draw();
		Line lineZ = Line(position, position + glm::vec3(0, 0, 1));
		lineZ.setMVP(projection * mCamera->GetViewMatrix());
		lineZ.setColor(vec3(0, 255, 0));
		lineZ.draw();
	}

	void RenderSystem::drawMesh(const TransformComponent& transform, const MeshComponent& mesh, TextureComponent texture)
	{	
		auto textures = texture.textures;

		mesh.shader->use();

		unsigned int diffuseNr = 0;
		unsigned int specularNr = 0;
		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].getTypeName();
			if (name == "diffuse") {
				name = "texture_diffuse";
				number = std::to_string(diffuseNr++);
			}
			else if (name == "specular") {
				name = "texture_specular";
				number = std::to_string(specularNr++);
			}
			mesh.shader->setUniform(name + number, i);
			glBindTexture(GL_TEXTURE_2D, textures[i].getTextureIndex());
		}
		glActiveTexture(GL_TEXTURE0);

		auto model = glm::mat4(1.0f);

		glm::vec3 worldPos;
		glm::vec3 rotation;
		glm::vec3 scale;
		if (transform.isReference&&transform.referencedTransform) {
			worldPos = transform.referencedTransform->worldPos;
		}

		if (SELF_ROTATION) {
			// rotation need to be improved
			auto model_rotate = glm::rotate(model, (float)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			auto model_translate = glm::translate(model, transform.worldPos);
			model = model_translate * model_rotate;
		}
		else {
			auto model_translate = glm::translate(model, transform.worldPos);
			auto model_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation_eular.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model_rotate = glm::rotate(model_rotate, glm::radians(transform.rotation_eular.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model_rotate = glm::rotate(model_rotate, glm::radians(transform.rotation_eular.z), glm::vec3(0.0f, 0.0f, 1.0f));

			model = glm::scale(model_translate * model_rotate, transform.scale);
		}
		mesh.shader->setUniform("model", model);

		auto view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = mCamera->GetViewMatrix();
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
		mesh.shader->setUniform("view", view);

		mesh.shader->setUniform("normalMat", glm::transpose(glm::inverse(view * model)));

		auto projection = glm::mat4(1);
		projection = glm::perspective(glm::radians(mCamera->mZoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		mesh.shader->setUniform("projection", projection);

		glBindVertexArray(mesh.VAOIndex);
		glDrawElements(GL_TRIANGLES, mesh.vertexSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void RenderSystem::drawImGuiMenu()
	{
		ui::ImGuiMenu::getInstance().tick();
	}

	void RenderSystem::initGrid()
	{
		mGridShader = std::make_shared<Shader>("Shaders/GridVertex.glsl", "Shaders/GridFragment.glsl");

		const int gridWidth = 500;
		const int gridHeight = 500;
		constexpr int pointNum = 2 * (gridWidth + 1 + gridHeight + 1);
		mGridPoints.reserve(pointNum * 3);
		for (int i = -gridWidth / 2; i < gridWidth / 2 + 1; i++) {
			mGridPoints.push_back(i);
			mGridPoints.push_back(0);
			mGridPoints.push_back(-gridWidth / 2);
			mGridPoints.push_back(i);
			mGridPoints.push_back(0);
			mGridPoints.push_back(gridWidth / 2);
		}
		for (int i = -gridWidth / 2; i < gridWidth / 2 + 1; i++) {
			mGridPoints.push_back(-gridWidth / 2);
			mGridPoints.push_back(0);
			mGridPoints.push_back(i);
			mGridPoints.push_back(gridWidth / 2);
			mGridPoints.push_back(0);
			mGridPoints.push_back(i);
		}

		glGenVertexArrays(1, &mGridVAOIndex);
		glGenBuffers(1, &mGridVBOIndex);
		glBindVertexArray(mGridVAOIndex);
		glBindBuffer(GL_ARRAY_BUFFER, mGridVBOIndex);
		glBufferData(GL_ARRAY_BUFFER, mGridPoints.size() * sizeof(float), mGridPoints.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	// Setup active shader, camera, window.
	void RenderSystem::init(WindowPtr window, std::shared_ptr<Camera> camera, std::shared_ptr<MyScene> scene) {
		mWindow = window;
		mCamera = camera;
		glEnable(GL_DEPTH_TEST);

		auto shaderPtr = std::make_shared<Shader>("Shaders/BlinnPhong.vs.glsl", "Shaders/BlinnPhong.fs.glsl");

		initGrid();

		//===========================================================
		// Complex model
		mActiveShader = std::make_shared<Shader>("Shaders/BlinnPhong.vs.glsl", "Shaders/BlinnPhong.fs.glsl");
		mActiveShader->use();
		mActiveShader->setUniform("spherePosition", LIGHT_BULB_POSITION);
		mActiveShader->setUniform("ambientColor", BLINN_PHONG_AMBIENT_COLOR);
		mActiveShader->setUniform("diffuseColor", BLINN_PHONG_DIFFUSE_COLOR);
		mActiveShader->setUniform("specularColor", BLINN_PHONG_SPECULAR_COLOR);
		mActiveShader->setUniform("kAmbient", 0.3f);
		mActiveShader->setUniform("kDiffuse", 0.6f);
		mActiveShader->setUniform("kSpecular", 1.0f);
		mActiveShader->setUniform("shininess", 10.0f);

		//ImGui
		setupImGUI();
		auto propertiesScreenController = std::make_shared<ui::PropertiesScreenController>(scene->getRegistry());
		ui::ImGuiMenu::getInstance().setupControllers(scene);
	}

	void RenderSystem::setupImGUI()
	{
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

	entt::entity RenderSystem::loadModel(std::string path, std::string modelName, entt::registry& registry, entt::entity parent, const TransformComponent& transform)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return entt::null;
		}

		mDirectory = path.substr(0, path.find_last_of('/'));

		entt::entity entity = registry.create();

		auto& newTrasnform = registry.emplace<TransformComponent>(entity, transform);

		auto child = processNode(scene->mRootNode, scene, registry, entity, newTrasnform);
		//TODO: PRE, NEXT
		auto& relation = registry.emplace<RelationComponent>(entity, parent, std::make_shared<std::vector<entt::entity>>());
		if (modelName.size() == 0) {
			registry.emplace<TagComponent>(entity, "default model");
		}
		else {
			registry.emplace<TagComponent>(entity, modelName);
		}
		relation.children->push_back(child);
		return entity;
	}

	void RenderSystem::bindSiblings(entt::registry& registry, entt::entity curr, entt::entity& prev)
	{
		if (prev != entt::null) {
			auto childRelation = registry.get<RelationComponent>(curr);
			auto prevRelation = registry.get<RelationComponent>(prev);

			registry.get<RelationComponent>(curr).prev = prev;
			registry.get<RelationComponent>(prev).next = curr;
		}
		prev = curr;
	}

	entt::entity RenderSystem::processNode(aiNode* node, const aiScene* scene, entt::registry& registry, entt::entity parent, const TransformComponent& parentTransform)
	{
		entt::entity entity = registry.create();
		std::shared_ptr<std::vector<Vertex>> verticesPtr;
		std::shared_ptr<std::vector<unsigned int>> indicesPtr;
		auto& relation = registry.emplace<RelationComponent>(entity, parent, std::make_shared<vector<entt::entity>>());
		auto& transform = registry.emplace<TransformComponent>(entity, parentTransform);

		entt::entity prev = entt::null;

		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			auto child = processMesh(mesh, scene, registry, entity, transform);

			bindSiblings(registry, child, prev);

			prev = child;
			relation.children->push_back(child);
		}

		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			auto child = processNode(node->mChildren[i], scene, registry, entity, transform);

			bindSiblings(registry, child, prev);

			prev = child;
			relation.children->push_back(child);
		}
		return entity;
	}

	entt::entity RenderSystem::processMesh(aiMesh* mesh, const aiScene* scene, entt::registry& registry, entt::entity parent, const TransformComponent& parentTransform)
	{
		entt::entity entity =  registry.create();

		VertexDataPtr verticesPtr = std::make_shared<VertexData>();
		IndexDataPtr indicesPtr = std::make_shared<IndexData>();

		std::vector<Texture> textures;

		bool hasNormal = false;
		bool hasTexture = false;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			//...
			verticesPtr->push_back(mesh->mVertices[i].x);
			verticesPtr->push_back(mesh->mVertices[i].y);
			verticesPtr->push_back(mesh->mVertices[i].z);
			if (mesh->HasNormals())
			{
				hasNormal = true;
				verticesPtr->push_back(mesh->mNormals[i].x);
				verticesPtr->push_back(mesh->mNormals[i].y);
				verticesPtr->push_back(mesh->mNormals[i].z);
			}
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				hasTexture = true;
				verticesPtr->push_back(mesh->mTextureCoords[0][i].x);
				verticesPtr->push_back(mesh->mTextureCoords[0][i].y);
			}
		}

		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indicesPtr->push_back(face.mIndices[j]);
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


		// TODO USE ACTIVE SHADER
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

		registry.emplace<TransformComponent>(entity, parentTransform);
		registry.emplace<MeshComponent>(entity, verticesPtr,indicesPtr,shaderPtr, hasNormal, hasTexture);
		registry.emplace<TextureComponent>(entity, textures);
		registry.emplace<RelationComponent>(entity, parent, std::make_shared<vector<entt::entity>>());

		return entity;
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
}
