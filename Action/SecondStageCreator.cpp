#include "SecondStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "RespawnPoint.h"
#include "NeedlePanelObject.h"
#include "MoveBlockObject.h"
#include "SwitchBaseObject.h"

/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
*/

SecondStageCreator::SecondStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
{
	offset = 400;
}

/*
  @fn デストラクタ
*/

SecondStageCreator::~SecondStageCreator()
{
	//マップデータの削除
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	layer6StageData.clear();
	layer7StageData.clear();
	layer8StageData.clear();
	layer9StageData.clear();
	layer10StageData.clear();
	layer11StageData.clear();

	playerData.clear();
	spawnPointData.clear();

}



bool SecondStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/secondStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();
	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/secondStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/secondStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/secondStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/secondStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/secondStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// ステージデータ読み込み (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/secondStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// ステージデータ読み込み (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/secondStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// ステージデータ読み込み (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/secondStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}
	// ステージデータ読み込み (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/secondStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// ステージデータ読み込み (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/secondStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// ステージデータ読み込み (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/secondStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/secondStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	return false;
}

PlayerObject* SecondStageCreator::CreatePlayer()
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

	GameObject::CreateMainCamera(pos);
	return new PlayerObject(pos, false, Tag::PLAYER);
}

void SecondStageCreator::CreateStage()
{

	// ステージデータを見てその情報ごとのclassを生成する

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int layer1 = layer1StageData[(int)iy][(int)ix];
			Vector3 layer1Pos = Vector3(offset * ix, -offset * iy, 0);
			Vector3 blockSize = Vector3(200, 200, 100);
			Vector3 switchBaseSize = Vector3(2.0f, 2.0f, 1.0f);
			Vector3 switchSize = Vector3(4, 4, 0.5);
			Vector3 needlePanelSize = Vector3(200, 200, 3);
			Vector3 jumpSwitchSize = Vector3(200, 200, 5);
			Vector3 wallBlockSizeNum1 = Vector3(600.0f, 200.0f, 2400.0f);
			Vector3 wallBlockSizeNum2 = Vector3(200.0f, 600.0f, 2400.0f);
			Vector3 moveWallSize = Vector3(20, 1000, 1000);
			AABB respawnBox = { Vector3(-10.0f,-10000.0f,-10000.0f),Vector3(10.0f,10000.0f,10000.0f) };
			switch (layer1)
			{
			case(79):
				new BoxObject(layer1Pos, blockSize, Tag::GROUND);
				break;
			}

			const unsigned int layer2 = layer2StageData[(int)iy][(int)ix];
			Vector3 layer2Pos = Vector3(offset * ix, -offset * iy, 200);
			Vector3 layer2SwitchPos = Vector3(offset * ix, -offset * iy, 101);

			switch (layer2)
			{
			case(78):
				new BoxObject(layer2Pos, blockSize, Tag::GROUND);
				break;
			case(40):
				new JumpSwitchObject(layer2SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(4):
				new NeedlePanelObject(layer2SwitchPos, needlePanelSize,Tag::NEEDLE_PANEL);
			}

			const unsigned int layer3 = layer3StageData[(int)iy][(int)ix];
			Vector3 layer3Pos = Vector3(offset * ix, -offset * iy, 400);
			Vector3 layer3SwitchPos = Vector3(offset * ix, -offset * iy, 301);

			switch (layer3)
			{
			case(77):
				new BoxObject(layer3Pos, blockSize, Tag::GROUND);
				break;
			case(21):
				new SwitchBaseObject(layer3SwitchPos, switchBaseSize,Tag::GROUND, Tag::FIRST_SWITCH);
				break;
			case(40):
				new JumpSwitchObject(layer3SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;

			}

			const unsigned int layer4 = layer4StageData[(int)iy][(int)ix];
			Vector3 layer4Pos = Vector3(offset * ix, -offset * iy, 600);
			Vector3 layer4SwitchPos = Vector3(offset * ix, -offset * iy, 501);
			switch (layer4)
			{
			case(76):
				new BoxObject(layer4Pos, blockSize, Tag::GROUND);
				break;
			case(5):
				new MoveBlockObject(layer4Pos, blockSize, Tag::MOVE_GROUND,Vector3(0.0f,1600.0f,0.0f),Vector3::UnitY,200.0f,MoveDirectionTag::MOVE_Y);
				break;
			case(21):
				new SwitchBaseObject(layer4SwitchPos, switchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
				break;

			}

			const unsigned int layer5 = layer5StageData[(int)iy][(int)ix];
			Vector3 layer5Pos = Vector3(offset * ix, -offset * iy, 800);
			Vector3 layer5SwitchPos = Vector3(offset * ix, -offset * iy, 701);

			switch (layer5)
			{
			case(75):
				new BoxObject(layer5Pos, blockSize, Tag::GROUND);
				break;
			case(21):
				new SwitchBaseObject(layer5SwitchPos, switchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
				break;
			case(22):
				new SwitchBaseObject(layer5SwitchPos, switchBaseSize, Tag::GROUND, Tag::NEXT_SCENE_SWITCH);
				break;
			case(40):
				new JumpSwitchObject(layer5SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(1):
				new WallBlockObject(layer5Pos, wallBlockSizeNum1, Tag::WALL);
				break;
			case(2):
				new WallBlockObject(layer5Pos, wallBlockSizeNum2, Tag::WALL);
				break;
			}

			const unsigned int layer6 = layer6StageData[(int)iy][(int)ix];
			Vector3 layer6Pos = Vector3(offset * ix, -offset * iy, 1000);
			Vector3 layer6SwitchPos = Vector3(offset * ix, -offset * iy, 901);

			switch (layer6)
			{
			case(74):
				new BoxObject(layer6Pos, blockSize, Tag::GROUND);
				break;
			case(6):
				new MoveBlockObject(layer6Pos, blockSize, Tag::MOVE_GROUND, Vector3(0.0f, 800.0f, 0.0f), Vector3::UnitY, 250.0f, MoveDirectionTag::MOVE_Y);
				break;
			case(7):
				new MoveBlockObject(layer6Pos, blockSize, Tag::MOVE_GROUND, Vector3(0.0f, -800.0f, 0.0f), Vector3::NegUnitY, 500.0f, MoveDirectionTag::MOVE_Y);
				break;
			case(21):
				new SwitchBaseObject(layer6SwitchPos, switchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
				break;
			case(22):
				new SwitchBaseObject(layer6SwitchPos, switchBaseSize, Tag::GROUND, Tag::NEXT_SCENE_SWITCH);
				break;
			case(40):
				new JumpSwitchObject(layer6SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(41):
				new MoveWallBlock(Vector3(layer6Pos.x, layer6Pos.y + 200.0f, layer6Pos.z - 100.0f), moveWallSize, Tag::FIRST_MOVE_WALL, 300.0f,
					Vector3(layer6Pos.x, layer6Pos.y, layer6Pos.z - moveWallSize.z));
				break;
			case(3):
				new RespawnPoint(layer6Pos, respawnBox, Tag::RESPOWN_POINT);
				break;

			}

			const unsigned int layer7 = layer7StageData[(int)iy][(int)ix];
			Vector3 layer7Pos = Vector3(offset * ix, -offset * iy, 1200);
			Vector3 layer7SwitchPos = Vector3(offset * ix, -offset * iy, 1101);

			switch (layer7)
			{
			case(73):
				new BoxObject(layer7Pos, blockSize, Tag::GROUND);
				break;
			case(40):
				new JumpSwitchObject(layer7SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(4):
				new NeedlePanelObject(layer7SwitchPos, needlePanelSize, Tag::NEEDLE_PANEL);
				break;
			case(3):
				new RespawnPoint(layer7Pos, respawnBox, Tag::RESPOWN_POINT);
				break;

			}

			const unsigned int layer8 = layer8StageData[(int)iy][(int)ix];
			Vector3 layer8Pos = Vector3(offset * ix, -offset * iy, 1400);
			Vector3 layer8SwitchPos = Vector3(offset * ix, -offset * iy, 1301);

			switch (layer8)
			{
			case(72):
				new BoxObject(layer8Pos, blockSize, Tag::GROUND);
				break;
			case(7):
				new MoveBlockObject(layer8Pos, blockSize, Tag::MOVE_GROUND, Vector3(0.0f, 0.0f, 800.0f), Vector3::UnitZ, 200.0f, MoveDirectionTag::MOVE_Z);
					break;
			case(40):
				new JumpSwitchObject(layer8SwitchPos, jumpSwitchSize, Tag::JUMP_SWITCH);
				break;
			case(22):
				new SwitchBaseObject(layer8SwitchPos, switchBaseSize, Tag::GROUND, Tag::NEXT_SCENE_SWITCH);
				break;
			case(42):
				new MoveWallBlock(Vector3(layer8Pos.x, layer8Pos.y + 200.0f, layer8Pos.z - 100.0f), moveWallSize, Tag::NEXT_SCENE_MOVE_WALL, 300.0f,
					Vector3(layer8Pos.x, layer8Pos.y, layer8Pos.z - moveWallSize.z));
				break;

			}

			const unsigned int layer9 = layer9StageData[(int)iy][(int)ix];
			Vector3 layer9Pos = Vector3(offset * ix, -offset * iy, 1600);
			Vector3 layer9SwitchPos = Vector3(offset * ix, -offset * iy, 1501);

			switch (layer9)
			{
			case(71):
				new BoxObject(layer9Pos, blockSize, Tag::GROUND);
				break;
			}

			const unsigned int layer10 = layer10StageData[(int)iy][(int)ix];
			Vector3 layer10Pos = Vector3(offset * ix, -offset * iy, 1800);
			Vector3 layer10SwitchPos = Vector3(offset * ix, -offset * iy, 1701);

			switch (layer10)
			{
			case(70):
				new BoxObject(layer10Pos, blockSize, Tag::GROUND);
				break;
			}

			const unsigned int layer11 = layer11StageData[(int)iy][(int)ix];
			Vector3 layer11Pos = Vector3(offset * ix, -offset * iy, 2000);
			Vector3 layer11SwitchPos = Vector3(offset * ix, -offset * iy, 1901);

			switch (layer11)
			{
			case(69):
				new BoxObject(layer11Pos, blockSize, Tag::GROUND);
			}

			const unsigned int layer12 = layer12StageData[(int)iy][(int)ix];
			Vector3 layer12Pos = Vector3(offset * ix, -offset * iy, 2200);
			Vector3 layer12SwitchPos = Vector3(offset * ix, -offset * iy, 1901);

			switch (layer12)
			{
			case(20):
				new NextSceneObject(Vector3(layer12Pos.x, layer12Pos.y, layer12Pos.z), Tag::NEXT_SCENE_POINT);
				break;
			}
		}
	}

}
