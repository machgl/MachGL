#version 330 core

layout (location = 0) out vec4 color;

in DATA {

	vec4 position;
	vec2 uv;
	vec4 color;

} fs_in;

uniform sampler2D _tex;
uniform float _time;

void main() {
	
	color = fs_in.color;

	if (_time > 2) {
		
		float alpha = 3 - _time;

		color = vec4(1.0f, 1.0f, 1.0f, alpha) * texture(_tex, fs_in.uv);

	} else {

		color = texture(_tex, fs_in.uv);
	}
}