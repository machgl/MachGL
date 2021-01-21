#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

uniform mat4 _splash_pr_matrix;

out DATA {

	vec4 position;
	vec2 uv;
	vec4 color;

} vs_out;

void main() {

	gl_Position =_splash_pr_matrix * position;
	vs_out.position = position;
	vs_out.uv = uv;
	vs_out.color = color;
}