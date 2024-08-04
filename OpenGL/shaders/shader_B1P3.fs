#version 330 core
out vec4 FragColor;
in vec3 ourColor;
//Variable Uniform
uniform float time;
void main()
{
	//Values to make the figure's colors dynamic
	float dynamicRed = (sin(time) / 2.0f) + 0.5f;
	float dynamicGreen = (cos(time) / 2.0f) + 0.5f;
	float dynamicBlue = ((sin(time)*cos(time)) / 2.0f) + 1.0f;

	FragColor = vec4(ourColor.x/dynamicRed,ourColor.y,ourColor.z*dynamicBlue,1.0f);
}