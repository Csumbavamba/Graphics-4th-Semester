#version 450 core

in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;

void main (void)
{
    // vec4 fragColor = texture(tex, fragTexCoord);
    color = texture(tex, fragTexCoord);
}