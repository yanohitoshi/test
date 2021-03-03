#include "PlayerSandSmokeMakeManeger.h"
#include "PlayerSandSmokeEffect.h"


PlayerSandSmokeMakeManeger::PlayerSandSmokeMakeManeger(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
{
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
	effectPosition = Vector3::Zero;
}

PlayerSandSmokeMakeManeger::~PlayerSandSmokeMakeManeger()
{
}

void PlayerSandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	if (owner->GetVelocity().x != 0 && owner->GetVelocity().z == 0 
		|| owner->GetVelocity().y != 0 && owner->GetVelocity().z == 0)
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
		generateCount = 0;
		break;

	case PARTICLE_ACTIVE:

		position = owner->GetPosition();

		++frameCount;

		if (frameCount % 10 == 0 && owner->GetVelocity().x > 600.0 ||
			frameCount % 10 == 0 && owner->GetVelocity().y > 600.0 ||
			frameCount % 10 == 0 && owner->GetVelocity().x < -600.0 ||
			frameCount % 10 == 0 && owner->GetVelocity().y < -600.0)
		{
			++generateCount;
			if (generateCount % 2 == 0)
			{
				if (owner->GetVelocity().x > 1.0)
				{
					effectPosition = position;
					effectPosition.y += 30.0f;
				}
				else if (owner->GetVelocity().x < -1.0)
				{
					effectPosition = position;
					effectPosition.y -= 30.0f;
				}
				else if (owner->GetVelocity().y > 1.0)
				{
					effectPosition = position;
					effectPosition.x += 30.0f;
				}
				else if (owner->GetVelocity().y < -1.0)
				{
					effectPosition = position;
					effectPosition.x -= 30.0f;
				}

			}
			else
			{
				if (owner->GetVelocity().x > 1.0)
				{
					effectPosition = position;
					effectPosition.y -= 30.0f;
				}
				else if (owner->GetVelocity().x < -1.0)
				{
					effectPosition = position;
					effectPosition.y += 30.0f;
				}
				else if (owner->GetVelocity().y > 1.0)
				{
					effectPosition = position;
					effectPosition.x -= 30.0f;
				}
				else if (owner->GetVelocity().y < -1.0)
				{
					effectPosition = position;
					effectPosition.x += 30.0f;
				}

			}
			//�I�[�i�[�̑��x�����炤
			Vector3 vel = owner->GetVelocity();
			vel.Normalize();
			//���x���t�����ɂ���
			vel = vel * -1.0;
			//particle�𐶐�
			new PlayerSandSmokeEffect(effectPosition, vel,true);
		}

		break;

	}

}
