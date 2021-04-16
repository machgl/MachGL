#version 330 core

layout (location = 0) out vec4 color;

in DATA {

	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	
} fs_in;

uniform sampler2D _texture_to_blur;

uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main() {

	vec2 texOffset = 1.0 / textureSize(_texture_to_blur, 0);
	vec3 result = texture(_texture_to_blur, fs_in.uv).rgb * weight[0];

	if (horizontal) {
		for (int i = 1; i < 5; ++i) {
			
			result += texture(_texture_to_blur, fs_in.uv + vec2(texOffset.x * i, 0.0)).rgb * weight[i];
			result += texture(_texture_to_blur, fs_in.uv - vec2(texOffset.x * i, 0.0)).rgb * weight[i];
		}
	}
	else {
		for (int i = 1; i < 5; ++i) {
			
			result += texture(_texture_to_blur, fs_in.uv + vec2(0.0, texOffset.y * i)).rgb * weight[i];
			result += texture(_texture_to_blur, fs_in.uv - vec2(0.0, texOffset.y * i)).rgb * weight[i];
		}
	}

	color = vec4(result, 1.0);
}