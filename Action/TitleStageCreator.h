#pragma once
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file TitleStageCreator.h
@brief TitleStageを生成する
*/
class TitleStageCreator :
    public StageCreatorBase
{
public:

	// コンストラクタ
	TitleStageCreator(bool _reUseGameObject, const Tag _objectTag);
	// デストラクタ
	~TitleStageCreator()override;

	/*
	@fn ファイルを開く
	@return 成功か否か
	*/
	bool OpenFile();

	/*
	@fn ステージを生成する
	*/
	void CreateStage();

private:

	//タイトル表示用
	std::vector<std::vector<int>> titleMapData;
	std::vector<std::vector<int>> titlePlayerData;

	//配置するオブジェクトの間隔X
	int sizeX;
	//配置するオブジェクトの間隔Y
	int sizeY;
	//配置するオブジェクトの間隔。サイズ
	float offset;

};

