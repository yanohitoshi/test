#version 330 core

layout (location = 0) out vec4 HDRBuffer;
layout (location = 1) out vec4 HiBrightBuffer;

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

// ライト
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
in vec4 fragLightPos;


uniform sampler2D uDiffuseMap;
uniform sampler2D uNormalMap;
uniform sampler2D uSpecularMap;
uniform sampler2D uEmissiveMap;

uniform sampler2D depthMap;

uniform vec3 uCameraPos;

uniform float uSpecPower;

uniform vec3 uAmbientLight;

uniform float uLuminance;

uniform DirectionalLight uDirLight;



float ShadowCalculation(vec4 fragPosLightSpace);

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 L = normalize(-uDirLight.mDirection);
	vec3 V = normalize(uCameraPos - fragWorldPos);
	vec3 R = normalize(reflect(-L, N));

	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);

	vec3 Diffuse;
	vec3 Specular;

	Diffuse = uDirLight.mDiffuseColor * max(NdotL,0.0f);
	Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);

	float shadow = ShadowCalculation(fragLightPos);

	vec3 texColor = texture(uDiffuseMap, fragTexCoord).rgb;
	vec3 diffuseColor = vec3(Diffuse) * texColor;
	vec3 ambientColor = uAmbientLight * texColor;

	vec3 result = ( 1.0 - shadow ) * (diffuseColor + Specular) + ambientColor;
	
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    {
        HiBrightBuffer = vec4(result, 0.0f) + texture(uEmissiveMap, fragTexCoord) * uLuminance;
    }
    else
    {
        HiBrightBuffer = vec4(0.0f, 0.0f, 0.0f, 0.0f) + texture(uEmissiveMap, fragTexCoord) * uLuminance;
    }
    HDRBuffer = vec4(result, 0.0);
}


float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(depthMap,projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 normal = normalize(fragNormal);
       vec3 lightDir = normalize(-uDirLight.mDirection);
    float bias = max(0.001 * (1.0 - dot(normal, lightDir)), 0.0001);
    
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
    {
        shadow = 0.0;
    }
    return shadow;
}
