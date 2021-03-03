#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

// ビルボード行列
Matrix4 ParticleComponent::staticBillboardMat;
// カメラのワールド座標
Vector3 ParticleComponent::staticCameraWorldPos;

/*
 @param _offset 親オブジェクトクラスと画像を描画する位置の差
 @param _scale 画像の描画サイズ
*/
ParticleComponent::ParticleComponent(GameObject* _owner, const Vector3& _offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, offset(_offset)
	, scale(_scale)
	, alpha(1.0f)
	, blendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, visible(true)
	, drawOrder(_updateOrder)
	, color(Vector3(1, 1, 1))
	, reverce(false)
	,textureID(0)

{
	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態でないか
	if (owner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	
	matScale = Matrix4::CreateScale(scale);
	mat = Matrix4::CreateTranslation(owner->GetPosition());

	_shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	_shader->SetFloatUniform("uAlpha", alpha);
	_shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// カメラ距離でのソート用
bool ParticleComponent::operator<(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis < lenRhs;
}

// カメラ距離でのソート用
bool ParticleComponent::operator>(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis > lenRhs;
}


Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1;

	Matrix4 rot;
	rot = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	ret =  rot * ret;
	return Matrix4(ret);
}
