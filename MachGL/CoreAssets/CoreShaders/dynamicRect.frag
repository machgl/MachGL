#version 330 core

layout (location = 0) out vec4 color;

in DATA {

	vec4 position;
	vec2 uv;
	vec4 color;

} fs_in;

uniform sampler2D _dynamicTexture;

void main() {

	vec4 outputColor = fs_in.color;

	outputColor = texture(_dynamicTexture, fs_in.uv);

	color = outputColor;
}