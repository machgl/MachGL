#version 330 core

layout (location = 0) out vec4 color;

in DATA {

	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;

} fs_in;

uniform sampler2D _simple_TIDs[32];
uniform float _simple_alpha;

void main() {
	
	vec4 texColor = fs_in.color;

	if (fs_in.tid > 0.0) {
			
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(_simple_TIDs[tid], fs_in.uv);
	}

	vec4 outputColor = vec4(0.0);

	if (texColor != vec4(1, 0, 1, 1)) {

		outputColor = vec4(texColor.x, texColor.y, texColor.z, _simple_alpha);	
	}

	color = outputColor;	
}