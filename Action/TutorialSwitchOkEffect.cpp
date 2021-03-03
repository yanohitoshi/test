#include "TutorialSwitchOkEffect.h"

TutorialSwitchOkEffect::TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/touch_OK.png", 1.0f)
{
	// ParticleComponent������
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(false);
	particleComponent->SetScale(128);
	// �ϐ�������
	owner = _owner;
}

TutorialSwitchOkEffect::~TutorialSwitchOkEffect()
{
}

void TutorialSwitchOkEffect::UpdateGameObject(float _deltaTime)
{
	// �e�̂̃t���O�����ĕ`���؂�ւ���
	if (owner->GetSwitchFlag() == true)
	{
		particleComponent->SetVisible(true);
	}
	else if (owner->GetSwitchFlag() == false)
	{
		particleComponent->SetVisible(false);
	}

}
