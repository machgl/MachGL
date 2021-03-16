#version 330 core

#define MAX_LIGHTS 12

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 normal;
layout (location = 4) in vec4 color;
layout (location = 5) in float shine;
layout (location = 6) in float reflectivity;
layout (location = 7) in float textureScale;

uniform mat4 _pr_matrix = mat4(1.0);
uniform mat4 _tr_matrix = mat4(1.0);
uniform mat4 _vw_matrix = mat4(1.0);
uniform vec3 _light_position[MAX_LIGHTS];
uniform vec3 _camera_position;

out DATA {

    vec4 pos;
    vec2 uv;
    float tid;
    vec4 col;
    vec3 surfaceNormal; 
    vec3 toLightVector[MAX_LIGHTS];
    vec3 toCameraVector;
    float shine;
    float reflectivity;
    vec3 reflectedVector;

} vs_out;


void main () {

    vec4 worldPosition =  _tr_matrix * position;
    vec4 posRelativeToCamera = _vw_matrix * worldPosition;
    gl_Position = _pr_matrix * posRelativeToCamera;

    vs_out.pos = posRelativeToCamera;
    vs_out.uv = uv * textureScale;
    vs_out.col = color;
    vs_out.tid = tid;
    vs_out.surfaceNormal = (_tr_matrix * normal).xyz;
    vs_out.toCameraVector = (inverse(_vw_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
    vs_out.shine = shine;
    vs_out.reflectivity = reflectivity;

    vec3 viewVector = normalize(worldPosition.xyz - _camera_position);
    vs_out.reflectedVector = reflect(viewVector, normalize(normal.xyz));

    for (int i = 0; i < MAX_LIGHTS; i++) {

        vs_out.toLightVector[i] = _light_position[i] - worldPosition.xyz;
    }
}