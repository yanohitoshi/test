// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330
layout (location = 0) out vec4 HDRBuffer;
layout (location = 1) out vec4 HiBrightBuffer;

// ライト
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
in vec4 fragLightPos;

uniform vec3 uColor=vec3(0,0,0);
uniform float uLuminance;

void main()
{
    // uniformで持ってきた色をvec4に変換
    vec4 result = vec4(uColor, 0.0f);

    // 色をそのままHiBrightBufferへ出力 
    HiBrightBuffer = result * uLuminance;

    // HDR成分はそのままHDRバッファへ出力
    HDRBuffer = result;

}
