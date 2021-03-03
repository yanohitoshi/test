#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(GameObject * _owner, bool _isBackGround,int _drawOrder)
    :Component(_owner)
    ,texture(nullptr)
    ,drawOrder(_drawOrder)
    ,textureWidth(0)
    ,textureHeight(0)
	, visible(true)
	, isBackGround(_isBackGround)
{

		//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveSprite(this);
}

/*
@brief	�`�揈��
@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SpriteComponent::Draw(Shader * _shader)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (texture&&owner->GetState()!=State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		_shader->SetFloatUniform("uAlpha", alpha);

		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
	}
}

/*
@fn �e�N�X�`�����Z�b�g���c���̒������v�Z����
@param _texture �g�p����e�N�X�`���̃|�C���^
*/
void SpriteComponent::SetTexture(Texture * _texture)
{
	if (_texture == nullptr)
	{
		return;
	}
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
