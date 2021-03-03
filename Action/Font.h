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

	// ファイルのロード
	bool Load(const std::string& fileName);
	void Unload();

	// 文字列とこのフォントを指定して、テクスチャに描画
	class Texture* RenderText(const std::string& renderingText,
		const Vector3& color = Color::White,
		int pointSize = 30);

private:
	// ポイントサイズのフォントデータへのマップ
	std::unordered_map<int, TTF_Font*> mFontData;
};

