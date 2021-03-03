#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
class SphereCollider;

/*
	 @enum AnimState
	�@�v���C���[�̃A�j���[�V�����̏��
*/
enum AnimState
{
	IDLE,
	WALK,
	RUN,
	JUMPLOOP,
	JUMPSTART,
	JUMPEND,
	DOWN,
	DOWN_LOOP,
	DOWN_UP,
	DOWN_OVER,
	PLAYER_DEAD,
	ITEMNUM
};

/*
@file PlayerObject.h
@brief �Q�[�����̃v���C���[
	   �Q�[�����̃v���C���[�̏������ƍX�V�������s��
*/
class PlayerObject : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObject();

	/*
	@fn �X�V����
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn ���͏���
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	*/
	void GameObjectInput(const InputState& _keyState)override;
	/*
	@fn �A�j���[�V�����̍X�V����
	*/
	void AnimationUpdate();
	/*
	@fn �߂荞�ݔ���
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);
	/*
	@fn �����߂�����
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec,const Tag& __pairTag);
	
	// �V�[���J�ڎ��Ɏg���t���O��getter
	static bool GetClearFlag() { return clearFlag; }
	static bool GetNextSceneFlag() { return nextSceneFlag; }
	static bool GetReStartFlag() { return reStartFlag; }

	// ���neffect���Ŏg�p����t���O�p��getter
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

private:

	//3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	Mesh* mesh;
	//�����蔻����s���N���X
	BoxCollider* boxCollider;
	SphereCollider* groundChackSphereCol;

	void OnCollision(const GameObject& _hitObject)override;
	void OnCollisionGround(const GameObject& _hitObject);

	//�����߂��Ɏg���v���C���[��AABB
	AABB playerBox;
	//-----------�A�j���[�V�����֌W------------//
	std::vector<const Animation*> animTypes;


	//�Đ�����A�j���[�V�����̏��
	int animState;
	//�؂�ւ�������𔻒f���邽�߂̕ϐ�
	int tmpAnimState;
	//-----------------------------------------//

	//���x�̒萔
	const float moveSpeed;
	//���͂����������ǂ������肷�邽�߂̃t���O
	bool inputFlag = false;
	//�E�����x�N�g��
	Vector3 rightVec;
	//�L�����N�^�[�̑O���x�N�g��
	Vector3 charaForwardVec;
	//�L�����N�^�[����]�����邩�O���x�N�g���Ɣ�r���邽�߂̃x�N�g��
	Vector3 tmpCharaForwardVec;
	//�����ɍ��킹�ĉ�]�����邽�߂̃x�N�g��
	Vector3 rotateVec;
	Vector3 firstPos;
	Vector3 startPos;
	Vector3 respownPos;

	//������Ă��鑬�x
	Vector3 pushedVelocity;
	//�d��
	static const float Gravity;
	//�����W�����v�͒萔
	const float FirstJumpPower;

	//�W�����v��
	float jumpPower;
	//�W�����v�����ǂ����̃t���O
	bool isJumping;
	//���������W�����v�{�^�������p�\���t���O
	bool isAvailableJumpKey;
	//�W�����v�ł��邩�t���O
	bool jumpFlag;
	//�W�����v�{�^����������Ă���Ԃ̃t���[���J�E���g
	int jumpFrameCount;
	//�W�����v�X�C�b�`�����������ǂ���
	bool switchJumpFlag;
	//�ڒn�t���O
	bool onGround;
	//�����Ԃ��ǂ���
	bool runFlag;
	// ���͂��\���ǂ���
	bool isAvailableInput;
	// ���͂��Ȃ��ԃJ�E���g
	int reStartCount;
	// �_�E����Ԃ��ǂ���
	bool downFlag;
	// �_�E�����R���e�B�j���[�I����YES���I�����ꂽ���ǂ���
	bool downUpFlag;
	// �_�E�����R���e�B�j���[�I����NO���I�����ꂽ���ǂ���
	bool downOverFlag;

	// �ŏI�X�e�[�W�p�̃N���A�t���O
	static bool clearFlag;
	// �ŏI�X�e�[�W�ȊO�ł̎��̃V�[���֑J�ڂ���t���O
	static bool nextSceneFlag;
	// ��莞�Ԉȏ���͂��Ȃ������ۂɃ^�C�g���֖߂�t���O
	static bool reStartFlag;
	// ���neffect�𔭐�������ۂɎg�p����t���O
	// JumpFlag�`�F�b�N�p
	static bool chackJumpFlag;
	// isJumping�`�F�b�N�p�i�W�����v�����ǂ����j
	static bool chackIsJumping;

	// ���񂾍ۂɂ������X�|�[�������Ȃ����߂̃J�E���g
	int reSpawnCount;
	// ���X�|�[���p�t���O
	bool reSpawnFlag;

	// dead��Ԃ���������Ȃ����m�F�p�t���O
	bool deadFlag;

};

