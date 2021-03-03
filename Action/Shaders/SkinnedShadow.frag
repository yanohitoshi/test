#version 330 core
layout (location = 0) out vec4 HDRBuffer;
layout (location = 1) out vec4 HiBrightBuffer;
// ライト
struct DirectionalLight
{
        vec3  mDirection; // ライトの方向(ディレクショナルライト)
        vec3  mDiffuseColor; // ライトディフューズ
        vec3  mSpecColor; // ライトスペキュラー
};

in      vec2  fragTexCoord         ; // テクスチャ座標
in      vec3  fragNormal            ; // フラグメント位置の法線ベクトル
in      vec3  fragWorldPos           ; // フラグメント位置のワールド座標
in      vec4  fragLightPos; // ライト空間でのフラグメント座標


uniform sampler2D uDiffuseMap    ; // ディフューズテクスチャ
uniform sampler2D depthMap      ; // シャドウ（深度）マップ
uniform sampler2D uEmissiveMap;
uniform sampler2D uSpecularMap;
uniform sampler2D uNormalMap;

uniform vec3 uCameraPos; // 視点
uniform float uSpecPower;
uniform vec3 uAmbientLight;
uniform float uLuminance;
uniform DirectionalLight uDirLight;

out     vec4  FragColor         ; // このフラグメントの出力

float ShadowCaluculation(vec4 fragPosLightSpace)
{
   //パースペクティブ徐算
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //  [0,1] の範囲に変換
    projCoords = projCoords * 0.5 + 0.5;
   //シャドウマップよりライトに最も近いフラグメントの深度値を得る
   float closestDepth = texture(depthMap,projCoords.xy).r;
   //現在描画しようとしているフラグメント深度値
   float crrentDepth = projCoords.z;
   //シャドウ判定（1.0：シャドウ0.0：シャドウの外）
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(-uDirLight.mDirection);
    float bias = max(0.001 * (1.0 - dot(normal, lightDir)), 0.0001);

   //float bias = 0.005;
   //float shadow = crrentDepth - bias > closestDepth ? 1.0 : 0.0;
    float shadow = crrentDepth - bias > closestDepth ? 1.0 : 0.0;
    if(projCoords.z > 1.0)
    {
        shadow = 0.0;
    }

   //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
   // for(int x = -1; x <= 1; ++x)
   // {
   //     for(int y = -1; y <= 1; ++y)
   //     {
   //         float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
   //         shadow += crrentDepth - bias > pcfDepth ? 1.0 : 0.0;        
   //     }    
   // }
   // shadow /= 9.0;

   return shadow;
}

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

	float shadow = ShadowCaluculation(fragLightPos);

	vec3 texColor = texture(uDiffuseMap, fragTexCoord).rgb;
	vec3 diffuseColor = vec3(Diffuse) * texColor;
	vec3 ambientColor = uAmbientLight * texColor;

	vec3 result = ( 1.0 - shadow ) * (diffuseColor + Specular) + ambientColor;

    FragColor = vec4(result, 1.0);
    
    //輝度計算によって高輝度成分のみ、HiBrightBufferに書き込み
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    {
        HiBrightBuffer = vec4(result, 0.0f) + texture(uEmissiveMap, fragTexCoord) * uLuminance;

    }
    else
    {
        HiBrightBuffer = vec4(0.0f, 0.0f, 0.0f, 0.0f) + texture(uEmissiveMap, fragTexCoord) * uLuminance;
    }

    // HDR成分はそのままHDRバッファへ出力
    HDRBuffer = vec4(result, 0.0);

}

