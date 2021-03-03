#include "Texture.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"

Texture::Texture()
	:textureID(0)
	, width(0)
	, height(0)
{
}

Texture::~Texture()
{
}

/*
@brief	テクスチャのロード
@param	_fileName テクスチャのファイル名
@return	true : 成功 , false : 失敗
*/
bool Texture::Load(const std::string& _fileName)
{
	int channels = 0;

	// SDLサーフェスをテクスチャから作成
	SDL_Texture* tex = nullptr;
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("テクスチャ読み込みに失敗 %s", _fileName.c_str());
		return false;
	}

	//サーフェスからテクスチャを作る
	tex = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), surf);
	if (!tex)
	{
		printf("サーフェスからテクスチャの作成に失敗 : %s", _fileName.c_str());
		return false;
	}

	// 画像の幅、高さを取得
	width = surf->w;
	height = surf->h;
	channels = surf->format->BytesPerPixel;

	// OpenGLにテクスチャ登録
	int format = GL_RGB;
	int depth, pitch;
	depth = 24;
	pitch = 3 * width; // 1ピクセルあたり3byte * 1行のピクセル数
	if (channels == 4)
	{
		format = GL_RGBA;
		depth = 32;
		pitch = 4 * width;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 異方性フィルタリングが使えるかどうか
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		// 最大の異方性を示す値を取得する
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		// 異方性フィルタリングを有効にする
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

/*
@brief	ロードしたテクスチャの解放
*/
void Texture::Unload()
{
	glDeleteTextures(1, &textureID);
}

void Texture::CreateFromSurface(SDL_Surface * _surface)
{
	width = _surface->w;
	height = _surface->h;

	// Generate a GL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, _surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/*
@brief	レンダリング用のテクスチャを作成
@param	テクスチャの横幅
@param	テクスチャの縦幅
@param	ピクセルデータのフォーマット
*/
void Texture::CreateForRendering(int _width, int _height, unsigned int _format)
{
	width = _width;
	height = _height;
	// テクスチャIDの作成
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// 画像の幅と高さを設定（初期データは指定しない）
	glTexImage2D(GL_TEXTURE_2D, 0, _format, width, height, 0, GL_RGB,
		GL_FLOAT, nullptr);

	// レンダリング先のテクスチャには最近傍フィルタリングのみを使う
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/*
@brief	テクスチャをアクティブにする
*/
void Texture::SetActive()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

}

bool Texture::LoadDiv(const std::string& _fileName, const unsigned int _allNum
	, const unsigned int _widthNum, const unsigned int _heightNum
	, const unsigned int _width, const unsigned int _height
	, std::vector<Texture*> textures)
{
	textures.clear();

	return false;
}
