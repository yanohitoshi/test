#include "FirstStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "NeedlePanelObject.h"
#include "RespawnPoint.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"

/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
 */

FirstStageCreator::FirstStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
{
	offset = 400;
}

/*
  @fn デストラクタ
 */

FirstStageCreator::~FirstStageCreator()
{
	//マップデータの削除
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	playerData.clear();
}

bool FirstStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/firstStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();
	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/firstStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/firstStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/firstStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/firstStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/firstStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	return false;
}

PlayerObject* FirstStageCreator::CreatePlayer()
{
	//playerクラスに初期位置を渡すための変数
	Vector3 pos = Vector3(0, 0, 0);

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			if (playerData[(int)iy][(int)ix] == 19)
			{
				pos = Vector3(offset * ix, -offset * iy, 500);
			}
		}
	}
	//1600.-4400
	GameObject::CreateMainCamera(pos);
	return new PlayerObject(pos, false, Tag::PLAYER);
}

void FirstStageCreator::CreateStage()
{
	// ステージデータを見てその情報ごとのclassを生成する

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			Vector3 blockSize = Vector3(200, 200, 100);
			Vector3 switchSize = Vector3(4, 4, 0.5);
			Vector3 switchBaseSize = Vector3(2.0f, 2.0f, 1.0f);
			Vector3 needlePanelSize = Vector3(200, 200, 3);
			Vector3 jumpSwitchSize = Vector3(200, 200, 3);
			Vector3 wallBlockSizeNum1 = Vector3(600.0f, 200.0f, 2400.0f);
			Vector3 wallBlockSizeNum2 = Vector3(200.0f, 600.0f, 2400.0f);
			AABB respawnBox = { Vector3(-10.0f,-1000.0f,-1000.0f),Vector3(10.0f,1000.0f,1000.0f) };

			const unsigned int layer1 = layer1StageData[(int)iy][(int)ix];
			Vector3 layer1Pos = Vector3(offset * ix, -offset * iy, 0);

			switch (layer1)
			{
			case(79):
				new BoxObject(layer1Pos, blockSize, Tag::GROUND);
				break;
			}

			const unsigned int layer2 = layer2StageData[(int)iy][(int)ix];
			Vector3 layer2Pos = Vector3(offset * ix, -offset * iy, 200);
			Vector3 layer2SwitchPos = Vector3(offset * ix, -offset * iy, 100);

			switch (layer2)
			{
			case(78):
				new BoxObject(layer2Pos, blockSize, Tag::GROUND);
				break;
			case(40):
				new JumpSwitchObject(layer2SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(16):
				new NeedlePanelObject(layer2SwitchPos, needlePanelSize, Tag::NEEDLE_PANEL);
				break;
			}

			const unsigned int layer3 = layer3StageData[(int)iy][(int)ix];
			Vector3 layer3Pos = Vector3(offset * ix, -offset * iy, 400);
			Vector3 layer3SwitchPos = Vector3(offset * ix, -offset * iy, 300);

			switch (layer3)
			{
			case(77):
				new BoxObject(layer3Pos, blockSize, Tag::GROUND);
				break;
			case(1):
				new WallBlockObject(layer3Pos, wallBlockSizeNum1, Tag::WALL);
				break;
			case(2):
				new WallBlockObject(layer3Pos, wallBlockSizeNum2, Tag::WALL);
				break;
			}

			const unsigned int layer4 = layer4StageData[(int)iy][(int)ix];
			Vector3 layer4Pos = Vector3(offset * ix, -offset * iy, 600);
			Vector3 layer4WallPos = Vector3(offset * ix, -offset * iy, 850);
			Vector3 layer4SwitchPos = Vector3(offset * ix, -offset * iy, 500);
			Vector3 layer4BaseSwitchPos = Vector3(offset * ix, -offset * iy, 700);

			switch (layer4)
			{
			case(76):
				new BoxObject(layer4Pos, blockSize, Tag::GROUND);
				break;
			case(3):
				new RespawnPoint(layer4Pos, respawnBox, Tag::RESPOWN_POINT);
				break;

			}

			const unsigned int layer5 = layer5StageData[(int)iy][(int)ix];
			Vector3 layer5Pos = Vector3(offset * ix, -offset * iy, 800);
			Vector3 layer5SwitchPos = Vector3(offset * ix, -offset * iy, 700);
			Vector3 moveWallSize = Vector3(20, 1000, 1000);

			switch (layer5)
			{
			case(75):
				new BoxObject(layer5Pos, blockSize, Tag::GROUND);
				break;
			case(21):
				new SwitchBaseObject(layer5SwitchPos, switchBaseSize, Tag::GROUND, Tag::TUTORIAL_SWITCH);
				break;
			case(20):
				new NextSceneObject(Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z), Tag::TUTORIAL_CLEAR_POINT);
				break;
			case(41):
				new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + 200.0f, layer5Pos.z - 100.0f), moveWallSize, Tag::TUTORIAL_MOVE_WALL, 300.0f,
					Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - moveWallSize.z));
				break;
			}
		}
	}
}
