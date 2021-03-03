#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

/*
 @file MeshComponent.h
 @brief メッシュデータの管理と描画を行う
*/
class MeshComponent : public Component
{
public:
	/*
	@param _skelton スケルトンデータを用いるか。
	@sa SkeletalMeshComponent.h
	*/
    MeshComponent(GameObject* _owner,bool _skelton,bool _color);
    ~MeshComponent();

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);

protected:
	//メッシュデータクラスへのポインタ
    Mesh* mesh;
	//テクスチャサイズ
    size_t textureIndex;
	//描画をするかどうか
	bool visible;
	//スケルトンデータを用いるか
	bool isSkelton;
	//カラーチェンジを用いるか
	bool isColorChange;

	virtual void SetTextureToShader(Shader* shader);

public: //ゲッターセッター
	/*
	@brief　メッシュコンポーネントが使うMeshの設定
	@param	_mesh 設定するMeshクラスのポインタ
	*/
	virtual void SetMesh(Mesh* _mesh) { mesh = _mesh; }

	/*
	 　@return 設定されたMeshクラスのポインタ
	*/
	virtual Mesh* GetMesh() { return mesh; }

	/*
	@brief　メッシュコンポーネントが使うTextureインデックスの設定
	*/
	void SetTextureIndex(size_t _index) { textureIndex = _index; }

	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

	/*
	@return スケルトンデータを用いるか
	*/
	bool GetIsSkeltal()const { return isSkelton; }


	/*
	@return カラーチェンジを用いるか
	*/
	bool GetIsColorChange()const { return isColorChange; }
	
};

