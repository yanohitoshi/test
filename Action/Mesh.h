#pragma once

#include <vector>
#include <string>
#include "Math.h"
#include "Collision.h"
#include "Renderer.h"

class Renderer;
class VertexArray;
class Texture;
/*
@file Mesh.h
@brief メッシュデータ
*/
class Mesh
{
public:
    Mesh();
    ~Mesh();
	/*
	@brief  メッシュデータの読み込み
	@param	_fileName ロードしたいメッシュのファイル名
	@param	_renderer Rendererクラスのポインタ
	@return true : 成功 , false : 失敗
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ロードしたメッシュデータの解放
	*/
    void Unload();
	//ゲッターセッター
	/*
	@return	VertexArray型のポインタ
	*/
	VertexArray* GetVertexArray() { return vertexArray; }

	/*
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(size_t _index);

	/*
	@return Textureクラスのポインタ
	*/
	const std::string& GetShaderName() const { return shaderName; }

	/*
	@return 半径
	*/
	float GetRadius() const { return radius; }

	/*
	@return 鏡面反射成分
	*/
	float GetSpecPower() const { return specPower; }

	/*
	@return luminance
	*/
	float GetLuminace() const { return luminance; }

	/*
	@return textureステージごとのtextureID
	*/
	int GetTextureID(TextureStage stage);

	/*
	@return MeshのAABB
	*/
	const AABB& GetBox() const { return mBox; }

	/*
	@return 頂点データ
	*/
	std::vector<Vector3> GetVerts() { return verts; }

private:

    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> textures;
	//このメッシュに使う頂点データ
	std::vector<Vector3> verts;
	//クラスのポインタ
    VertexArray* vertexArray;

    //このメッシュに使うシェーダーの名前
    std::string shaderName;
    //オブジェクト空間での境界球の半径
    float radius;
    //鏡面反射成分の大きさ
    float specPower;
	// 自己発行強度
	float luminance;
	// テクスチャステージに割り当てられたテクスチャ
	std::unordered_map<TextureStage, int> stageDefTexture;

	// AABB変数
	AABB mBox;

};