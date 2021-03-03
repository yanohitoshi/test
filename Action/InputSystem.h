#pragma once

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

/*
enum ButtonState
ボタンの状態を表す
*/
enum ButtonState
{
	//押されていない
	None,		
	//押した
	Pressed,	
	//離した
	Released,	
	//押されている
	Held		
};

/*
@file KeyboardState.hキーボードの入力管理クラス
*/
class KeyboardState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;
private:
	//現在のキーボードの入力状態
	const Uint8* currState;
	//１フレーム前のキーボードの入力状態
	Uint8 prevState[SDL_NUM_SCANCODES];
public://ゲッターセッター
	/*
	@brief	現在のキーの入力状態のみを取得する
	@param	SDL_Scancodeのキーコード
	@return	true : 押されている , false : 押されていない
	*/
	bool GetKeyValue(SDL_Scancode _keyCode) const;
	bool GetKeyDownValue(SDL_Scancode _keyCode) const;

	/*
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_Scancodeのキーコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetKeyState(SDL_Scancode _keyCode) const;
};

/*
@file MouseState.h
@brief マウスの入力管理クラス
*/
class MouseState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;
private:
	//マウスのポジション
	Vector2 mousePos;
	//スクロールホイールのスクロール量
	Vector2 scrollWheel;
	// 現在のマウスの入力状態
	Uint32 currButtons;
	//１フレーム前のマウスの入力状態
	Uint32 prevButtons;
	// 相対マウスモードかどうか
	bool isRelative;
public://ゲッターセッター

	/*
	@brief	相対マウスモードかどうかを取得する
	@return	true : 相対モード , false , 通常モード
	*/
	bool IsRelative() const { return isRelative; }

	/*
	@brief	現在のマウスのポジションを取得する
	@return	Position
	*/
	const Vector2& GetPosition() const { return mousePos; }

	/*
	@brief	現在のマウスのスクロールホイールの状態を取得する
	@return	スクロール量（Vector2）
	*/
	const Vector2& GetScrollWheel() const { return scrollWheel; }

	/*
	@brief	現在の入力状態のみを取得する
	@param	SDL_BUTTON定数
	@return	true : 押されている , false : 押されていない
	*/
	bool GetButtonValue(int _button) const;

	/*
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_BUTTON定数
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(int _button) const;
};

/*
@file ControllerState.h
@brief コントローラーの入力管理クラス
*/
class ControllerState
{
public:
	// InputSystemから容易に更新できるようにする
	friend class InputSystem;
private:
	//現在のボタンの入力状態
	Uint8 currButtons[SDL_CONTROLLER_BUTTON_MAX];
	//１フレーム前のボタンの入力状態
	Uint8 prevButtons[SDL_CONTROLLER_BUTTON_MAX];

	//両スティックの情報
	float axisValues[SDL_CONTROLLER_AXIS_MAX];
	Vector2 lAxisLeft;
	Vector2 lAxisRight;
	float leftTriggerAxis;
	float rightTriggerAxis;
public://ゲッターセッター
	/*
	@brief	現在の入力状態のみを取得する
	@param	SDL_GameControllerButtonのボタンコード
	@return	true : 押されている , false : 押されていない
	*/
	bool GetButtonValue(SDL_GameControllerButton _button) const;

	/*
	@brief	現在と1フレーム前の状態からButtonStateを返す
	@param	SDL_GameControllerButtonのボタンコード
	@return	ButtonState型の現在の状態
	*/
	ButtonState GetButtonState(SDL_GameControllerButton _button) const;

	/*
	@brief スティックの入力を0~32767で返す
	@param iAxis どのスティックのどの値を取得するか
		   (左スティックのXを取得...SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
	@return スティックの入力情報
	*/
	float GetAxisValue(const SDL_GameControllerAxis iAxis) const;
	/*
	@brief スティックの入力を0~1で返す
	@return スティックの入力情報
	*/
	const Vector2& GetLAxisLeftVec() const { return lAxisLeft; }
	const Vector2& GetLAxisRightVec() const { return lAxisRight; }

	const float& GetLeftTrigger() const { return leftTriggerAxis; }
	const float& GetRightTrigger() const { return rightTriggerAxis; }

};

/*
@struct InputState 
各入力機器の入力状態をまとめたラッパー構造体
*/
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};
/*
@file InputSystem.h
@brief 入力情報を管理
*/
class InputSystem
{
public:
	/*
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize();

	/*
	@brief  終了処理
	*/
	void Shutdown();

	/*
	@brief  Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
	*/
	void PrepareForUpdate();

	/*
	@brief  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
	*/
	void Update();

	/*
	@brief  SDLイベントをInputSystemに渡す
	*/
	void ProcessEvent(union SDL_Event& _event);

private:

	/*
	@brief  入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
	@param	入力された値のx（int）
	@param	入力された値のy（int）
	@return	フィルタリングされた値
	*/
	Vector2 Filter2D(int _inputX, int _inputY);

	/*
	@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
	@param	入力された値（int）
	@return	フィルタリングされた値
	*/
	float Filter1D(int _input);


	//各入力機器の入力状態をまとめたラッパー構造体
	InputState state;
	//SDLでコントローラーを認識するためのクラスポインタ
	SDL_GameController* controller;
	//コントローラーが接続されたか
	static bool controllerConnected;

public://ゲッターセッター
	/*
	@brief  現在の入力状態を取得する
	@return （InputState）各入力情報をまとめた構造体
	*/
	const InputState& GetState() const { return state; }

	/*
	@brief  マウスのモードを設定する
	@param	true : 相対モード , false : デフォルトモード
	*/
	void SetRelativeMouseMode(bool _value);

	static bool GetConnectedController() { return controllerConnected; }
};
