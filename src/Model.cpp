#include "../include/Model.h"
#include "../include/stb/stb_image.h"
Model::Model(string const &path, bool gamma) : gammaCorrection(gamma) {
	Model::name = path;
	Model::path = path.substr(0,path.find_last_of('/')+1);
	loadModel(path);
}
void Model::render(Shader &shader, Camera &camera) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].render(shader, camera);
}

void  Model::rotate(float theta, axis a) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].rotate(theta, a);
}

void  Model::translate(float displacement, axis a) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].translate(displacement, a);
}

void Model::setScale(float scale) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].setScale(scale);
}

void Model::loadModel(string const &path) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
	vector<Vertex> vertices;
	vector<Texture> textures_loaded;
	vector<unsigned int> indices;
	vector<Texture> textures;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.pos = vector;
		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.y = mesh->mTextureCoords[0][i].x;
			vec.x = mesh->mTextureCoords[0][i].y;
			vertex.texture = vec;
		}
		else
			vertex.texture = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	vector<Texture> diffuseMaps;
	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
		aiString str;
		material->GetTexture(aiTextureType_DIFFUSE, i, &str);
		string nameAndPath = path + str.C_Str();
		const char *texName = nameAndPath.c_str();
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(texNames[j].c_str(), texName) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture(texName, "diffuse", i);
			texNames.push_back(texName);
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	vector<Texture> specularMaps;
	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++) {
		aiString str;
		material->GetTexture(aiTextureType_SPECULAR, i, &str);
		string nameAndPath = path + str.C_Str();
		const char *texName = nameAndPath.c_str();
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(texNames[j].c_str(), texName) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture(texName, "specular", i);
			texNames.push_back(texName);
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	return Mesh(vertices, indices, textures);
}