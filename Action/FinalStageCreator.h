#pragma once
#include "StageCreatorBase.h"

/*
@file FinalStageCreator.h
@brief FinalStageを生成する
*/
class FinalStageCreator :
    public StageCreatorBase
{
public:
	FinalStageCreator(bool _reUseGameObject, const Tag _objectTag);
	~FinalStageCreator()override;
	/*
	@fn ファイルを開く
	@return 成功か否か
	*/
	bool OpenFile();

	/*
	@fn プレイヤーを生成する
	*/
	class PlayerObject* CreatePlayer();

	/*
	@fn ステージを生成する
	*/
	void CreateStage();

private:

	//ファーストステージデータ
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


	//playerのデータ
	std::vector<std::vector<int>> playerData;

	//配置するオブジェクトの間隔X
	int sizeX;
	//配置するオブジェクトの間隔Y
	int sizeY;
	//配置するオブジェクトの間隔。サイズ
	float offset;

};

