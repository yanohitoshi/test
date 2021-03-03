#include "GameClearEffectManeger.h"
#include "GameClearEffect.h"

GameClearEffectManeger::GameClearEffectManeger(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
{
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	particleCount = 0;
}

GameClearEffectManeger::~GameClearEffectManeger()
{
}

void GameClearEffectManeger::UpdateGameObject(float _deltaTime)
{
	if (owner->GetVelocity().z != 0 && owner->GetPosition().z >= 5500.0f)
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
		position = owner->GetPosition();
		
		if (frameCount % 15 == 0 && generateCount <= 8)
		{
			for (int i = 0; i < 10; i++)
			{
				++particleCount;
				//Vector3 randV((rand() % 300) / 10.0f - 5.0f, (rand() % 300) / 10.0f - 5.0f, (rand() % 100) / 10.0f);
				Vector3 randV((rand() % 300) / 10.0f - 5.0f, (rand() % 300) / 10.0f - 5.0f,0);

				velocity = randV * 0.1f;
				//”­¶ˆÊ’u‚ðÝ’è
				Vector3 vel = velocity;
				//ƒ‰ƒ“ƒ_ƒ€‚È’l‚ð“n‚·
				vel = vel + randV;
				vel.z *= -1.0f;
				if (i % 2 == 0)
				{
					vel.x *= -1.0f;
				}
				else if (i % 3 == 0)
				{
					vel.y *= -1.0f;
				}

				if (i % 4 == 0)
				{
					vel.y *= -1.0f;
				}
				else if (i % 6 == 0)
				{
					vel.x *= -1.0f;
				}
				//particle‚ð¶¬
				new GameClearEffect(position, vel);
			}
			++generateCount;
		}

		break;

	}

}
