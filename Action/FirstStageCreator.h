#pragma once
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file FirstStageCreator.h
@brief FirstStage�𐶐�����
*/
class FirstStageCreator 
	 : public StageCreatorBase
{
public:
	FirstStageCreator(bool _reUseGameObject, const Tag _objectTag);
	~FirstStageCreator()override;
	/*
	@fn �t�@�C�����J��
	@return �������ۂ�
	*/
	bool OpenFile();

	/*
	@fn �v���C���[�𐶐�����
	*/
	class PlayerObject* CreatePlayer();

	/*
	@fn �X�e�[�W�𐶐�����
	*/
	void CreateStage();

private:

	//�t�@�[�X�g�X�e�[�W�f�[�^
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;

	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;

};

