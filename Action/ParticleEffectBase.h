#pragma once
#include "GameObject.h"
#include "ParticleComponent.h"
#include <string>

enum ParticleState
{
	PARTICLE_ACTIVE,
	PARTICLE_DISABLE,
};


/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/
class ParticleEffectBase :
	public GameObject
{
public:
	/*
	@param _pos オブジェクトの生成場所
	@param _velocity オブジェクトの移動量
	@param _lifeCount オブジェクトの生存時間
	@param _spriteFileName 画像へのアドレス
	@param _scale 画像の拡大サイズ
	*/
	ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, const float& _scale = 10);
	~ParticleEffectBase();

	/*
	@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	/*
	@fn 派生クラスごとに決定する更新関数
	*/
	virtual void UpdateParticleObject(float _deltaTime);
protected:
	/*
	@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
	*/
	void LifeCountDown();
	//画像の描画クラス
	ParticleComponent* particleComponent;
	//生存時間
	int lifeCount;

	ParticleState particleState;
public:
	void SetReverve(float _flag);
};
