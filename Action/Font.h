#pragma once
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "RapidJsonHelper.h"

class Font
{
public:
	Font();
	~Font();

	// �t�@�C���̃��[�h
	bool Load(const std::string& fileName);
	void Unload();

	// ������Ƃ��̃t�H���g���w�肵�āA�e�N�X�`���ɕ`��
	class Texture* RenderText(const std::string& renderingText,
		const Vector3& color = Color::White,
		int pointSize = 30);

private:
	// �|�C���g�T�C�Y�̃t�H���g�f�[�^�ւ̃}�b�v
	std::unordered_map<int, TTF_Font*> mFontData;
};

