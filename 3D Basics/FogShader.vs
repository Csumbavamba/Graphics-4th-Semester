#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; 
layout (location = 2) in vec2 texCoord;

out vec2 fragTexCoord;
out vec4 worldPosition;

uniform mat4 PVM;
uniform mat4 model;


void main(void)
{
	vec4 worldPosition = model * vec4(position, 1.0);

	// gl_Position = projection * view * worldPosition;
	gl_Position = PVM * vec4(position, 1.0f);



	fragTexCoord = texCoord;
}