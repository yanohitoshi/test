#pragma warning(disable:4996)

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <document.h>
#include "Skeleton.h"
#include "Animation.h"
#include "SkeletalMeshComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "HDRRenderer.h"

Renderer* Renderer::renderer = nullptr;

void Renderer::SetParticleVertex()
{
	particleVertex->SetActive();
}

Renderer::Renderer()
	: hdrRenderer(nullptr)
	, spriteShader(nullptr)
	, spriteVerts(nullptr)
	, particleShader(nullptr)
	, particleVertex(nullptr)
	, depthMapShader(nullptr)
	, switchShader(nullptr)
	, shadowMapShader(nullptr)
	, mSkinnedDepthMapShader(nullptr)
	, mSkinnedShadowMapShader(nullptr)
	, view(Matrix4::Identity)
	, projection(Matrix4::Identity)
	, screenWidth(0)
	, screenHeight(0)
	, ambientLight(Vector3::Zero)
	, SHADOW_WIDTH (8192)
	, SHADOW_HEIGHT(8192)
{
}

Renderer::~Renderer()
{
}

/*
@brief  インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}

/*
@brief  インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成

	window = SDL_CreateWindow("OpenGL Game", 1, 1,
		static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);

	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL);
	}

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	context = SDL_GL_CreateContext(window);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}


	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	// SDL_ttfの初期化
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	undefineTexID = GetTexture("Assets/noneTexture.png")->GetTextureID();

	//　HDRrendererの生成
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);

	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	CreateTimeFontTexture(151,72);

	return true;
}

/*
@brief  終了処理
*/
void Renderer::Shutdown()
{
	//shaderとvertexの後片付け
	delete particleVertex;
	particleShader->Unload();
	delete particleShader;

	delete spriteVerts;

	spriteShader->Unload();
	delete spriteShader;

	switchShader->Unload();
	delete switchShader;

	depthMapShader->Unload();
	delete depthMapShader;

	shadowMapShader->Unload();
	delete shadowMapShader;

	mSkinnedDepthMapShader->Unload();
	delete mSkinnedDepthMapShader;

	mSkinnedShadowMapShader->Unload();
	delete mSkinnedShadowMapShader;

	//コンテキストとwindowの後片付け
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ロードしたデータの解放
*/
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : textures)
	{
		i.second->Unload();
		delete i.second;
	}
	textures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : meshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// Unload animations
	for (auto a : mAnims)
	{
		delete a.second;
	}

	meshes.clear();
	mSkeletons.clear();
	mAnims.clear();
}

/*
@brief  描画処理
*/
void Renderer::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// デプスマップレンダリング
	DepthRendering();

	//シャドウマップ描画
	DrawShadow();

	// particle描画
	DrawParticle();

	// UI系スプライトコンポーネントの描画
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	// デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);


	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	spriteShader->SetActive();
	spriteVerts->SetActive();
	// すべてのスプライトの描画
	for (auto sprite : sprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	// バッファを交換
	SDL_GL_SwapWindow(window);
}


/*
@brief  スプライトの追加
@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)

	bool isBackGround = _spriteComponent->GetIsBackGround();
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	if (isBackGround == false)
	{
		auto iter = sprites.begin();
		for (;
			iter != sprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// 検索した場所のiterの場所に挿入
		sprites.insert(iter, _spriteComponent);
	}

	if (isBackGround == true)
	{
		auto iter = backGroundSprites.begin();
		for (;
			iter != backGroundSprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// 検索した場所のiterの場所に挿入
		backGroundSprites.insert(iter, _spriteComponent);
	}
}

/*
@brief スプライトの削除
@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	bool isBackGround = _spriteComponent->GetIsBackGround();
	if (isBackGround == false)
	{
		auto iter = std::find(sprites.begin(), sprites.end(), _spriteComponent);
		sprites.erase(iter);
	}

	if (isBackGround == true)
	{
		auto iter = std::find(backGroundSprites.begin(), backGroundSprites.end(), _spriteComponent);
		backGroundSprites.erase(iter);
	}

}


/*
@brief  パーティクルの追加
@param	_particleComponent　追加するParticleObjectクラスのポインタ
*/
void Renderer::AddParticle(ParticleComponent * _particleComponent)
{
	int myDrawOrder = _particleComponent->GetDrawOrder();
	auto iter = particles.begin();
	for (;
		iter != particles.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	particles.insert(iter, _particleComponent);
}

/*
@brief  スプライトの削除
@param	削除するParticleObjectクラスのポインタ
*/
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(particles.begin(), particles.end(), _particleComponent);
	particles.erase(iter);
}

/*
@brief  メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	//メッシュデータにスケルトンデータがあれば
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else if(_meshComponent->GetIsColorChange() == true)
	{
		colorChangeMeshComponents.emplace_back(_meshComponent);
	}
	else
	{
		meshComponents.emplace_back(_meshComponent);
	}
}


/*
@brief  メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else if (_meshComponent->GetIsColorChange())
	{
		auto iter = std::find(colorChangeMeshComponents.begin(), colorChangeMeshComponents.end(), _meshComponent);
		colorChangeMeshComponents.erase(iter);
	}
	else
	{
		auto iter = std::find(meshComponents.begin(), meshComponents.end(), _meshComponent);
		meshComponents.erase(iter);
	}
}


/*
@param _fileName モデルへのアドレス
@return スケルトンモデルの取得
*/
const Skeleton * Renderer::GetSkeleton(const char * fileName)
{
	std::string file(fileName);
	auto iter = mSkeletons.find(file);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/*
@param _fileName アニメーションへのアドレス
@return スケルトンアニメーションの取得
*/
const Animation * Renderer::GetAnimation(const char * fileName, bool _loop)
{
	auto iter = mAnims.find(fileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(fileName,_loop))
		{
			mAnims.emplace(fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@brief  テクスチャの取得
@param	_fileName　取得したいテクスチャのファイル名
@return Textureクラスのポインタ
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = textures.find(_fileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			textures.emplace(_fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

Font* Renderer::GetFont(const std::string& _fileName)
{
	Font* font = nullptr;
	//すでに作成されてないか調べる
	auto itr = fonts.find(_fileName);
	if (itr != fonts.end())
	{
		font = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		font = new Font();
		if (font->Load(_fileName))
		{
			fonts.emplace(_fileName, font);
		}
		else
		{
			delete font;
			font = nullptr;
		}
	}

	return font;
}

/*
@brief  メッシュの取得
@param	_fileName 取得したいメッシュのファイル名
@return Meshクラスのポインタ
*/
Mesh* Renderer::GetMesh(const std::string &_fileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = meshes.find(_fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			meshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@brief  シェーダーの読み込み
@return true : 成功 , false : 失敗
*/
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	spriteShader->SetActive();
	// sprite用ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);


	// 3Dモデル用ビュー行列の設定
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		screenWidth, screenHeight, 25.0f, 7000.0f);

	// switch用シェーダーの作成(色変更可能シェーダー)
	switchShader = new Shader();
	if (!switchShader->Load("Shaders/shadowmap.vert", "Shaders/switch.frag"))
	{
		return false;
	}
	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view * projection);


	//particleシェーダー
	particleShader = new Shader();
	if (!particleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	// シャドウ用フレームバッファオブジェクトを作成・デプスマップを生成し、シャドウバッファにアタッチ
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// depthMapFBOにデプステクスチャをアタッチする
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// デプスマップ焼き用シェーダ(アニメーションなし)
	depthMapShader = new Shader();
	if (!depthMapShader->Load("Shaders/depthmap.vert", "Shaders/depthmap.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}
	// シャドウを適用した描画用シェーダ作成(アニメーションなし)
	shadowMapShader = new Shader();
	if (!shadowMapShader->Load("Shaders/shadowmap.vert", "Shaders/shadowmap.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	// デプスマップ焼き用シェーダ (アニメーションあり)
	mSkinnedDepthMapShader = new Shader();
	if (!mSkinnedDepthMapShader->Load("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag"))
	{
		printf("シェーダー読み込み失敗depth\n");
	}
	// シャドウを適用した描画用シェーダ作成 (アニメーションあり)
	mSkinnedShadowMapShader = new Shader();
	if (!mSkinnedShadowMapShader->Load("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag"))
	{
		printf("シェーダー読み込み失敗shadow\n");
	}

	return true;
}

/*
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

// パーティクル頂点作成
void Renderer::CreateParticleVerts()
{
	float vertices[] = {
		-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 2, 1,
		2, 0, 3
	};
	particleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::CreateTimeFontTexture(int _value, int _fontSize)
{
	Font* font = GetFont("Assets/Config/Fonts/impact.ttf");
	timeFontTextures.resize(_value);
	timeBlackFontTextures.resize(_value);
	timeRedFontTextures.resize(_value);

	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeFontTextures[i] = font->RenderText(str,Color::White, _fontSize);
	}
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeBlackFontTextures[i] = font->RenderText(str, Color::Black, _fontSize);
	}
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeRedFontTextures[i] = font->RenderText(str, Color::Red, _fontSize);
	}


}

Texture* Renderer::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

Texture* Renderer::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

Texture* Renderer::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

void Renderer::DrawShadow()
{


	/* HDRとシャドウマップの処理開始 */
	hdrRenderer->HdrRecordBegin();

	// 背景描画
	DrawBackGround();

	//シャドウマップshaderをアクティブ
	shadowMapShader->SetActive();
	// ライトのカメラ情報
	shadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	shadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
	shadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	shadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	shadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	shadowMapShader->SetMatrixUniform("view", view);
	shadowMapShader->SetMatrixUniform("projection", projection);

	// デプスマップをセット（メッシュ用）
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	shadowMapShader->SetIntUniform("depthMap", 4);

	shadowMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// シェーダーに渡すライティング情報を更新する
	// すべてのメッシュの描画
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(shadowMapShader);
		}
	}

	//シャドウマップshaderをアクティブ(skinnend)
	mSkinnedShadowMapShader->SetActive();
	// ライトのカメラ情報
	mSkinnedShadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	mSkinnedShadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	mSkinnedShadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	mSkinnedShadowMapShader->SetMatrixUniform("uViewProj", view * projection);
	// デプスマップをセット（スキニング用）
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	mSkinnedShadowMapShader->SetIntUniform("depthMap", 4);
	mSkinnedShadowMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShadowMapShader);
		}
	}
	/*  シャドウマップ描画終了 */

	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view* projection);
	// ライトのカメラ情報
	switchShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	switchShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
	switchShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	switchShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	switchShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	switchShader->SetMatrixUniform("view", view);
	switchShader->SetMatrixUniform("projection", projection);

	for (auto mc : colorChangeMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(switchShader);
		}
	}


	hdrRenderer->HdrRecordEnd();

	/* HDR Bloom の作成と合成 */
	// ガウスぼかしの生成
	hdrRenderer->HiBrightBlurCreate();
	// ガウスぼかしした画像とHDRを最終合成
	hdrRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBufferにレンダリングしたときのDepth情報をスクリーンにコピー
	hdrRenderer->CopyDepthToScreen();

}

void Renderer::DepthRendering()
{
	/* ここからデプスマップ開始 */


	//ライト情報
	LightPos = Vector3(playerPos.x, playerPos.y, playerPos.z + 1000.0f);
	LightDir = dirLight.direction;
	LightDir.Normalize();
	lightProjection = Matrix4::CreateOrtho(3000.0f, 3000.0f, 1.0f, 5000.0f);
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	lightSpeceMatrix = lightView * lightProjection;

	// ビューポートを深度マップサイズに設定する
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	// シャドウフレームバッファをバインド
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);

	// デプスマップ焼き用シェーダを有効化し、必要な値をシェーダにセット・シャドウをつけたいオブジェクトを描画する
	depthMapShader->SetActive();
	depthMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(depthMapShader);
		}
	}

	mSkinnedDepthMapShader->SetActive();
	mSkinnedDepthMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedDepthMapShader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* ここでデプスマップ終了 */

}

void Renderer::DrawBackGround()
{
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトコンポーネントの描画(背景)
	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	spriteShader->SetActive();
	spriteVerts->SetActive();
	glActiveTexture(GL_TEXTURE0);
	spriteShader->SetIntUniform("uTexture", 0);
	// すべてのスプライトの描画
	for (auto sprite : backGroundSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}

void Renderer::DrawParticle()
{
	
	std::sort(particles.begin(), particles.end(), std::greater<ParticleComponent*>());

	if (particles.size() == 0)
	{
		return;
	}
	// ブレンドモード初期状態取得
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	// シェーダーON
	particleShader->SetActive();
	particleShader->SetMatrixUniform("uViewProj", viewProjectionMat);
	// 全てのパーティクルのビルボード行列をセット
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	glActiveTexture(GL_TEXTURE0);
	particleShader->SetIntUniform("uTexture", 0);
	ChangeBlendMode(blendType);
	
	ChangeTexture(nowTexture);

	for (auto particle : particles)
	{
		if (particle->GetVisible())
		{
			//ブレンドモード変更が必要なら変更する
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();
			if (blendType != prevType)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}
			// テクスチャ変更が必要なら変更する
			nowTexture = particle->GetTextureID();
			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// パーティクル描画
			particle->Draw(particleShader);

			// 前回描画状態として保存
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4 & view, const Matrix4 & proj, float viewPortScale, bool lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(screenWidth * viewPortScale),
		static_cast<int>(screenHeight * viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// Set the mesh shader active
	//meshShader->SetActive();
	//// Update view-projection matrix
	//meshShader->SetMatrixUniform("uViewProj", view * proj);
	//// Update lighting uniforms
	//if (lit)
	//{
	//	SetLightUniforms(meshShader, view);
	//}
	//for (auto mc : meshComponents)
	//{
	//	if (mc->GetVisible())
	//	{
	//		mc->Draw(meshShader);
	//	}
	//}

}

/*
@brief  光源情報をシェーダーの変数にセットする
@param _shader セットするShaderクラスのポインタ
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", ambientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		dirLight.direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		dirLight.diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		dirLight.specColor);
}

void Renderer::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

void Renderer::ChangeTexture(int changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = view;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}


// 画面全体を覆う頂点定義
void Renderer::screenVAOSetting(unsigned int& vao)
{
	unsigned int vbo;
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}