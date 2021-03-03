// ----------------------------------------------------------------
//  �p�[�e�B�N���p�t���O�����g�V�F�[�_�[
// ----------------------------------------------------------------

// GLSL 3.3 ��v��
#version 330

//layout (location = 0) out vec4 HDRBuffer;
//layout (location = 1) out vec4 HiBrightBuffer;

// ���_�V�F�[�_�[����̓���
// �e�N�X�`�����W
in vec2 fragTexCoord;
// �@���i���[���h��ԁj
in vec3 fragNormal;
// ���_�ʒu�i���[���h��ԁj
in vec3 fragWorldPos;


// �o�̓J���[�i�o�̓s�N�Z���J���[�j
out vec4 outColor;

// �e�N�X�`���T���v�����O
uniform sampler2D uTexture;
uniform float     uAlpha;
uniform vec3      uColor;

void main()
{
    vec4 col = texture(uTexture, fragTexCoord);
	outColor.rgb = col.rgb * uColor;
	outColor.a = col.a * uAlpha;

}
