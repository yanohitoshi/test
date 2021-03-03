#pragma once

#include <string>
#include <vector>

class Texture
{
public:

    Texture();
    ~Texture();
	/*
	@brief	テクスチャのロード
	@param	_fileName テクスチャのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& _fileName);
	/*
	@brief	ロードしたテクスチャの解放
	*/
	void Unload();

	void CreateFromSurface(struct SDL_Surface* _surface);

	/*
	@brief	レンダリング用のテクスチャを作成
	@param	テクスチャの横幅
	@param	テクスチャの縦幅
	@param	ピクセルデータのフォーマット
	*/
	void CreateForRendering(int _width, int height, unsigned int _format);

	/*
	@brief	テクスチャをアクティブにする
	*/
	void SetActive();

	/*
	@brief	テクスチャの横幅を取得する
	@return 横幅
	*/
	int GetWidth() const { return width; }

	/*
	@brief	テクスチャの縦幅を取得する
	@return 縦幅
	*/
	int GetHeight() const { return height; }

	int GetTextureID() const { return textureID; }

	static bool LoadDiv(
		 const std::string& _fileName,const unsigned int _allNum
		,const unsigned int _widthNum, const unsigned int _heightNum
		,const unsigned int _width, const unsigned int _height
		,std::vector<Texture*> textures);

private:

	unsigned int textureID;

	//テクスチャの横幅
	int width;
	//テクスチャの縦幅
	int height;
};

