#version 410 core

#define MAX_LIGHTS 12

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 bloomColor;

uniform vec4 _light_color[MAX_LIGHTS];
uniform vec3 _light_attenuation[MAX_LIGHTS];
uniform float _light_brightness[MAX_LIGHTS];

uniform sampler2D _texture;
uniform samplerCube _environmentMap;

in DATA {

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

} fs_in;

void main() {

    vec4 texColor = fs_in.col;
        
    texColor = texture(_texture, fs_in.uv);
    
    vec3 unitNormal = normalize(fs_in.surfaceNormal);
    vec3 unitVectorToCamera = normalize(fs_in.toCameraVector);
    
    vec4 totalDiffuse = vec4(0.0);
    vec4 totalSpecular = vec4(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++) {

        float dist = length(fs_in.toLightVector[i]);
        float attFactor = _light_attenuation[i].x + (_light_attenuation[i].y * dist) + (_light_attenuation[i].z * dist * dist);

        vec3 unitLightVector = normalize(fs_in.toLightVector[i]);

        float nDotl = dot(unitNormal, unitLightVector);
        float brightness = max(nDotl, 0.0) * min(_light_brightness[i], 1.0);

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
        specularFactor = max(specularFactor, 0.0);
        float dampedFactor = pow(specularFactor, fs_in.shine);

        totalDiffuse = totalDiffuse + (brightness * _light_color[i]) / attFactor;
        totalSpecular = totalSpecular + (dampedFactor * fs_in.reflectivity * _light_color[i]) / attFactor;
    }

    totalDiffuse = max(totalDiffuse, 0.2);

    vec4 reflectedColor = texture(_environmentMap, fs_in.reflectedVector);
    vec4 outColor = totalDiffuse * texColor + totalSpecular;
    color = mix(outColor, reflectedColor, fs_in.reflectivity);
}