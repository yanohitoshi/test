#include "SwitchEffectMakeManeger.h"
#include "SwitchParticleEffect.h"

SwitchEffectMakeManeger::SwitchEffectMakeManeger(GameObject* _owner)
	: GameObject(false,Tag::PARTICLE)
{
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	ChackOnFlag = false;
	tmpChackOnFlag = false;
	generateFlag = false;
}

SwitchEffectMakeManeger::~SwitchEffectMakeManeger()
{
}

void SwitchEffectMakeManeger::UpdateGameObject(float _deltaTime)
{

	ChackOnFlag = owner->GetSwitchFlag();

	if (ChackOnFlag != tmpChackOnFlag)
	{
		particleState = ParticleState::PARTICLE_ACTIVE;
		generateFlag = true;
	}
	

	switch (particleState)
	{

	case (PARTICLE_DISABLE):
		break;

	case PARTICLE_ACTIVE:


		//particle����������t���[���̏�����������
		if (generateFlag == true)
		{
			for (int i = 0; i < 15; i++)
			{
				Vector3 randV((rand() % 100) / 10.0f , (rand() % 100) / 10.0f, (rand() % 100)/ 10.0f + 2.0f);
				velocity = randV * 0.1f;
				//�����ʒu��ݒ�
				Vector3 vel = velocity;
				//�����_���Ȓl��n��
				vel = vel + randV;
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
				//particle�𐶐�
				position = owner->GetPosition();
				new SwitchParticleEffect(position, vel);
			}
			generateFlag = false;
		}

		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	tmpChackOnFlag = ChackOnFlag;

}

