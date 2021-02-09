#version 330 core

layout (location = 0) out vec4 color;

in vec3 texCoords;

uniform samplerCube _skybox[2];
uniform int _skyboxes = 1;
uniform float _blendFactor = 0.5;

void main() {
	
	vec3 uv = vec3(texCoords.x, -texCoords.y, texCoords.z);

	if (_skyboxes == 2) {

		vec4 texture1 = texture(_skybox[0], uv);
		vec4 texture2 = texture(_skybox[1], uv);
		color = mix(texture1, texture2, _blendFactor);

	} else {

		color = texture(_skybox[0], uv);
	}

}