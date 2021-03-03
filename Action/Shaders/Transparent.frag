// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;

// This corresponds to the output color to the color buffer
out vec4 outColor;

// This is used for the texture sampling
uniform sampler2D uTexture;
uniform vec3 uColor = vec3(0,0,0);
uniform float uAlpha = 1.0;

void main()
{
	// Sample color from texture
    outColor = texture(uTexture, fragTexCoord);
    outColor = vec4(outColor.rgb + uColor,uAlpha);
}
