#include "Model.h"

Model::Model(const GLchar *path) {
	this->loadModel(path);
}

void Model::draw(Shader shader) {
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		this->meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path) {
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		// The node object only contains indices to index the actual objects in the scene.
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
// Data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		// Does the mesh contain texture coordinates?
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		} else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// Process materials
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		const char *textureType = connectField(MATERIAL, DIFFUSE);
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE,
																	  textureType);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		textureType = connectField(MATERIAL, SPECULAR);
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR,
																	   textureType);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;

		std::string fullPath = this->directory + '/' + std::string(str.C_Str());
		aiString aifp = aiString(fullPath);
		for (GLuint j = 0; j < textures_loaded.size(); j++) {
			if (textures_loaded[j].getPath() == aifp) {
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)

				break;
			}
		}

		if (!skip) {   // If texture hasn't been loaded already, load it
			Texture texture = Texture::load(fullPath);
			texture.setType(typeName);
			textures.push_back(texture);
			// Store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
			this->textures_loaded.push_back(texture);
		}
	}

	return textures;
}
