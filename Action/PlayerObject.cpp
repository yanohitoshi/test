#include "PlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "InputSystem.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlayerSandSmokeMakeManeger.h"
#include "JumpParticleEffectManeger.h"
#include "LandingEffectManeger.h"
#include "CountDownFont.h"

// 定数と静的メンバーの初期化
const float PlayerObject::Gravity = 6000.0f;
bool PlayerObject::clearFlag = false;
bool PlayerObject::nextSceneFlag = false;
bool PlayerObject::reStartFlag = false;
bool PlayerObject::chackJumpFlag = false;
bool PlayerObject::chackIsJumping = false;

PlayerObject::PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	,playerBox({ Vector3::Zero,Vector3::Zero })
	, FirstJumpPower(1100.0f)
	,moveSpeed(600.0f)
{

	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Vector3(1.2f, 1.2f, 1.2f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	SetScale(scale);
	SetPosition(_pos);

	firstPos = Vector3(position.x, position.y, 5000.0f);
	jumpPower = FirstJumpPower;
	//リスポ－ンするまでのカウント初期化
	reSpawnCount = 0;
	//リスポ－ンflag初期化
	reSpawnFlag = false;
	// リスポ－ンflag位置初期化
	respownPos = _pos;

	// 前方ベクトル初期化
	forwardVec = Vector3(0.0f, 0.0f, 0.0f);
	// キャラクターの前方ベクトル初期化
	charaForwardVec = Vector3(1.0f, 0.0f, 0.0f);
	// 前フレームでのキャラクターの前方ベクトル保存用ベクトル初期化
	tmpCharaForwardVec = Vector3(0.0f, 0.0f, 0.0f);
	// 右方向ベクトル初期化
	rightVec = Vector3(0.0f,0.0f,0.0f);
	// 回転ベクトル初期化
	rotateVec = Vector3(0.1f, 0.0f, 0.0f);
	// 回転ベクトルNormalize
	rotateVec.Normalize();
	// 押し出されたときにその速度を保存しキャラクターの速度に足すためのベクトル初期化
	pushedVelocity = Vector3::Zero;

	// 接地フラグ初期化
	onGround = false;
	// 入力フラグ初期化
	inputFlag = false;
	// 入力可能かフラグ初期化
	isAvailableInput = true;
	// 走り状態かフラグ初期化
	runFlag = false;

	// ジャンプフラグ初期化
	jumpFlag = false;
	// ジャンプ中かどうかフラグ初期化
	isJumping = false;
	// ジャンプが利用可能かフラグ初期化
	isAvailableJumpKey = false;
	// ジャンプ中のフレームをカウントする用のカウント初期化
	jumpFrameCount = 0;

	// ジャンプswitch用フラグ初期化
	switchJumpFlag = false;

	//clear判定フラグ
	clearFlag = false;
	reStartCount = 0;
	//アニメーションステータスの初期化
	animState = IDLE;
	tmpAnimState = IDLE;

	// ダウン・コンティニュー・deadフラグ初期化
	downFlag = false;
	downUpFlag = false;
	downOverFlag = false;
	deadFlag = false;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/robo_model/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/robo_model/SK_Rob.gpskel"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(AnimState::ITEMNUM);
	//アニメーションを読み込み
	animTypes[IDLE] = RENDERER->GetAnimation("Assets/Model/robo_model/Happy_Idle_Anim.gpanim", true);
	animTypes[WALK] = RENDERER->GetAnimation("Assets/Model/robo_model/Happy_Walk.gpanim", true);
	animTypes[RUN] = RENDERER->GetAnimation("Assets/Model/robo_model/Running.gpanim", true);
	animTypes[JUMPLOOP] = RENDERER->GetAnimation("Assets/Model/robo_model/Floating.gpanim", true);
	animTypes[JUMPSTART] = RENDERER->GetAnimation("Assets/Model/robo_model/Jump_up.gpanim", false);
	animTypes[JUMPEND] = RENDERER->GetAnimation("Assets/Model/robo_model/Landing.gpanim", false);
	animTypes[DOWN] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_down.gpanim", false);
	animTypes[DOWN_LOOP] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_Idle.gpanim", false);
	animTypes[DOWN_UP] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_up.gpanim", false);
	animTypes[DOWN_OVER] = RENDERER->GetAnimation("Assets/Model/robo_model/over_down.gpanim", false);
	animTypes[PLAYER_DEAD] = RENDERER->GetAnimation("Assets/Model/robo_model/Stunned.gpanim", false);



	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[IDLE], 1.0f);

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,ColliderComponent::PlayerTag, GetOnCollisionFunc());
	playerBox = mesh->GetBox();
	playerBox = { Vector3(-55.0f,-6.5f,0.0f),Vector3(55.0f,6.5f,179.0f) };
	boxCollider->SetObjectBox(playerBox);

	//接地判定用のsphereCollider
	groundChackSphereCol = new SphereCollider(this, ColliderComponent::GroundCheckTag, std::bind(&PlayerObject::OnCollisionGround, this, std::placeholders::_1));
	Sphere groundChackSphere = { Vector3(0.0f,0.0f,0.0f),5.0f };
	groundChackSphereCol->SetObjectSphere(groundChackSphere);

	// 砂ぼこりと着地時のeffectを持たせる
	new PlayerSandSmokeMakeManeger(this);
	new LandingEffectManeger(this);


}

PlayerObject::~PlayerObject()
{
	// 静的フラグの初期化
	clearFlag = false;
	nextSceneFlag = false;
	reStartFlag = false;
	chackJumpFlag = false;
	chackIsJumping = false;
}

void PlayerObject::UpdateGameObject(float _deltaTime)
{
	// アニメーション更新処理
	AnimationUpdate();

	// 接地中じゃなければ重力をかける（一定数以上かかったら止めて定数にする）
	if (onGround == false)
	{
		velocity.z -= Gravity * _deltaTime;
		if (velocity.z <= -2000.0f)
		{
			velocity.z = -2000.0f;
		}
	}
	
	// ほかのオブジェクトから影響を受けた速度をプレイヤーの速度に追加
	velocity = velocity + pushedVelocity;
	// positionに速度を足してキャラクターを動かす
	position = (position + velocity * _deltaTime );
	SetPosition(position);

	//カメラにplayerのpositionを渡す
	if (clearFlag == false && nextSceneFlag == false && position.z >= -500.0f)
	{
		mainCamera->SetLerpObjectPos(position);
	}

	// RENDERERに現在のポジションを送る
	RENDERER->SetPlayerPositon(position);
	
	// フレームの最後に接地判定と押されている速度を初期化
	onGround = false;
	pushedVelocity = Vector3::Zero;

}

void PlayerObject::GameObjectInput(const InputState& _keyState)
{
	//前のフレームと今のフレームを比較するために保存
	tmpAnimState = animState;

	//今カメラが向いている方向をplayerに渡す
	forwardVec = mainCamera->GetCameraVec();

	//カメラの向きから右方向を計算
	rightVec = Vector3::Cross(forwardVec, Vector3(0.0f, 0.0f, 1.0f));

	// スタート時のカウントダウンが終わったら入力可能状態にする
	if (CountDownFont::countStartFlag == true)
	{
		isAvailableInput = true;
	}
	else if (CountDownFont::countStartFlag == false || CountDownFont::timeOverFlag == true)
	{
		// カウントダウンが終わっていないまたはタイムオーバーになったら入力を切る
		isAvailableInput = false;
	}

	// クリア状態でなく入力可能状態でタイムオーバーでも死んでもいなければ入力処理を行う
	if (clearFlag == false && isAvailableInput == true && 
		CountDownFont::timeOverFlag == false && deadFlag == false)
	{
		// コントローラーが接続されていなければ
		if (InputSystem::GetConnectedController() == 0)
		{
			Vector3 dirVec = Vector3(0.0f, 0.0f, 0.0f);
			// Wで前進
			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
			{
				dirVec += forwardVec;
				inputFlag = true;
			}
			// Sで後退
			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
			{
				dirVec -= forwardVec;
				inputFlag = true;
			}
			// Dで右移動
			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
			{
				dirVec -= rightVec;
				inputFlag = true;
			}
			// Aで左移動
			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
			{
				dirVec += rightVec;
				inputFlag = true;
			}

			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 &&
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 0 &&
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 &&
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 0 )
			{
				inputFlag = false;
			}

			// 左右シフトキーどちらか入力で走る
			if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT) == 1 ||
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RSHIFT) == 1)
			{
				runFlag = true;
			}
			else
			{
				runFlag = false;
			}

			charaForwardVec = dirVec;

			//入力があったら速度にキャラクターの方向と動くスピードを掛けたものを代入
			//ここでzに速度を足すとジャンプに影響するのでx,yのみに代入
			//入力がない間は速度を0に
			if (inputFlag == true)
			{
				velocity.x = charaForwardVec.x * moveSpeed;
				velocity.y = charaForwardVec.y * moveSpeed;

				if (runFlag == true)
				{
					velocity.x = charaForwardVec.x * moveSpeed * 2.0f;
					velocity.y = charaForwardVec.y * moveSpeed * 2.0f;
				}
			}
			else
			{
				velocity.x = 0.0f;
				velocity.y = 0.0f;
			}

			//入力があったらキャラクターを回転（回転する必要がある場合）
			if (inputFlag == true)
			{
				if (tmpCharaForwardVec != charaForwardVec)
				{
					charaForwardVec.Normalize();
					//回転
					rotateVec = Vector3::Lerp(rotateVec, charaForwardVec, 0.2f);
					RotateToNewForward(rotateVec);
				}
			}

			// 接地中かつジャンプ中ではない時
			if (onGround == true && jumpFlag == false)
			{
				// SPACEキーもしくはスイッチジャンプフラグがtrueだったら
				if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed || switchJumpFlag == true)
				{
					// ジャンプフラグをtrueにしジャンプ使用中かフラグをtrueにする
					jumpFlag = true;
					isJumping = true;
					// ジャンプstartのアニメーションを再生しアニメーションステータスをJUMPSTARTに更新
					skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
					animState = JUMPSTART;
				}

			}

			// ジャンプキーが離されたらジャンプ使用可能フラグとジャンプ使用中フラグをおろしジャンプパワーを初期値に戻す
			if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
			{
				isAvailableJumpKey = false;
				isJumping = false;
				jumpPower = FirstJumpPower;
			}

			if (isAvailableJumpKey == true && isJumping == true || switchJumpFlag == true && isAvailableJumpKey == true)
			{
				if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Held || switchJumpFlag == true)
				{
					++jumpFrameCount;
					jumpFlag = true;
					velocity.z = jumpPower;

					if (jumpFrameCount > 0 && jumpFrameCount < 13 && switchJumpFlag == false)
					{
						jumpPower += 150.0f;
					}
					else if (switchJumpFlag == true && jumpFrameCount < 17)
					{
						jumpPower += 150.0f;
					}
					else
					{
						isAvailableJumpKey = false;
						isJumping = false;
						switchJumpFlag = false;
					}
				}
			}
		}
		
		// コントローラーが接続されていたら
		if (InputSystem::GetConnectedController() == 1)
		{
			//Axisの値をとる32700~-32700
			float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
			float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);


			//アナログスティックのキー入力を取得
			Vector2 Axis = Vector2(0.0f, 0.0f);
			Axis = _keyState.Controller.GetLAxisLeftVec();

			//実際に動かしたい軸がずれているので補正
			Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

			//入力があるか
			if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
			{
				// 方向キーの入力値とカメラの向きから、移動方向を決定
				charaForwardVec = forwardVec * axis.x + rightVec * axis.y;
				charaForwardVec.Normalize();
				inputFlag = true;
				//アナログスティックの入力状態で歩きか走りかを判定
				if (ALX >= 28000.0f || ALX <= -28000.0f || ALY >= 28000.0f || ALY <= -28000.0f)
				{
					runFlag = true;
				}
				else 
				{
					runFlag = false; 
				}
			}
			else
			{
				inputFlag = false;
			}
			//入力があったら速度にキャラクターの方向と動くスピードを掛けたものを代入
			//ここでzに速度を足すとジャンプに影響するのでx,yのみに代入
			//入力がない間は速度を0に
			if (inputFlag == true)
			{
				velocity.x = charaForwardVec.x * moveSpeed;
				velocity.y = charaForwardVec.y * moveSpeed;

				if (runFlag == true)
				{
					velocity.x = charaForwardVec.x * moveSpeed * 2.0f;
					velocity.y = charaForwardVec.y * moveSpeed * 2.0f;
				}
			}
			else
			{
				velocity.x = 0.0f;
				velocity.y = 0.0f;
			}

			//入力があったらキャラクターを回転（回転する必要がある場合）
			if (inputFlag == true)
			{
				if (tmpCharaForwardVec != charaForwardVec)
				{
					charaForwardVec.Normalize();
					//回転
					rotateVec = Vector3::Lerp(rotateVec, charaForwardVec, 0.2f);
					RotateToNewForward(rotateVec);
				}
			}

			if (onGround == true && jumpFlag == false)
			{
				if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
					switchJumpFlag == true)
				{
					jumpFlag = true;
					isJumping = true;
					skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
					animState = JUMPSTART;
				}

			}

			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released )
			{
				isAvailableJumpKey = false;
				isJumping = false;
				jumpPower = FirstJumpPower;
			}


			if (isAvailableJumpKey == true && isJumping == true || switchJumpFlag == true && isAvailableJumpKey == true)
			{
				if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
					_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
					switchJumpFlag == true)
				{
					++jumpFrameCount;
					jumpFlag = true;
					velocity.z = jumpPower;

					if (jumpFrameCount > 0 && jumpFrameCount < 12 && switchJumpFlag == false)
					{
						jumpPower += 100.0f;
					}
					else if (switchJumpFlag == true && jumpFrameCount < 14)
					{
						jumpPower += 150.0f;
					}
					else
					{
						isAvailableJumpKey = false;
						isJumping = false;
						switchJumpFlag = false;
					}
				}
			}

		}

	}

	if (CountDownFont::timeOverFlag == true)
	{
		isAvailableInput = false;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		downFlag = true;

		if (downUpFlag == false && downOverFlag == false)
		{
			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
			{
				downUpFlag = true;
			}
			else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
					 _keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
				 {
					downOverFlag = true;
				 }
		}
	}

	chackJumpFlag = jumpFlag;
	chackIsJumping = isJumping;

	if (deadFlag == true)
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	if (deadFlag == true && reSpawnFlag == false)
	{
		reSpawnFlag = true;
	}

	if (reSpawnFlag == true)
	{
		++reSpawnCount;
		if (reSpawnCount >= 120)
		{
			position = respownPos;
			SetPosition(position);
			mainCamera->ReSetYaw();
			reSpawnCount = 0;
			reSpawnFlag = false;
			deadFlag = false;
		}
	}

	// 一定時間入力が無かったらタイトルに戻る
	if (inputFlag == false && jumpFlag == false)
	{
		++reStartCount;
		if (reStartCount >= 10000)
		{
			reStartFlag = true;
		}
	}
	else
	{
		reStartCount = 0;
	}

}

void PlayerObject::AnimationUpdate()
{
	// 死亡状態だったら
	if (deadFlag == true)
	{
		if (animState != PLAYER_DEAD && animState != DOWN_LOOP)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[PLAYER_DEAD], 1.0f);
			animState = PLAYER_DEAD;
		}
		else if (!skeltalMeshComponent->IsPlaying() && animState == DOWN)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[DOWN_LOOP], 1.0f);
			animState = DOWN_LOOP;
		}
	}

	//前回の当たり判定処理で下に地面がなかったらジャンプ中へ移行する
	if (!jumpFlag && !onGround)
	{
		if (animState != JUMPLOOP)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPLOOP], 1.0f);
			animState = JUMPLOOP;
		}

		return;
	}
	if (isJumping && downFlag == false && deadFlag == false || 
		jumpFlag == true && downFlag == false && deadFlag == false)
	{
		// JUMP開始からJumpLoopへ
		if (animState == JUMPSTART)
		{
			if (!skeltalMeshComponent->IsPlaying())
			{
				skeltalMeshComponent->PlayAnimation(animTypes[JUMPLOOP], 1.0f);
				animState = JUMPLOOP;
			}
		}
		return;
	}


	// 待機アニメ開始
	if (!inputFlag)
	{
		if (animState == JUMPEND)
		{
			if (!skeltalMeshComponent->IsPlaying())
			{
				skeltalMeshComponent->PlayAnimation(animTypes[IDLE], 1.0f);
				animState = IDLE;
			}
		}
		else if (animState != IDLE && downFlag == false && deadFlag == false)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[IDLE], 1.0f);
			animState = IDLE;
			return;
		}
	}
	else
	{
		// ジャンプ終了アニメからのRUN開始
		if (animState == JUMPEND)
		{
			if (!skeltalMeshComponent->IsPlaying())
			{
				if (runFlag == true && downFlag == false)
				{
					skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
					animState = RUN;
				}
				else if(runFlag == false && downFlag == false)
				{
					skeltalMeshComponent->PlayAnimation(animTypes[WALK], 1.0f);
					animState = WALK;
				}
			}
		}

		// RUNアニメ開始
		if (animState != WALK && runFlag == false && downFlag == false && deadFlag == false)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[WALK], 1.0f);
			animState = WALK;
			return;
		}
		else if (animState != RUN && runFlag == true && downFlag == false && deadFlag == false)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
			animState = RUN;
			return;
		}

	}

	// タイムオーバー時のアニメーション遷移
	if (downFlag == true)
	{
		if (animState != DOWN && animState != DOWN_LOOP && downOverFlag == false && downUpFlag == false)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[DOWN], 1.0f);
			animState = DOWN;
		}
		else if (!skeltalMeshComponent->IsPlaying() && animState == DOWN)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[DOWN_LOOP], 1.0f);
			animState = DOWN_LOOP;
		}

		if (animState == DOWN_LOOP && downUpFlag == true)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[DOWN_UP], 1.0f);
			animState = DOWN_UP;
			if (!skeltalMeshComponent->IsPlaying() && animState == DOWN_UP)
			{
				skeltalMeshComponent->PlayAnimation(animTypes[IDLE], 1.0f);
				animState = IDLE;
			}
		}
		else if (animState == DOWN_LOOP && downOverFlag == true)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[DOWN_OVER], 1.0f);
			animState = DOWN_OVER;
			if (!skeltalMeshComponent->IsPlaying() && animState == DOWN_OVER)
			{
				skeltalMeshComponent->PlayAnimation(animTypes[IDLE], 1.0f);
				animState = IDLE;
			}
		}

	}

}

/*
@fn めり込み判定
*/
void PlayerObject::FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	if (_pairTag == Tag::GROUND || _pairTag == Tag::WALL || _pairTag == Tag::FIRST_MOVE_WALL ||
		_pairTag == Tag::SECOND_MOVE_WALL || _pairTag == Tag::TUTORIAL_MOVE_WALL ||
		_pairTag == Tag::NEXT_SCENE_MOVE_WALL || _pairTag == Tag::CLEAR_SCENE_MOVE_WALL ||
		_pairTag == Tag::MOVE_GROUND || _pairTag == Tag::PUSH_BOARD || _pairTag == Tag::PUSH_BOX ||
		_pairTag == Tag::TUTORIAL_SWITCH || _pairTag == Tag::FIRST_SWITCH ||
		_pairTag == Tag::SECOND_SWITCH || _pairTag == Tag::NEXT_SCENE_SWITCH ||
		_pairTag == Tag::CLEAR_SCENE_SWITCH)
	{
		Vector3 ment = Vector3(0, 0, 0);
		playerCalcCollisionFixVec(myAABB, pairAABB, ment, _pairTag);
		SetPosition(position + ment);
	}
}

void PlayerObject::OnCollision(const GameObject& _hitObject)
{
	if (onGround == false)
	{
		playerBox = boxCollider->GetWorldBox();
		FixCollision(playerBox, _hitObject.aabb, _hitObject.GetTag());
	}

	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND ||
		_hitObject.GetTag() == Tag::PUSH_BOARD || _hitObject.GetTag() == Tag::PUSH_BOX ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		pushedVelocity = _hitObject.GetVelocity();
	}

	if (_hitObject.GetTag() == Tag::CLEAR_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::CLEAR_SCENE_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			clearFlag = true;
		}

	}

	if (_hitObject.GetTag() == Tag::NEXT_SCENE_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::NEXT_SCENE_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			nextSceneFlag = true;
		}
	}

	if (_hitObject.GetTag() == Tag::TUTORIAL_CLEAR_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::TUTORIAL_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			nextSceneFlag = true;
		}
	}

	if (_hitObject.GetTag() == Tag::RESPOWN_POINT)
	{
		respownPos = Vector3::Zero;
		respownPos = _hitObject.GetPosition();
	}

	if (_hitObject.GetTag() == Tag::NEEDLE_PANEL)
	{
		deadFlag = true;
	}

}

void PlayerObject::OnCollisionGround(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND || 
		_hitObject.GetTag() == Tag::PUSH_BOARD || _hitObject.GetTag() == Tag::PUSH_BOX ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		onGround = true;

		if (jumpFlag == false && onGround == true)
		{
			velocity.z = 0.0f;
			jumpFrameCount = 0;
		}

		if (animState == JUMPLOOP)
		{
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPEND], 1.0f);
			animState = JUMPEND;
		}

		if (jumpFlag == true)
		{
			jumpFlag = false;
			isAvailableJumpKey = true;
			jumpPower = FirstJumpPower;
		}
		switchJumpFlag = false;
	}

	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		pushedVelocity = _hitObject.GetVelocity();
	}

	if (_hitObject.GetTag() == Tag::JUMP_SWITCH && jumpFlag == false)
	{
		if (switchJumpFlag == false)
		{
			jumpFrameCount = 0;
			jumpPower = FirstJumpPower;
			switchJumpFlag = true;

		}
	}
}


/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
//@param _calcFixVec 移動物体の補正差分ベクトル
*/
void PlayerObject::playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec,const Tag& __pairTag)
{
	_calcFixVec = Vector3(0, 0, 0);

	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}

