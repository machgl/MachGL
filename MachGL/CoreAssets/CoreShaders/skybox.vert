#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 _pr_matrix = mat4(1.0);
uniform mat4 _vw_matrix = mat4(1.0);

out vec3 texCoords;

void main() {
	
	texCoords = pos;
	vec4 position = _pr_matrix * _vw_matrix * vec4(pos, 1.0);
	gl_Position = position.xyww;
}