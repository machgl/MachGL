#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 _simple_pr_matrix = mat4(1.0);
uniform float _radius = 0;

out DATA {

	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
	float radius;

} vs_out;

void main() {

	gl_Position = _simple_pr_matrix * position;
	vs_out.position = position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
	vs_out.radius = _radius;
}