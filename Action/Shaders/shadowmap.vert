#version 330 core

layout (location = 0) in vec3 aPos      ; // 頂点位置
layout (location = 1) in vec3 aNormal   ; // 法線
layout (location = 2) in vec2 aTexCoords; // テクスチャ座標

//uniform mat4 model             ; 
uniform mat4 uWorldTransform; // モデル行列
uniform mat4 view              ; // ビュー行列
uniform mat4 projection        ; // プロジェクション行列
uniform mat4 lightSpaceMatrix  ; // ライト空間行列

out     vec3 fragNormal            ; // フラグメントへの法線出力
out     vec3 fragWorldPos           ; // フラグメントの位置座標出力
out     vec2 fragTexCoord         ; // テクスチャ座標
out     vec4 fragLightPos ; // ライト空間でのフラグメント座標

void main()
{

    fragWorldPos      = vec3(vec4(aPos, 1.0) * uWorldTransform);
    fragNormal        = mat3(transpose(inverse(uWorldTransform))) * aNormal;
    fragTexCoord      = aTexCoords;
    fragLightPos      = vec4(fragWorldPos, 1.0) * lightSpaceMatrix;
    gl_Position       = vec4(fragWorldPos ,1.0) * view * projection  ;

}