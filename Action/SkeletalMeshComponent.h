#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

/*
@file SkeletalMeshComponent.h
@brief スケルトンデータの描画とアニメーション
*/
class SkeletalMeshComponent : public MeshComponent
{
public:

	SkeletalMeshComponent(class GameObject* owner);

	void Update(float deltaTime) override;

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* shader) override;

   	/*
	@fn アニメーションの再生
	@param _anim アニメーションデータクラス
	@param _playRate アニメーションの再生速度
	@return アニメーションの残り時間
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);
protected:
	/*
	@fn 行列パレットの計算
	*/
	void ComputeMatrixPalette();                                       
	// 行列パレット
	MatrixPalette palette;                                    
	// スケルトンデータ
	const class Skeleton* skeleton;                                       
	// アニメーションデータ
	const class Animation* animation;                                     
	// アニメーションの再生速度
	float animPlayRate;                                                  
	// アニメーション時間
	float animTime;                                                       
	//スケルトンデータに乗算する色
	Vector3 color;
	//textureセット用関数
	void SetTextureToShader(Shader* shader);

public://ゲッターセッター
	/*
	@param _skeleton スケルトンデータ
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { skeleton = _skeleton; }
	/*
	@param _color スケルトンデータに乗算する色
	*/
	void SetColor(const Vector3& _color) { color = _color; }

	//再生中かどうか
	bool IsPlaying();


};
