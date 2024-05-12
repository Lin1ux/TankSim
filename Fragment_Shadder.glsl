#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;


uniform vec3 lightPos0;
uniform vec3 cameraPos;

void main()
{
	//fs_color = vec4(vs_color,1.0f);
	//fs_color = texture(texture0, vs_texcord) * vec4(vs_color,1.0f) + texture(texture1, vs_texcord) * vec4(vs_color,1.0f);
	
	//�wiat�o otoczenia
	vec3 ambientLight = material.ambient;


	//�wat�o rozproszone
	vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
	float diffuse = clamp(dot(posToLightDirVec,vs_normal),0,1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	//�wiat�o lustrzane
	vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec,normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	float specularConstant = pow(max(dot(posToViewDirVec,reflectDirVec),0),30);
	vec3 specularFinal = material.specular * specularConstant;


	//Os�abienie


	//Ostateczne �wiat�o
	//vec4(vs_color,1.0f)
	fs_color = texture(material.diffuseTex, vs_texcord)
	* (vec4(ambientLight,1.0f) + vec4(diffuseFinal,1.0f) + vec4(specularFinal,1.0f));
}