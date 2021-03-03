#include "MainCameraObject.h"
#include "CameraObjectBase.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "LineSegmentCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "FirstStageScene.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"

const float MainCameraObject::yawSpeed = 0.03f;
const float MainCameraObject::pitchSpeed = 0.025f;

MainCameraObject::MainCameraObject(const Vector3 _pos) :
	CameraObjectBase(false,Tag::CAMERA)
{
	SetPosition(_pos);
	float PI = Math::Pi;
	yaw = Math::ToRadians(180);
	pitch = Math::ToRadians(30);
	r = 700.0f;
	height = 0.0f;
	tmpMovePos = Vector3(0.0f,0.0f,0.0f);
	forwardVec = Vector3(1.0f, 0.0f, 0.0f);
	cameraTutorialCount = 0;
	boxcollider = new BoxCollider(this, ColliderComponent::CameraTag, GetOnCollisionFunc());
	AABB aabb = { Vector3(-80.0f,-80.0f,-50.0f),Vector3(80.0f,80.0f,50.0f) };
	boxcollider->SetObjectBox(aabb);
	tutorialCameraFlag = true;

}


MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	if (PlayerObject::GetClearFlag() == false && CountDownFont::timeOverFlag == false)
	{
		tmpMovePos.x = r * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
		tmpMovePos.y = r * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
		tmpMovePos.z = r * sinf(pitch) + height + lerpObjectPos.z;

		position = Vector3::Lerp(position , tmpMovePos, _deltaTime * 10.0f);
		SetPosition(position);
		Vector3 viewPosition = Vector3(lerpObjectPos.x, lerpObjectPos.y, lerpObjectPos.z + 100.0f);
		view = Matrix4::CreateLookAt(position, viewPosition, Vector3(0.0f,0.0f,1.0f));
		RENDERER->SetViewMatrix(view);

		forwardVec = lerpObjectPos - position;
		forwardVec.Normalize();
		forwardVec.z = 0.0f;
	}
	else if (PlayerObject::GetClearFlag() == true)
	{
		view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);
	}
	else if (CountDownFont::timeOverFlag == true)
	{
		yaw += 0.01f;
		tmpMovePos.x = 400 * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
		tmpMovePos.y = 400 * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
		tmpMovePos.z = r * sinf(pitch) + height + lerpObjectPos.z;

		position = Vector3::Lerp(position, tmpMovePos, _deltaTime * 7.0f);
		SetPosition(position);

		view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);

	}

}

void MainCameraObject::GameObjectInput(const InputState& _keyState)
{
	Vector2 rightAxis = Vector2(0.0f, 0.0f);
	rightAxis = _keyState.Controller.GetLAxisRightVec();

	if (PlayerObject::GetClearFlag() == false)
	{
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) == 1 ||
			rightAxis.x > 0)
		{
			yaw += yawSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT) == 1 ||
			rightAxis.x < 0)
		{
			yaw -= yawSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_UP) == 1 ||
			rightAxis.y < 0)
		{
			pitch -= pitchSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN) == 1 ||
			rightAxis.y > 0)
		{
			pitch += pitchSpeed;
		}

	}

	if (pitch > Math::ToRadians(60.0f))
	{
		pitch = Math::ToRadians(60.0f);
	}
	if (pitch < Math::ToRadians(5.0f))
	{
		pitch = Math::ToRadians(5.0f);
	}
}


/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObjectPos = _parentPos;
}


void MainCameraObject::OnCollision(const GameObject& _hitObject)
{
	AABB myAabb = boxcollider->GetWorldBox();
	FixCollision(myAabb, _hitObject.aabb, _hitObject.GetTag());
}

void MainCameraObject::FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	if (_pairTag == Tag::GROUND || _pairTag == Tag::WALL || _pairTag == Tag::FIRST_MOVE_WALL ||
		_pairTag == Tag::SECOND_MOVE_WALL || _pairTag == Tag::NEXT_SCENE_MOVE_WALL||
		_pairTag == Tag::CLEAR_SCENE_MOVE_WALL || _pairTag == Tag::TUTORIAL_MOVE_WALL)
	{
		Vector3 ment = Vector3(0, 0, 0);
		calcCollisionFixVec(myAABB, pairAABB, ment);
		SetPosition(position + ment);
	}

}
void MainCameraObject::calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
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
