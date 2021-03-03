#pragma once
#include "Math.h"
#include "BoneTransform.h"
#include <vector>
#include <string>

/*
 @file Animation.h
 @fn Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/
class Animation
{
public:
	/*
	@fn �A�j���[�V�����ǂݍ���
	@param �A�j���[�V�����ւ̃p�X
	*/
	bool Load(const std::string& fileName,bool _loop);                                          
private:
	//�A�j���[�V�����̂��߂̃{�[����
	size_t mNumBones;
	//�A�j���[�V�����̃t���[����
	size_t mNumFrames;
	//�A�j���[�V�����̍Đ�����
	float mDuration;
	//�A�j���[�V�����̃t���[���Ԃ̎���
	float mFrameDuration;
	// ���[�v�A�j���[�V�������邩�H
	bool isLoopAnimation;

	/*
	�g���b�N��̊e�t���[���̕ϊ����B
	�O���̃x�N�g���̊e�C���f�b�N�X�̓{�[���A
	�����̃x�N�g���̓t���[���B�@�@�@�@�@�@�@
	mTracks[�{�[��][�t���[����]*/
	std::vector<std::vector<BoneTransform>> mTracks;
public: //�Q�b�^�[�Z�b�^�[
	/*
	 @fn �{�[����
	*/
	size_t GetNumBones() const { return mNumBones; }                                
	/*
	 @fn �t���[����
	*/
	size_t GetNumFrames() const { return mNumFrames; }                              
	/*
	 @fn �A�j���[�V��������
	*/
	float GetDuration() const { return mDuration; }                               
	/*
	 @fn �t���[������
	*/
	float GetFrameDuration() const { return mFrameDuration; }                       

	//�w�肳�ꂽ�z����A�A�j���[�V�����̎w�肳�ꂽ���ԂɁA
	//�e�{�[���̃O���[�o���i���݂́j�|�[�Y�}�g���b�N�X�Ŗ��߂�B
	//���Ԃ� > = 0.0f���� <= ���Ԃł���Ɨ\�z�����
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

	//���[�v����A�j���[�V�������ǂ����̃t���O���Ƃ�
	bool IsLoopAnimation() const { return isLoopAnimation; }
};
