#pragma once

#include "GameObject.h"
#include <glew.h>

class BoxCollider;
class Mesh;
class ChangeColorMeshComponent;

/*
@file SwitchBlock.h
@brief �X�C�b�`�̐����ƍX�V�������s��
*/


class SwitchBlock : public GameObject
{
public:
	// �R���X�g���N�^
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag);
	// �f�X�g���N�^
	~SwitchBlock();
	// �A�b�v�f�[�g
	void UpdateGameObject(float _deltaTime)override;

private:
	// ��悲�Ƃɕ����ꂽswitch�����ׂĉ����ꂽ���ǂ����`�F�b�N����֐�
	void ChackOnFlag(Tag& _Tag);
	// �������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�OnCollision
	void OnCollision(const GameObject& _hitObject)override;
	// �v���C���[�̑�������Ƃ�OnCollision
	void PlayerFootOnCollision(const GameObject& _hitObject);

	// ���b�V���R���|�[�l���g
	ChangeColorMeshComponent* meshComponent;
	// �������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�Collider
	BoxCollider* boxCollider;
	// �v���C���[�Ƃ̑�������pCollider
	BoxCollider* PlayerFootBoxCollider;
	// ���b�V������AABB�̍ő�_�ŏ��_�𓾂�Ƃ��Ɏg��
	Mesh* mesh;
	// Switch�����p�\��
	bool isAvailableSwitch;
	// Switch�̏����|�W�V�����ۑ��p
	Vector3 initPosition;
	// player��switch�ɏ���Ă��邩�ǂ���
	bool isOnPlayer;
	bool isHitPlayer;
	// �����̂��~�߂邩�ǂ���
	bool pushStop;
	// �F��ς��邩�ǂ���
	bool changeColorFlag;
	// �O�̃t���[���ŐF�ύX���s��ꂽ���ǂ���
	bool tmpChangeColorFlag;
	// switch�̒�~�ʒu
	float stopPoint;

};
