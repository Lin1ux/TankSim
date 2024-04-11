#version 330

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcord;

out vec4 fs_color;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	//fs_color = vec4(vs_color,1.0f);
	fs_color = texture(texture0, vs_texcord) * vec4(vs_color,1.0f) + texture(texture1, vs_texcord) * vec4(vs_color,1.0f);
	//fs_color = texture(texture0, vs_texcord) * vec4(vs_color,1.0f);
}