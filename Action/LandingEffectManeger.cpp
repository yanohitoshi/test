#include "LandingEffectManeger.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

LandingEffectManeger::LandingEffectManeger(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	ChackOnFlag = false;
	tmpVelZ = 0.0f;
	generateFlag = false;
}

LandingEffectManeger::~LandingEffectManeger()
{
}

void LandingEffectManeger::UpdateGameObject(float _deltaTime)
{
	if (owner->GetVelocity().z == 0.0f && tmpVelZ != 0.0f && PlayerObject::GetChackJumpFlag() == false)
	{
		particleState = ParticleState::PARTICLE_ACTIVE;
		generateFlag = true;
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


		//particle‚ª”­¶‚·‚éƒtƒŒ[ƒ€‚ÌðŒŽ®‚ð‘‚­
		if (generateFlag == true)
		{
			position = owner->GetPosition();

			for (int i = 0; i < 8; i++)
			{
				if (i == 0)
				{
					velocity = Vector3(1.0f,0.0f,0.0f);
				}
				if (i == 1)
				{
					velocity = Vector3(0.0f,1.0f,0.0f);
				}
				if (i == 2)
				{
					velocity = Vector3(-1.0f, 0.0f, 0.0f);
				}
				if (i == 3)
				{
					velocity = Vector3(0.0f, -1.0f, 0.0f);
				}
				if (i == 4)
				{
					velocity = Vector3(1.0f, 1.0f, 0.0f);
				}
				if (i == 5)
				{
					velocity = Vector3(1.0f, -1.0f, 0.0f);
				}
				if (i == 6)
				{
					velocity = Vector3(-1.0f, 1.0f, 0.0f);
				}
				if (i == 7)
				{
					velocity = Vector3(-1.0f, -1.0f, 0.0f);
				}

				//particle‚ð¶¬
				new LandingEffect(position, velocity);
			}
			generateFlag = false;
		}

		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	tmpVelZ = owner->GetVelocity().z;

}
