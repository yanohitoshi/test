#pragma once
#include "StageCreatorBase.h"

/*
@file FinalStageCreator.h
@brief FinalStage�𐶐�����
*/
class FinalStageCreator :
    public StageCreatorBase
{
public:
	FinalStageCreator(bool _reUseGameObject, const Tag _objectTag);
	~FinalStageCreator()override;
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
	std::vector<std::vector<int>> layer6StageData;
	std::vector<std::vector<int>> layer7StageData;
	std::vector<std::vector<int>> layer8StageData;
	std::vector<std::vector<int>> layer9StageData;
	std::vector<std::vector<int>> layer10StageData;
	std::vector<std::vector<int>> layer11StageData;
	std::vector<std::vector<int>> layer12StageData;
	std::vector<std::vector<int>> layer13StageData;
	std::vector<std::vector<int>> layer14StageData;
	std::vector<std::vector<int>> layer15StageData;
	std::vector<std::vector<int>> layer16StageData;
	std::vector<std::vector<int>> layer17StageData;
	std::vector<std::vector<int>> layer18StageData;
	std::vector<std::vector<int>> layer19StageData;
	std::vector<std::vector<int>> layer20StageData;


	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;

};

