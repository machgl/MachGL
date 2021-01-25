#version 330 core

layout (location = 0) out vec4 color;

in vec3 texCoords;

uniform samplerCube _skybox;

void main() {
	
	vec3 uv = vec3(texCoords.x, -texCoords.y, texCoords.z);

	color = texture(_skybox, uv);
}