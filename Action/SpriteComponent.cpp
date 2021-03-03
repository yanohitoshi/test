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

		//レンダラーにポインターを送る
	RENDERER->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveSprite(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void SpriteComponent::Draw(Shader * _shader)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
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
@fn テクスチャをセットし縦横の長さを計算する
@param _texture 使用するテクスチャのポインタ
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
