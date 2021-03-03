#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "GameObject.h"

#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 direction;
	// 拡散反射色
	Vector3 diffuseColor;
	// 鏡面反射色
	Vector3 specColor;
};


enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class ChangeColorMeshComponent;
class TileMapSpriteComponent;
class Font;
class HDRRenderer;
/*
@file Renderer.h
@brief 描画の進行を行うクラス
*/
class Renderer
{
public:
	/*
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static Renderer* GetInstance() { return renderer; }

	/*
	@brief  インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@brief  インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);
	/*
	@brief  終了処理
	*/
	void Shutdown();

	/*
	@brief  ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@brief  描画処理
	*/
	void Draw();
	   
	/*
	@brief  スプライトの追加
	@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief スプライトの削除
	@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  パーティクルの追加
	@param	_particleComponent　追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  スプライトの削除
	@param	削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@brief  メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);



	/*
	@brief  メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  テクスチャの取得
	@param	_fileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& _fileName);
	   
	/*
	@brief  フォントの取得
	@param	_fileName　取得したいフォントのファイル名
	@return Fontクラスのポインタ
	*/
	Font* GetFont(const std::string& _fileName);

	/*
	@param _fileName モデルへのアドレス
	@return スケルトンモデルの取得
	*/
	const class Skeleton* GetSkeleton(const char* fileName);                       
	/*
	@param _fileName アニメーションへのアドレス
	@return スケルトンアニメーションの取得
	*/
	const class Animation* GetAnimation(const char* fileName, bool _loop);                     // スケルタルアニメーションの取得

	/*
	@brief  メッシュの取得
	@param	_fileName 取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	ビュー行列を設定する
	@param	_view ビュー行列
	*/
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	環境光を設定する
	@param	_ambient Vector3（環境光を表す）
	*/
	void SetAmbientLight(Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
	float GetScreenWidth() const { return screenWidth; }

	/*
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	float GetScreenHeight() const { return screenHeight; }

	/*
	@brief	View行列のgetter
	@return View行列
	*/
	Matrix4 GetViewMatrix() const { return view; };
	
	/*
	@brief	Particle用頂点データのセット関数
	*/
	void SetParticleVertex();
	
	/*
	@brief	Projection行列のgetter
	@return Projection行列
	*/
	Matrix4 GetProjectionMatrix() { return projection; }

	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }
	/*
	@brief	プレイヤーのポジションをセットするsetter
	@param	プレイヤーのポジション
	*/
	void SetPlayerPositon(Vector3 _pos) { playerPos = _pos; }
	/*
	@brief	カメラの前方ベクトルをセットするsetter
	@param	カメラの前方ベクトル
	*/
	void SetCameraForawrd(Vector3 _vec) { cameraForwardVec = _vec; }
	unsigned int GetUndefineTexID() { return undefineTexID; }

	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（白）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeTexture(int _time);

	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（黒）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeBlackTexture(int _time);
	
	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（赤）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeRedTexture(int _time);


private:
	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	friend class Shadow;

	// スケルトンデータ
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> mAnims;    

	//自分のインスタンス
	static Renderer* renderer;
	SDL_Renderer* sdlRenderer;

	// HDR レンダラー
	HDRRenderer* hdrRenderer;

	/*
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
	bool LoadShaders();
	/*
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();
	void CreateParticleVerts();

	void CreateTimeFontTexture(int _value,int _fontSize);

	void DrawShadow();
	void DepthRendering();
	void DrawBackGround();
	void DrawParticle();

	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);

	/*
	@brief  光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);
	void screenVAOSetting(unsigned int& vao);
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);
	Vector3 CalcCameraPos();

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> meshes;

	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> meshComponents;
	//カラーチェンジコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> colorChangeMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//背景画像用スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> backGroundSprites;

	//パーティクルのポインタ
	std::vector<ParticleComponent*> particles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>textures;
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>mSkeletalMeshes;   
	// 色を変えるメッシュの描画に使われる
	std::vector<class ChangeColorMeshComponent*>mChangeColorMeshes;

	// Map for fonts
	std::unordered_map<std::string, class Font*> fonts;



	//クラスのポインタ
	//スプライト
	Shader* spriteShader;
	VertexArray* spriteVerts;
	//メッシュ
	//Shader* basicShader;
	//Shader* meshShader;
	Shader* switchShader;
	//effect用メッシュ
	Shader* effectMeshShader;
	//スキンメッシュ
	Shader*  mSkinnedShader;  
	//shadowマップ関連シェーダー
	//shadow用（メッシュ）
	Shader* depthMapShader;
	Shader* shadowMapShader;
	//shadow用（スキンメッシュ）
	Shader* mSkinnedDepthMapShader;
	Shader* mSkinnedShadowMapShader;
	//デバック用シェーダー
	Shader* debugShader;

	//パーティクル
	Shader* particleShader;
	// パーティクル用頂点定義
	VertexArray* particleVertex;   

	//ビュー行列
	Matrix4 view;
	//射影行列
	Matrix4 projection;
	//ビルボード行列
	Matrix4 mBillboardMat;
	//スクリーンの横幅
	float screenWidth;
	//スクリーンの縦幅
	float screenHeight;
	//環境光
	Vector3 ambientLight;
	//平行光源
	DirectionalLight dirLight;
	//ウィンドウ
	SDL_Window* window;
	//コンテキスト
	SDL_GLContext context;


	Vector3 lightDir;
	Vector3 playerPos;
	//デプスマップ
	unsigned int depthMapFBO;
	const unsigned int SHADOW_WIDTH;
	const unsigned int SHADOW_HEIGHT;
	unsigned int depthMap;
	Vector3 LightPos;
	Vector3 LightDir;
	Matrix4 lightProjection, lightView, lightSpeceMatrix;
	Vector3 cameraForwardVec;
	Vector3 lightViewPos;
	Matrix4 lightViewMat;
	Matrix4 lightProjMat;
	// HDR関連	
	// 未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int undefineTexID;


	//時間表示用のフォントtexture
	std::vector<Texture*> timeFontTextures;
	std::vector<Texture*> timeBlackFontTextures;
	std::vector<Texture*> timeRedFontTextures;


};