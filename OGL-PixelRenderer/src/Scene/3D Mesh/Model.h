#pragma once

#include <vector>
#include "Mesh.h"
#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../OpenGL/Shaders/ShaderProgram.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Cameras/Camera.h"

#include <unordered_map>

class Model : public PR_PropertyDef
{
public:
	Model(const char* path, const char* vert, const char* frag);
	~Model();

	void BeginProperty() override;
	void Draw(Camera* cam);

	glm::mat4* ModelMatrix();

protected:
	std::unordered_map<std::string, Material*> matMap; // map with existing materials

	ShaderProgram* _shader = nullptr;

	std::vector<Mesh*> _meshes;

	glm::vec3 _position = glm::vec3(0);
	glm::vec3 _rotation = glm::vec3(0);
	glm::vec3 _scale = glm::vec3(1);
	
	glm::mat4 _model;

	// temp function
	bool LoadFromFile(const char *path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, aiNode* node, const aiScene* scene);
};

