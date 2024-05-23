#pragma once
#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "Shadder.h"
#include "Material.h"
#include "OBJLoader.h"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void UpdateUniforms();

public:
	Model(glm::vec3 position,Material* material,
		Texture* overrideTexDiff,
		Texture* overrideTexSpec,
		std::vector<Mesh*>meshes);

	Model(glm::vec3 position, Material* material,
		Texture* overrideTexDiff,
		Texture* overrideTexSpec,
		const char* objFile);
	~Model();
	void Rotate(const glm::vec3 rotation);
	void Move(const glm::vec3 direction);
	void SetPosition(const glm::vec3 position);
	void SetMatrix(glm::mat4 Matrix);

	void Update();
	void Render(shader* shader);
};
