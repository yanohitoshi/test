#include "CrystalEffectManager.h"
#include "CrystalDefaultEffect.h"


CrystalEffectManager::CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor)
	:GameObject(false, Tag::PARTICLE)
{
	crystalColor = _crystalColor;
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	position.z -= 100.0f;
	frameCount = 0;
	activeFrameCount = 0;
	revers = false;
	tmpMovePos = Vector3::Zero;
	r = 150.0f;
	if (crystalColor == CrystalColor::WHITE)
	{
		yaw = Math::ToRadians(0);
	}
	else if (crystalColor == CrystalColor::RED)
	{
		yaw = Math::ToRadians(90);
	}
	else if (crystalColor == CrystalColor::BLUE)
	{
		yaw = Math::ToRadians(180);
	}
	else if (crystalColor == CrystalColor::GREEN)
	{
		yaw = Math::ToRadians(270);
	}
}

CrystalEffectManager::~CrystalEffectManager()
{
}

void CrystalEffectManager::UpdateGameObject(float _deltaTime)
{
	yaw += yawSpeed;

	tmpMovePos.x = r * cosf(yaw) + owner->GetPosition().x;
	tmpMovePos.y = r * sinf(yaw) + owner->GetPosition().y;
	tmpMovePos.z = owner->GetPosition().z - 100.0f;
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * 10.0f);
	SetPosition(position);

	++activeFrameCount;

	if (activeFrameCount  >= 8)
	{
		particleState = ParticleState::PARTICLE_ACTIVE;
		activeFrameCount = 0;
	}
	else
	{
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	switch (particleState)
	{
	case (PARTICLE_DISABLE):
		break;
	case PARTICLE_ACTIVE:

		Vector3 vel;
		Vector3 randV((rand() % 100) / 10.0f, (rand() % 100) / 10.0f, (rand() % 100) / 10.0f + 2.0f);
		velocity = randV * 0.1f;
		//発生位置を設定
		vel = velocity;
		//ランダムな値を渡す
		vel = vel + randV;
		vel.x = 0.0f;
		vel.y = 0.0f;
		if (revers)
		{
			vel.x *= -1.0f;
			vel.y *= -1.0f;
			revers = false;
		}
		else
		{
			revers = true;
		}

		////発生位置を設定
		//Vector3 vel = owner->GetVelocity();
		//vel.Normalize();
		////ランダムな値を渡す
		//vel = vel * -1.0;

		Vector3 randPos((rand() % 100) / 10.0f, (rand() % 100) / 10.0f, (rand() % 100) / 10.0f + 2.0f);
		Vector3 pos = randPos * 0.1f;
		pos = pos + position;


		//particleを生成
		new CrystalDefaultEffect(pos, vel,crystalColor);

		break;

	}

}
