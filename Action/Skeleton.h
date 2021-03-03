#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>

/*
 @file Skeleton.h 
 @fn 骨格
*/
class Skeleton
{
public:
	/*
	 @struct それぞれのボーンの骨格定義
	*/
	struct Bone
	{
		// ローカルバインドポーズ
		BoneTransform mLocalBindPose;                         
		// ボーン名
		std::string mName;                                                
		// 親ID
		int mParent;                                                     
	};

	/*
	@fn スケルトンのファイルからのロード
	@param _filename
	@return 成功、失敗
	*/
	bool Load(const std::string& _filename);
protected:
	/*
	@fn スケルトンがロードされたときに自動的に呼び出され各ボーンのグローバル逆バインドポーズを計算
	*/    
	void ComputeGlobalInvBindPose();
private:
	//ボーン配列
	std::vector<Bone> mBones;
	//それぞれのボーンの逆バインドポーズ行列
	std::vector<Matrix4> mGlobalInvBindPoses;
public: //ゲッターセッター
	/*
	@fn ボーン数
	*/
	size_t GetNumBones() const { return mBones.size(); }
	/*
	@fn idによるボーン
	*/
	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	/*
	@fn ボーン配列
	*/
	const std::vector<Bone>& GetBones() const { return mBones; }
	/*
	@fn グローバル逆バインド行列配列の取得
	*/
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
