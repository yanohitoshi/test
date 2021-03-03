#pragma once
#include "GameObject.h"


class SkeletalMeshComponent;
class Animation;

/*
@file TitlePlayerObject.h
@brief タイトルシーン中でのプレイヤー
       ただアニメーションを再生するだけのクラス
*/

class TitlePlayerObject :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	再利用するかフラグ
    @param	オブジェクト判別用tag
    */
    TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);
    ~TitlePlayerObject()override;
    /*
    @fn 更新処理
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;
    
    /*
    @fn 入力を引数で受け取る更新関数
    @brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
    */
    void GameObjectInput(const InputState& _keyState)override;

private:

    /*
    @fn アニメーションの更新処理
    */
    void AnimationUpdate();

    // アニメーション用vector配列
    std::vector<const Animation*> animTypes;
    // アニメーションの状態用変数
    int animState;

    // SkeletalMeshComponentのポインタ変数
    SkeletalMeshComponent* skeltalMeshComponent;
    
    // 重力定数
    const float Gravity;
    // 接地フラグ
    bool onGround;
    // ジャンプフラグ
    bool jumpFlag;
    // ジャンプの間隔を測るためのカウント
    int jumpDelayCount;
    // 作用するジャンプ力
    float jumpPower;
    // 初速
    float firstJumpPower;
    // ジャンプする時間用カウント
    float jumpFrameCount;

};

