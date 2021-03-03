#include "SandSmokeMakeManeger.h"
#include "ParticleEffectBase.h"
#include "SandSmokeParticle.h"

SandSmokeMakeManeger::SandSmokeMakeManeger(GameObject* _owner)
	:GameObject(false,Tag::PARTICLE)
{
	owner = _owner;
	position = owner->GetPosition();
	ownerSize = owner->GetScaleVec();
	frameCount = 0;
	position.x -= 40.0f;
	if (ownerSize.y == 1000.0f)
	{
		position.y -= 900.0f;
	}

	if (ownerSize.y == 1600.0f)
	{
		position.y -= 1500.0f;
	}
}

SandSmokeMakeManeger::~SandSmokeMakeManeger()
{
}

void SandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	if (owner->GetVelocity().z != 0)
	{
		particleState = ParticleState::PARTICLE_ACTIVE;
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

		++frameCount;
		if (ownerSize.y == 1000.0f)
		{
			if (frameCount % 3 == 0)
			{

				for (int i = 0; i < 10; i++)
				{
					Vector3 randV((rand() % 500) / 10.0f, (rand() % 20000) / 10.0f, (rand() % 100) / 10.0f);
					velocity = randV * 0.1f;
					velocity.x = -2.0f;
					velocity.z = 1.0f;
					velocity.y = 0.0f;

					//発生位置を設定
					Vector3 pos = position;
					//ランダムな値を渡す
					pos = pos + randV;
					//particleを生成
					new SandSmokeParticle(pos, velocity);

				}
			}
		}

		if (ownerSize.y == 1600.0f)
		{
			if (frameCount % 3 == 0)
			{

				for (int i = 0; i < 20; i++)
				{
					Vector3 randV((rand() % 500) / 10.0f, (rand() % 40000) / 10.0f, (rand() % 100) / 10.0f);
					velocity = randV * 0.1f;
					velocity.x = -2.0f;
					velocity.z = 1.0f;


					//発生位置を設定
					Vector3 pos = position;
					//ランダムな値を渡す
					pos = pos + randV;
					//particleを生成
					new SandSmokeParticle(pos, velocity);

				}
			}

		}


		break;
	}


}

