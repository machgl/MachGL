#version 330 core

layout (location = 0) out vec4 color;

in DATA {

	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	
} fs_in;

uniform sampler2D _texture;
uniform float _gamma = 2.2;
uniform float _exposure = 0.1;

void main() {

	vec3 hdrColor = texture(_texture, fs_in.uv).rgb;
	vec3 mapped = vec3(1.0) - exp(-hdrColor * _exposure);
	mapped = pow(mapped, vec3(1.0 / _gamma));
	color = vec4(mapped, 1.0);
}