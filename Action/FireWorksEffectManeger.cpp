#include "FireWorksEffectManeger.h"
#include "FierWorksEffect.h"
FireWorksEffectManeger::FireWorksEffectManeger(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
{
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateFlag = true;
	particleCount = 0;
	crystalColor = CrystalColor::WHITE;
}

FireWorksEffectManeger::~FireWorksEffectManeger()
{
}

void FireWorksEffectManeger::UpdateGameObject(float _deltaTime)
{
	if (owner->GetState() == State::Dead)
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


		if (generateFlag == true)
		{
			for (int i = 0; i < 24; i++)
			{
				++particleCount;
				Vector3 randV((rand() % 100) / 10.0f, (rand() % 100) / 10.0f, (rand() % 100) / 10.0f);
				velocity = randV * 0.1f;

				//Vector3 randC((rand() % 10) / 10.0f , (rand() % 10) / 10.0f , (rand() % 10) / 10.0f);

				//”­¶ˆÊ’u‚ðÝ’è
				Vector3 vel = velocity;
				//ƒ‰ƒ“ƒ_ƒ€‚È’l‚ð“n‚·
				vel = vel + randV;
				vel.z *= -1.0f;

				if (i % 2 == 0)
				{
					vel.x *= -1.0f;
					crystalColor = CrystalColor::WHITE;
				}
				
				if (i % 4 == 0)
				{
					vel.y *= -1.0f;
					crystalColor = CrystalColor::RED;
				}
				
				if (i % 6 == 0)
				{
					vel.y *= -1.0f;
					crystalColor = CrystalColor::BLUE;
				}
				
				if (i % 8 == 0)
				{
					vel.x *= -1.0f;
					crystalColor = CrystalColor::GREEN;
				}

				//particle‚ð¶¬
				new FierWorksEffect(position, vel, crystalColor);
			}
			generateFlag = false;
		}

		break;

	}

}
