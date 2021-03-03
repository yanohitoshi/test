#include "TitleStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "ClearPointObject.h"
#include "TitlePlayerObject.h"
#include "TitleGroundObject.h"



/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
 */

TitleStageCreator::TitleStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
{
	offset = 400;
}

/*
  @fn デストラクタ
 */

TitleStageCreator::~TitleStageCreator()
{
	//マップデータの削除
	titleMapData.clear();
	titlePlayerData.clear();
}

bool TitleStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(titleMapData, "Assets/Config/TitleMap.json", "baselayer"))
	{
		printf("do'nt have Layer/Titlebaselayer\n");
		return true;
	}
	sizeX = titleMapData[0].size();
	sizeY = titleMapData.size();

	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(titlePlayerData, "Assets/Config/TitleMap.json", "player"))
	{
		printf("do'nt have Layer/Titleplayer\n");
		return true;
	}

	return false;
}

void TitleStageCreator::CreateStage()
{
	// ステージデータを見てその情報ごとのclassを生成する

	Vector3 cameraPos = Vector3::Zero;
	Vector3 playerPos = Vector3::Zero;

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int playerLayer = titlePlayerData[(int)iy][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, -offset * iy, 100);

			switch (playerLayer)
			{
			case(3):
				new TitlePlayerObject(objectPos, false, Tag::TITLE_PLAYER);
				cameraPos = objectPos;
				playerPos = objectPos;
				break;
			}
		}
	}

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int baseLayer = titleMapData[(int)iy][(int)ix];
			Vector3 baseLayerPos = Vector3(offset * ix, -offset * iy, 0);
			Vector3 blockSize = Vector3(200, 200, 100);

			switch (baseLayer)
			{
			case(79):
				new TitleGroundObject(baseLayerPos, blockSize, playerPos,Tag::TITLE_OBJECT);
				break;
			}
		}
	}

	GameObject::CreateTitleCamera(cameraPos);

}
