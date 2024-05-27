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

Model::Model(glm::vec3 position, Material* material, Texture* overrideTexDiff, Texture* overrideTexSpec, const char* objFile)
{
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = overrideTexDiff;
	this->overrideTextureSpecular = overrideTexSpec;

	std::vector<Vertex> mesh = OBJModel::loadOBJ(objFile);
	this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(1.0f)
	));

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

void Model::Move(const glm::vec3 direction)
{
	for (auto& i : this->meshes)
	{
		i->Move(direction);
	}
}

void Model::SetPosition(const glm::vec3 position)
{
	for (auto& i : this->meshes)
	{
		i->SetPosition(position);
	}
}

void Model::Scale(const glm::vec3 scale)
{
	for (auto& i : this->meshes)
	{
		i->SetScale(scale);
	}
}

void Model::SetMatrix(glm::mat4 Matrix)
{
	for (auto& i : this->meshes)
	{
		i->SetModelMatrix(Matrix,false);
	}
}

void Model::SetColor(glm::vec3 color)
{
	for (auto& i : this->meshes)
	{
		i->SetColor(color);
	}
}

void Model::RenderColor(bool OnlyColor)
{
	for (auto& i : this->meshes)
	{
		i->RenderColor(OnlyColor);
	}
}

glm::mat4 Model::GetMatrix(int index)
{
	return meshes[index]->GetMatrix();
}

glm::vec3 Model::GetPosition(int index)
{
	return meshes[index]->GetMatrix()[3];
}

void Model::Update()
{
}

void Model::Render(shader* shader)
{
	//this->UpdateUniforms();

	//Aktualizowanie uniformów (wysyłanie do karty graficznej
	//this->UpdateUniforms();

	this->material->sendToShader(*shader);

	shader->use();

	//Aktywacja textur

	//Rysowanie
	for (auto& i : this->meshes)
	{
		this->overrideTextureDiffuse->bind(0);	//Diffuse texture
		this->overrideTextureSpecular->bind(1);	//Specular texture
		
		i->render(shader);

	}


	//Aktywacja textur
	//this->Textures[TEXTURE_BRICKS0]->bind(0);	//Diffuse texture
	//this->Textures[TEXTURE_BRICKS_SPEC]->bind(1);	//Specular texture

	//this->Meshes[1]->render(this->Shaders[SHADER_CORE_PROGRAM]);

}
