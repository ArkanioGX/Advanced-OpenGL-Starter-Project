#version 330 core
in vec2 TexCoord;
in vec4 OurColor;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(0.1,0.5,0.9,1.0);
}