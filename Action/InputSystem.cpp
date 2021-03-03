#include "InputSystem.h"
#include <SDL.h>
#include <cstring>
#include <stdio.h>
#include <limits.h>

bool InputSystem::controllerConnected = 0;

/*
@brief	���݂̃L�[�̓��͏�Ԃ݂̂��擾����
@param	SDL_Scancode�̃L�[�R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return currState[_keyCode] == 1;
}

bool KeyboardState::GetKeyDownValue(SDL_Scancode _keyCode) const
{
	if (prevState[_keyCode] == 0 && currState[_keyCode] == 1)
	{
		return true;
	}
	return false;
}

/*
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_Scancode�̃L�[�R�[�h
@return	ButtonState�^�̌��݂̏��
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (prevState[_keyCode] == 0)
	{
		if (currState[_keyCode] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currState[_keyCode] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	���݂̓��͏�Ԃ݂̂��擾����
@param	SDL_BUTTON�萔
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool MouseState::GetButtonValue(int _button) const
{
	return (SDL_BUTTON(_button) & currButtons) == 1;
}

/*
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_BUTTON�萔
@return	ButtonState�^�̌��݂̏��
*/
ButtonState MouseState::GetButtonState(int _button) const
{
	int mask = SDL_BUTTON(_button);
	if ((mask & prevButtons) == 0)
	{
		if ((mask & currButtons) == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if ((mask & currButtons) == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	���݂̓��͏�Ԃ݂̂��擾����
@param	SDL_GameControllerButton�̃{�^���R�[�h
@return	true : ������Ă��� , false : ������Ă��Ȃ�
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton _button) const
{
	return currButtons[_button] == 1;
}

/*
@brief	���݂�1�t���[���O�̏�Ԃ���ButtonState��Ԃ�
@param	SDL_GameControllerButton�̃{�^���R�[�h
@return	ButtonState�^�̌��݂̏��
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton _button) const
{
	if (prevButtons[_button] == 0)
	{
		if (currButtons[_button] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (currButtons[_button] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

float ControllerState::GetAxisValue(const SDL_GameControllerAxis iAxis) const
{
	return axisValues[iAxis];
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool InputSystem::Initialize()
{
	//�L�[�{�[�h�̏���������
	//���̃L�[�{�[�h�̏�Ԃ����蓖�Ă�
	state.Keyboard.currState = SDL_GetKeyboardState(NULL);
	//�P�t���[���O�̓��͏�Ԃ�����������
	memset(state.Keyboard.prevState, 0,
		SDL_NUM_SCANCODES);

	memset(state.Controller.axisValues, 0,
		sizeof(float) * SDL_CONTROLLER_AXIS_MAX);


	//���݂ƂP�t���[���O�̃}�E�X�̓��͏�Ԃ�����������
	state.Mouse.currButtons = 0;
	state.Mouse.prevButtons = 0;

	// �p�b�h�̐ݒ�t�@�C�� gamecontrollerdb.txt �̓ǂݍ��݂Ɩ�肪�������̃`�F�b�N
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	//�R���g���[���[���J��
	controller = nullptr;
	controller = SDL_GameControllerOpen(0);
	if (controller != nullptr)
	{
		controllerConnected = true;
	}
	if (SDL_IsGameController(0))
	{
		printf("Controller :: %s \n", SDL_GameControllerMapping(controller));
	}

	// �R���g���[���C�x���g�̖����i�����炩��t���[�����ɏ�Ԃ��擾���邽�߁j
	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

/*
@brief  �I������
*/
void InputSystem::Shutdown()
{
	if (!controller)
	{
		SDL_GameControllerClose(controller);
	}
	controller = nullptr;
}

/*
@brief  Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
*/
void InputSystem::PrepareForUpdate()
{
	//���݂̓��͏�Ԃ��P�t���[���O�̓��͏�ԂɃR�s�[����
	//�L�[�{�[�h
	memcpy(state.Keyboard.prevState,
		state.Keyboard.currState,
		SDL_NUM_SCANCODES);

	//�}�E�X
	state.Mouse.prevButtons = state.Mouse.currButtons;
	state.Mouse.isRelative = false;
	state.Mouse.scrollWheel = Vector2::Zero;

	//�R���g���[���[
	memcpy(state.Controller.prevButtons,
		state.Controller.currButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/*
@brief  �t���[�����̏����iSDL_PollEvents�̒���ɌĂԁj
*/
void InputSystem::Update()
{
	//�}�E�X
	int x = 0, y = 0;
	if (state.Mouse.isRelative)
	{
		state.Mouse.currButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		state.Mouse.currButtons =
			SDL_GetMouseState(&x, &y);
	}

	state.Mouse.mousePos.x = static_cast<float>(x) - 1024.0f / 2;
	state.Mouse.mousePos.y = 768.0f / 2 - static_cast<float>(y);



	// �R���g���[���������ꍇ�� early exit����
	if (controller != NULL)
	{
		// �O�̃t���[���̃R���g���[���̏�Ԃ��R�s�[����
		memcpy(&state.Controller.prevButtons, &state.Controller.currButtons, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);

		// �R���g���[���̏�Ԃ��X�V����
		SDL_GameControllerUpdate();

		// ���݂̃R���g���[���̃{�^����Ԃ�ۑ�
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		{
			state.Controller.currButtons[i] = SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)i);
		}

		// ���݂̃R���g���[���̎�����ۑ�
		for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
		{
			state.Controller.axisValues[i] = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)i);
		}

		// LPAD���͂��x�N�g��������
		const float maxInput = 32767.0f;
		state.Controller.lAxisLeft.x = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTX];
		state.Controller.lAxisLeft.y= (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_LEFTY];
		// RPAD���͂��x�N�g��������
		state.Controller.lAxisRight.x = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_RIGHTX];
		state.Controller.lAxisRight.y = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_RIGHTY];

		//�X�e�B�b�N�̓��͂ɍŒ�l��݂���(�萔�ȉ��̓J�b�g)
		state.Controller.lAxisLeft.x= (fabs(state.Controller.lAxisLeft.x) < (float)7849) ? 0.0f : state.Controller.lAxisLeft.x / maxInput;
		state.Controller.lAxisLeft.y= (fabs(state.Controller.lAxisLeft.y) < (float)8689) ? 0.0f : state.Controller.lAxisLeft.y / maxInput;

		state.Controller.lAxisRight.x = (fabs(state.Controller.lAxisRight.x) < (float)7849) ? 0.0f : state.Controller.lAxisRight.x / maxInput;
		state.Controller.lAxisRight.y = (fabs(state.Controller.lAxisRight.y) < (float)8689) ? 0.0f : state.Controller.lAxisRight.y / maxInput;

		//�g���K�[�̒l��0~1�ɕϊ�
		state.Controller.leftTriggerAxis = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_TRIGGERLEFT];
		state.Controller.rightTriggerAxis = (float)state.Controller.axisValues[SDL_CONTROLLER_AXIS_TRIGGERRIGHT];

		state.Controller.leftTriggerAxis = (fabs(state.Controller.leftTriggerAxis) < (float)16384) ? 0.0f : state.Controller.leftTriggerAxis / maxInput;
		state.Controller.rightTriggerAxis = (fabs(state.Controller.rightTriggerAxis) < (float)16384) ? 0.0f : state.Controller.rightTriggerAxis / maxInput;


	}
}

/*
@brief  SDL�C�x���g��InputSystem�ɓn��
*/
void InputSystem::ProcessEvent(SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEWHEEL:
		state.Mouse.scrollWheel = Vector2(
			static_cast<float>(_event.wheel.x),
			static_cast<float>(_event.wheel.y));
		break;
	default:
		break;
	}
}

/*
@brief  �}�E�X�̃��[�h��ݒ肷��
@param	true : ���΃��[�h , false : �f�t�H���g���[�h
*/
void InputSystem::SetRelativeMouseMode(bool _value)
{
	SDL_bool set = _value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	state.Mouse.isRelative = _value;
}

/*
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�-1.0~1.0�ɂ܂Ƃ߂�j
@param	���͂��ꂽ�l�iint�j
@return	�t�B���^�����O���ꂽ�l
*/
float InputSystem::Filter1D(int _input)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const int deadZone = 250;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const int maxValue = 30000;

	float retVal = 0.0f;

	//���͒l�̐�Βl�����
	int absValue = _input > 0 ? _input : -_input;
	//���͒l���f�b�h�]�[����菬�����Ȃ�
	if (absValue > deadZone)
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		//���������̒l�Ɠ����ɂ���
		retVal = _input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0�̊ԂɎ��߂�
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/*
@brief  ���͂��ꂽ�l�iint�j���t�B���^�����O����i�͈͓��Ɏ��߂�0.0~1.0�ɂ܂Ƃ߂�j
@param	���͂��ꂽ�l��x�iint�j
@param	���͂��ꂽ�l��y�iint�j
@return	�t�B���^�����O���ꂽ�l
*/
Vector2 InputSystem::Filter2D(int _inputX, int _inputY)
{
	//�f�b�h�]�[���i���̒l��菬�����Ȃ�0.0�ɂ���j
	const float deadZone = 8000.0f;
	//�ő�l�i���̒l���傫���Ă�1.0�ɂ���j
	const float maxValue = 30000.0f;

	//2�����x�N�g���ɂ���
	Vector2 dir;
	dir.x = static_cast<float>(_inputX);
	dir.y = static_cast<float>(_inputY);

	float length = dir.Length();

	//���͒l�̃x�N�g���̒������f�b�h�]�[����菬�����Ȃ�
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//�f�b�h�]�[���ƍő�l�̊Ԃ�1.0�ȉ��ɂȂ�悤�v�Z����
		float f = (length - deadZone) / (maxValue - deadZone);
		//0.0��1.0�̊ԂɎ��߂�
		f = Math::Clamp(f, 0.0f, 1.0f);
		//�x�N�g���𐳋K�����āA�����̒l�ɃX�P�[�����O����
		dir *= f / length;
	}

	return dir;
}
