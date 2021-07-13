#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;
//layout (location = 3) in vec3 aNormal;

out vec2 TexCoord;
out vec3 ourColor;
//out vec3 Normal;
//out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 model = mat4(1.0);
	gl_Position = projection * view * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	ourColor = aColor;
	//FragPos = aPos;
	//Normal = aNormal;
}