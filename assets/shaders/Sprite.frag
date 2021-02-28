#version 330 core

in vec2 texCoords;

uniform sampler2D u_Tex;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Tex, texCoords);
	if(FragColor.w < 1)
		discard;
};