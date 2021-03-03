#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include <unordered_map>
#include "Game.h"

class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;

/*
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum State
{
	//�A�N�e�B�u
	Active,
	//�X�V����~���Ă���
	Paused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	Dead
};

/*
	@enum�@GameObject�^�O
	object���Ȃ�Ȃ̂��̔��ʂɎg�p
*/
enum Tag
{
	OTHER,
	CAMERA,
	PLAYER,
	GROUND,
	MOVE_GROUND,
	WALL,
	NEEDLE,
	NEEDLE_PANEL,
	PUSH_BOARD,
	PUSH_BOX,
	FIRST_MOVE_WALL,
	SECOND_MOVE_WALL,
	NEXT_SCENE_MOVE_WALL,
	CLEAR_SCENE_MOVE_WALL,
	TUTORIAL_MOVE_WALL,
	TUTORIAL_SWITCH,
	FIRST_SWITCH,
	SECOND_SWITCH,
	NEXT_SCENE_SWITCH,
	CLEAR_SCENE_SWITCH,
	JUMP_SWITCH,
	SWITCH_BASE,
	GROUND_CHECK,
	SCENE,
	CLEAR_POINT,
	NEXT_SCENE_POINT,
	RESPOWN_POINT,
	TUTORIAL_CLEAR_POINT,
	UI,
	TITLE_OBJECT,
	TITLE_PLAYER,
	PARTICLE,
};

enum MoveDirectionTag
{
	MOVE_X,
	MOVE_Y,
	MOVE_Z
};


/*
@enum �Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
*/
enum PauzingEvent
{
	//�{�X�̓��ꉉ�o
	SummonMageEvent,
	//�|�[�Y��ʒ�
	PausingEvent,
	//�v���C���[�����j����Ă��܂����ۂ̉��o
	DeadPlayerEvent,
	//�Q�[���I�[�o�[���̉��o DeadPlayerEvent�Ɗ֘A
	GameOverEvent,
	//�Q�[���I�u�W�F�N�g�̍X�V���s���Ă���B
	NoneEvent
};

class GameObject
{
public:
	/*
	@param	�Q�[���N���X�̃|�C���^
	*/
	GameObject(bool _reUseGameObject,const Tag _objectTag);
	virtual ~GameObject();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();
	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��
	@param	scale
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	float GetScale() { return scale.x; }
	Vector3 GetScaleVec() {return scale;}
	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	Tag GetTag() const { return tag; }
		
	int GetObjectId() { return myObjectId; };
	static int GetTotalObjectId() { return gameObjectId; };


	bool GetReUseGameObject() { return reUseObject; }

	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	void RotateToNewForward(const Vector3& forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera(const Vector3 _pos);

	/*
	@fn �ÓI��titleCamera�𐶐�����
	*/
	static void CreateTitleCamera(const Vector3 _pos);

	/*
	@brief�@�X�C�b�`�p�t���O��getter
	@return	onFlag
	*/
	bool GetSwitchFlag() { return onFlag; }

	/*
	@brief�@tag���g�p����GameObject��T�����߂̊֐�
	@return	std::vector<GameObject*>��Ԃ�
	*/
	static std::vector<GameObject*> FindGameObject(Tag _tag);

	/*
	@brief�@�g�p�����S�Ă�GameObject�̍폜
	*/
	static 	void RemoveUsedGameObject();

	/*
	@brief�@Velocity��gettta�֐�
	@param	velocity(Vector3�^)
	*/
	const Vector3& GetVelocity() const { return velocity; }

	AABB aabb;

protected:

	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

	//�Q�[�������C���J����
	static class MainCameraObject* mainCamera;
	static class TitleCameraObject* titleCamera;
	//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent pauzingEvent;

	//�Q�[���I�u�W�F�N�g�̏��
	State state;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag tag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int gameObjectId;
	//���̃Q�[���I�u�W�F�N�g��ID
	const int myObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	Matrix4 worldTransform;
	Vector3 velocity;
	Vector3 forwardVec;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool recomputeWorldTransform;

	//switch�p�t���O
	bool onFlag;

	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;

private:

	/*
	@brief�@GameObject�̒ǉ�
	@param	�ǉ�����GameObject�̃|�C���^
	*/
	static void AddGameObject(GameObject* _object);
	/*
	@brief�@GameObject�̍폜
	@param	�폜����GameObject�̃|�C���^
	*/
	static void RemoveGameObject(GameObject* _object);


	//�V�[�����ׂ��ۂɊJ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool reUseObject;
	static std::vector<GameObject*> pendingGameObjects;
	static std::unordered_map<Tag, std::vector<GameObject*>> gameObjectMap;
	static bool updatingGameObject;

	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	friend void ProcessInputs(const InputState & _state);

};

