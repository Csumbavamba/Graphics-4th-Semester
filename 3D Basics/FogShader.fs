#version 450 core

in vec2 fragTexCoord;
in vec4 worldPosition;

out vec4 color;

uniform sampler2D tex;
uniform vec3 camPos;


void main (void)
{

	vec3 tempCamPos = vec3(0.0f, 0.0f, 10.0f);

	float distanceToCamera = distance(worldPosition.xyz, tempCamPos);

	float fogMaxDistance = 15.0f;
	float fogMinDistance = 1.0f;
	vec4 fogColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);

	float lerp = (distanceToCamera - fogMinDistance) / fogMaxDistance;
	lerp = clamp(lerp, 0.0f, 1.0f);

	vec4 textureColor = texture(tex, fragTexCoord);

	color = mix(textureColor, fogColor, lerp);

}