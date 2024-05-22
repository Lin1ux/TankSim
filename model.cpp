#include "model.h"

void Model::UpdateUniforms()
{
}

Model::Model(glm::vec3 position, Material* material, Texture* overrideTexDiff, Texture* overrideTexSpec, std::vector<Mesh*> meshes)
{
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = overrideTexDiff;
	this->overrideTextureSpecular = overrideTexSpec;
	for (auto* i : meshes)
	{
		this->meshes.push_back(new Mesh(*i));
	}

	for (auto*& i : this->meshes)
	{
		i->Move(this->position);
		i->SetOrigin(this->position);
	}
}

Model::~Model()
{
	for (auto*& i : this->meshes)
	{
		delete i;
	}
}

void Model::Rotate(const glm::vec3 rotation)
{
	for (auto& i : this->meshes)
	{
		i->Rotate(rotation);
	}
}

void Model::Update()
{
}

void Model::Render(shader* shader)
{
	this->UpdateUniforms();

	//Aktualizowanie uniformów (wysyłanie do karty graficznej
	this->UpdateUniforms();

	this->material->sendToShader(*shader);

	shader->use();

	//Aktywacja textur
	this->overrideTextureDiffuse->bind(0);	//Diffuse texture
	this->overrideTextureSpecular->bind(1);	//Specular texture

	//Rysowanie
	for (auto& i : this->meshes)
	{
		i->render(shader);

	}


	//Aktywacja textur
	//this->Textures[TEXTURE_BRICKS0]->bind(0);	//Diffuse texture
	//this->Textures[TEXTURE_BRICKS_SPEC]->bind(1);	//Specular texture

	//this->Meshes[1]->render(this->Shaders[SHADER_CORE_PROGRAM]);

}
