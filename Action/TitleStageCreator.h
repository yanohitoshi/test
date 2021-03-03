#pragma once
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file TitleStageCreator.h
@brief TitleStage�𐶐�����
*/
class TitleStageCreator :
    public StageCreatorBase
{
public:

	// �R���X�g���N�^
	TitleStageCreator(bool _reUseGameObject, const Tag _objectTag);
	// �f�X�g���N�^
	~TitleStageCreator()override;

	/*
	@fn �t�@�C�����J��
	@return �������ۂ�
	*/
	bool OpenFile();

	/*
	@fn �X�e�[�W�𐶐�����
	*/
	void CreateStage();

private:

	//�^�C�g���\���p
	std::vector<std::vector<int>> titleMapData;
	std::vector<std::vector<int>> titlePlayerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;

};

