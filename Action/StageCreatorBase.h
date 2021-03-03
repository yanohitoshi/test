#pragma once
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file StageCreatorBase.h
@brief �X�e�[�W����class�̊��N���X
*/
class StageCreatorBase :
    public GameObject
{
public:
	StageCreatorBase(bool _reUseGameObject, const Tag _objectTag);
	~StageCreatorBase()override;

protected:
	/*
	@fn Json�t�@�C����ǂݍ��݃R���e�i�^�Ɋi�[����
	@param _mapDate �i�[���������R���e�i�ւ̃A�h���X
	@param _fileName Json�t�@�C���A�h���X
	@param _layerName Json�t�@�C�����̃��C���[�A�h���X
	@return false=���s
	*/
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);


};

