#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;
out vec3 ourColor;

void main()
{
	//Values to make the figure's dynamic
	float dynamicX= sin(xOffset)/4.0f;
	float dynamicY= sin(xOffset)/4.0f;
	gl_Position = vec4(aPos.x - dynamicX, aPos.y + dynamicY, aPos.z, 1.0);
	ourColor = aColor;
}
