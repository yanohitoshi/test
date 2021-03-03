#pragma once
#include "Math.h"
struct InputState;
enum SceneState;

/*
@file BaseScene.h
@brief Scene�̊��N���X
*/

class BaseScene
{
public:

	// �R���X�g���N�^�i���z�֐��j
	BaseScene() {};
	// �f�X�g���N�^�i���z�֐��j
	virtual ~BaseScene() {};

	/*
	@brief	�A�b�v�f�[�g�i���z�֐��j
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	virtual SceneState Update(const InputState& state) = 0;

protected:

	// ���C�g�pVector3�ϐ�
	Vector3 light;
	// �N���A��̃J�E���g
	int clearCount;
	// �؂�ւ��p�J�E���g
	int changeCount;
	// �V�[�����n�܂������ǂ����t���O
	bool startScene;
	// �R���e�j���[���ꂽ���t���O
	bool continueFlag;
	// �I���t���O
	bool endFlag;
	// ���C�g�𗎂Ƃ����ǂ����t���O
	bool lightDownFlag;


};

