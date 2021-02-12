#version 330 core

layout (location = 0) out vec4 color;
layout (origin_upper_left) in vec4 gl_FragCoord;

in DATA {

	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	float radius;

} fs_in;

uniform sampler2D _simple_TIDs[32];
uniform float _simple_alpha;

void main() {
	
	if (fs_in.radius > 0) {
		
		vec2 pos = mod(gl_FragCoord.xy, fs_in.radius * 2) - fs_in.radius;
		float dist = dot(pos, pos);

		if (dist > fs_in.radius * fs_in.radius) {
			discard;
		}
	}

	vec4 texColor = fs_in.color;

	if (fs_in.tid > 0.0) {
			
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(_simple_TIDs[tid], fs_in.uv);
		
		if (texColor.a < 0.1f) {
			discard;	
		}
	}

	color = vec4(texColor.x, texColor.y, texColor.z, _simple_alpha);	
}