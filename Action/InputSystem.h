#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

/*
enum ButtonState
�{�^���̏�Ԃ�\��
*/
enum ButtonState
{
	//������Ă��Ȃ�
	None,		
	//������
	Pressed,	
	//������
	Released,	
	//������Ă���
	Held		
};

/*
@file KeyboardState.h�L�[�{�[�h�̓��͊Ǘ��N���X
*/
class KeyboardState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;
private:
	//���݂̃L�[�{�[�h�̓��͏��
	const Uint8* currState;
	//�P�t���[���O�̃L�[�{�[�h�̓��͏��
	Uint8 prevState[SDL_NUM_SCANCODES];
public://�Q�b�^�[�Z�b�^�[
	/*
	@brief	���݂̃L�[�̓��͏�Ԃ݂̂��擾����
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetKeyValue(SDL_Scancode _keyCode) const;
	bool GetKeyDownValue(SDL_Scancode _keyCode) const;

	/*
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_Scancode�̃L�[�R�[�h
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetKeyState(SDL_Scancode _keyCode) const;
};

/*
@file MouseState.h
@brief �}�E�X�̓��͊Ǘ��N���X
*/
class MouseState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;
private:
	//�}�E�X�̃|�W�V����
	Vector2 mousePos;
	//�X�N���[���z�C�[���̃X�N���[����
	Vector2 scrollWheel;
	// ���݂̃}�E�X�̓��͏��
	Uint32 currButtons;
	//�P�t���[���O�̃}�E�X�̓��͏��
	Uint32 prevButtons;
	// ���΃}�E�X���[�h���ǂ���
	bool isRelative;
public://�Q�b�^�[�Z�b�^�[

	/*
	@brief	���΃}�E�X���[�h���ǂ������擾����
	@return	true : ���΃��[�h , false , �ʏ탂�[�h
	*/
	bool IsRelative() const { return isRelative; }

	/*
	@brief	���݂̃}�E�X�̃|�W�V�������擾����
	@return	Position
	*/
	const Vector2& GetPosition() const { return mousePos; }

	/*
	@brief	���݂̃}�E�X�̃X�N���[���z�C�[���̏�Ԃ��擾����
	@return	�X�N���[���ʁiVector2�j
	*/
	const Vector2& GetScrollWheel() const { return scrollWheel; }

	/*
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_BUTTON�萔
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(int _button) const;

	/*
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_BUTTON�萔
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetButtonState(int _button) const;
};

/*
@file ControllerState.h
@brief �R���g���[���[�̓��͊Ǘ��N���X
*/
class ControllerState
{
public:
	// InputSystem����e�ՂɍX�V�ł���悤�ɂ���
	friend class InputSystem;
private:
	//���݂̃{�^���̓��͏��
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	//�P�t���[���O�̃{�^���̓��͏��
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];

	//���X�e�B�b�N�̏��
	float axisValues[SDL_CONTROLLER_AXIS_MAX];
	Vector2 lAxisLeft;
	Vector2 lAxisRight;
	float leftTriggerAxis;
	float rightTriggerAxis;
public://�Q�b�^�[�Z�b�^�[
	/*
	@brief	���݂̓��͏�Ԃ݂̂��擾����
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	true : ������Ă��� , false : ������Ă��Ȃ�
	*/
	bool GetButtonValue(SDL_GameControllerButton _button) const;

	/*
	@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
	@param	SDL_GameControllerButton�̃{�^���R�[�h
	@return	ButtonState�^�̌��݂̏��
	*/
	ButtonState GetButtonState(SDL_GameControllerButton _button) const;

	/*
	@brief �X�e�B�b�N�̓��͂�0~32767�ŕԂ�
	@param iAxis �ǂ̃X�e�B�b�N�̂ǂ̒l���擾���邩
		   (���X�e�B�b�N��X���擾...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
	@return �X�e�B�b�N�̓��͏��
	*/
	float GetAxisValue(const SDL_GameControllerAxis iAxis) const;
	/*
	@brief �X�e�B�b�N�̓��͂�0~1�ŕԂ�
	@return �X�e�B�b�N�̓��͏��
	*/
	const Vector2& GetLAxisLeftVec() const { return lAxisLeft; }
	const Vector2& GetLAxisRightVec() const { return lAxisRight; }

	const float& GetLeftTrigger() const { return leftTriggerAxis; }
	const float& GetRightTrigger() const { return rightTriggerAxis; }

};

/*
@struct InputState 
�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
*/
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};
/*
@file InputSystem.h
@brief ���͏����Ǘ�
*/
class InputSystem
{
public:
	/*
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize();

	/*
	@brief  �I������
	*/
	void Shutdown();

	/*
	@brief  Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
	*/
	void PrepareForUpdate();

	/*
	@brief  �t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
	*/
	void Update();

	/*
	@brief  SDL�C�x���g��InputSystem�ɓn��
	*/
	void ProcessEvent(union SDL_Event& _event);

private:

	/*
	@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
	@param	���͂��ꂽ�l��x�iint�j
	@param	���͂��ꂽ�l��y�iint�j
	@return	�t�B���^�����O���ꂽ�l
	*/
	Vector2 Filter2D(int _inputX, int _inputY);

	/*
	@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
	@param	���͂��ꂽ�l�iint�j
	@return	�t�B���^�����O���ꂽ�l
	*/
	float Filter1D(int _input);


	//�e���͋@��̓��͏�Ԃ��܂Ƃ߂����b�p�[�\����
	InputState state;
	//SDL�ŃR���g���[���[��F�����邽�߂̃N���X�|�C���^
	SDL_GameController* controller;
	//�R���g���[���[���ڑ����ꂽ��
	static bool controllerConnected;

public://�Q�b�^�[�Z�b�^�[
	/*
	@brief  ���݂̓��͏�Ԃ��擾����
	@return �iInputState�j�e���͏����܂Ƃ߂��\����
	*/
	const InputState& GetState() const { return state; }

	/*
	@brief  �}�E�X�̃��[�h��ݒ肷��
	@param	true : ���΃��[�h , false : �f�t�H���g���[�h
	*/
	void SetRelativeMouseMode(bool _value);

	static bool GetConnectedController() { return controllerConnected; }
};
