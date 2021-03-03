#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>

/*
 @file Skeleton.h 
 @fn ���i
*/
class Skeleton
{
public:
	/*
	 @struct ���ꂼ��̃{�[���̍��i��`
	*/
	struct Bone
	{
		// ���[�J���o�C���h�|�[�Y
		BoneTransform mLocalBindPose;                         
		// �{�[����
		std::string mName;                                                
		// �eID
		int mParent;                                                     
	};

	/*
	@fn �X�P���g���̃t�@�C������̃��[�h
	@param _filename
	@return �����A���s
	*/
	bool Load(const std::string& _filename);
protected:
	/*
	@fn �X�P���g�������[�h���ꂽ�Ƃ��Ɏ����I�ɌĂяo����e�{�[���̃O���[�o���t�o�C���h�|�[�Y���v�Z
	*/    
	void ComputeGlobalInvBindPose();
private:
	//�{�[���z��
	std::vector<Bone> mBones;
	//���ꂼ��̃{�[���̋t�o�C���h�|�[�Y�s��
	std::vector<Matrix4> mGlobalInvBindPoses;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@fn �{�[����
	*/
	size_t GetNumBones() const { return mBones.size(); }
	/*
	@fn id�ɂ��{�[��
	*/
	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	/*
	@fn �{�[���z��
	*/
	const std::vector<Bone>& GetBones() const { return mBones; }
	/*
	@fn �O���[�o���t�o�C���h�s��z��̎擾
	*/
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
