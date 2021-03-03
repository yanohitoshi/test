#pragma once
#include "Math.h"
#include "BoneTransform.h"
#include <vector>
#include <string>

/*
 @file Animation.h
 @fn Skeletonを用いたアニメーションのデータクラス
*/
class Animation
{
public:
	/*
	@fn アニメーション読み込み
	@param アニメーションへのパス
	*/
	bool Load(const std::string& fileName,bool _loop);                                          
private:
	//アニメーションのためのボーン数
	size_t mNumBones;
	//アニメーションのフレーム数
	size_t mNumFrames;
	//アニメーションの再生時間
	float mDuration;
	//アニメーションのフレーム間の時刻
	float mFrameDuration;
	// ループアニメーションするか？
	bool isLoopAnimation;

	/*
	トラック上の各フレームの変換情報。
	外側のベクトルの各インデックスはボーン、
	内側のベクトルはフレーム。　　　　　　　
	mTracks[ボーン][フレーム数]*/
	std::vector<std::vector<BoneTransform>> mTracks;
public: //ゲッターセッター
	/*
	 @fn ボーン数
	*/
	size_t GetNumBones() const { return mNumBones; }                                
	/*
	 @fn フレーム数
	*/
	size_t GetNumFrames() const { return mNumFrames; }                              
	/*
	 @fn アニメーション期間
	*/
	float GetDuration() const { return mDuration; }                               
	/*
	 @fn フレーム期間
	*/
	float GetFrameDuration() const { return mFrameDuration; }                       

	//指定された配列を、アニメーションの指定された時間に、
	//各ボーンのグローバル（現在の）ポーズマトリックスで埋める。
	//時間は > = 0.0fかつ <= 期間であると予想される
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

	//ループするアニメーションかどうかのフラグをとる
	bool IsLoopAnimation() const { return isLoopAnimation; }
};
