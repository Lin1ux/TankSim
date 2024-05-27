#version 330

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

//interpolarne
in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms 
uniform Material material;


uniform vec3 lightPos0;
uniform vec3 lightPos1;
uniform vec3 cameraPos;

//Funkcje
//�wiat�o otoczenia
vec3 calculateAmbient(Material material)
{
	return vec3(1.0f) * clamp(dot(normalize(vs_normal), normalize(lightPos0)), 0, 1);
}

//�wiat�o rozproszone
vec3 calculateDiffuse(Material material,vec3 vs_position,vec3 vs_normal,vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float distance =  length(lightPos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec,vs_normal),0,1);
	
	//vec3 color = vec3(1.0,0.7,0.1);		//Pomara�czowy
	vec3 color = vec3(1.0,0.5,0.0);		//Pomara�czowy
	//vec3 color = vec3(0.0,0.0,1.0);
	vec3 diffuseFinal = material.diffuse * diffuse * (1/(distance/10)) * color;

	return diffuseFinal;
}

//�wiat�o lustrzane
vec3 calculateSpecular(Material material,vec3 vs_position,vec3 vs_normal,vec3 lightPos0,vec3 cameraPos)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec,normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec,reflectDirVec),0),35);
	vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex,vs_texcord).rgb;

	return specularFinal;
}
void main()
{	
	//�wiat�o otoczenia
	vec3 ambientFinal = calculateAmbient(material);


	//�wat�o rozproszone
	vec3 diffuseFinal = calculateDiffuse(material,vs_position,vs_normal,lightPos1);
	

	//�wiat�o lustrzane
	vec3 specularFinal = calculateSpecular(material,vs_position,vs_normal,lightPos0,cameraPos);


	//Ostateczne �wiat�o
	fs_color = texture(material.diffuseTex, vs_texcord) * (vec4(ambientFinal,1.0f) + vec4(diffuseFinal,1.0f) + vec4(specularFinal,1.0f));
}