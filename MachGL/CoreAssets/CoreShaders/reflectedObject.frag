#version 410 core

layout (location = 0) out vec4 color;

uniform sampler2D _texture;
uniform samplerCube _environmentMap;

in DATA {

    vec4 pos;
    vec2 uv;
    float tid;
    vec4 col;
    float shine;
    float reflectivity;
    vec3 reflectedVector;

} fs_in;

void main() {

    vec4 texColor = fs_in.col;
        
    texColor = texture(_texture, fs_in.uv);
   
    vec4 reflectedColor = texture(_environmentMap, fs_in.reflectedVector);
    vec4 outColor = texColor;
    color = mix(outColor, reflectedColor, fs_in.reflectivity);
}