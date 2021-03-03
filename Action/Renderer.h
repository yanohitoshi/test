#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "GameObject.h"

#define RENDERER Renderer::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 direction;
	// �g�U���ːF
	Vector3 diffuseColor;
	// ���ʔ��ːF
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
@brief �`��̐i�s���s���N���X
*/
class Renderer
{
public:
	/*
	@brief  �C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X
	*/
	static Renderer* GetInstance() { return renderer; }

	/*
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);
	/*
	@brief  �I������
	*/
	void Shutdown();

	/*
	@brief  ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@brief  �`�揈��
	*/
	void Draw();
	   
	/*
	@brief  �X�v���C�g�̒ǉ�
	@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief �X�v���C�g�̍폜
	@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  �p�[�e�B�N���̒ǉ�
	@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  �X�v���C�g�̍폜
	@param	�폜����ParticleObject�N���X�̃|�C���^
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@brief  ���b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);



	/*
	@brief  ���b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  �e�N�X�`���̎擾
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(const std::string& _fileName);
	   
	/*
	@brief  �t�H���g�̎擾
	@param	_fileName�@�擾�������t�H���g�̃t�@�C����
	@return Font�N���X�̃|�C���^
	*/
	Font* GetFont(const std::string& _fileName);

	/*
	@param _fileName ���f���ւ̃A�h���X
	@return �X�P���g�����f���̎擾
	*/
	const class Skeleton* GetSkeleton(const char* fileName);                       
	/*
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����̎擾
	*/
	const class Animation* GetAnimation(const char* fileName, bool _loop);                     // �X�P���^���A�j���[�V�����̎擾

	/*
	@brief  ���b�V���̎擾
	@param	_fileName �擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	�r���[�s���ݒ肷��
	@param	_view �r���[�s��
	*/
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	������ݒ肷��
	@param	_ambient Vector3�i������\���j
	*/
	void SetAmbientLight(Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	���s�����̍\���̂��擾����
	@return	DirectionalLight�i���s�����̍\���́j
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	�X�N���[���̉������擾����
	@return	�X�N���[���̉���
	*/
	float GetScreenWidth() const { return screenWidth; }

	/*
	@brief	�X�N���[���̏c�����擾����
	@return	�X�N���[���̏c��
	*/
	float GetScreenHeight() const { return screenHeight; }

	/*
	@brief	View�s���getter
	@return View�s��
	*/
	Matrix4 GetViewMatrix() const { return view; };
	
	/*
	@brief	Particle�p���_�f�[�^�̃Z�b�g�֐�
	*/
	void SetParticleVertex();
	
	/*
	@brief	Projection�s���getter
	@return Projection�s��
	*/
	Matrix4 GetProjectionMatrix() { return projection; }

	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }
	/*
	@brief	�v���C���[�̃|�W�V�������Z�b�g����setter
	@param	�v���C���[�̃|�W�V����
	*/
	void SetPlayerPositon(Vector3 _pos) { playerPos = _pos; }
	/*
	@brief	�J�����̑O���x�N�g�����Z�b�g����setter
	@param	�J�����̑O���x�N�g��
	*/
	void SetCameraForawrd(Vector3 _vec) { cameraForwardVec = _vec; }
	unsigned int GetUndefineTexID() { return undefineTexID; }

	/*
	@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
	@param	�J�E���g�_�E���^�C��
	@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
	*/
	Texture* GetTimeTexture(int _time);

	/*
	@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
	@param	�J�E���g�_�E���^�C��
	@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
	*/
	Texture* GetTimeBlackTexture(int _time);
	
	/*
	@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i�ԁj
	@param	�J�E���g�_�E���^�C��
	@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
	*/
	Texture* GetTimeRedTexture(int _time);


private:
	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer();

	friend class Shadow;

	// �X�P���g���f�[�^
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// �A�j���[�V�����f�[�^
	std::unordered_map<std::string, class Animation*> mAnims;    

	//�����̃C���X�^���X
	static Renderer* renderer;
	SDL_Renderer* sdlRenderer;

	// HDR �����_���[
	HDRRenderer* hdrRenderer;

	/*
	@brief  �V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s
	*/
	bool LoadShaders();
	/*
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
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
	@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);
	void screenVAOSetting(unsigned int& vao);
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);
	Vector3 CalcCameraPos();

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> meshes;

	//���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> meshComponents;
	//�J���[�`�F���W�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> colorChangeMeshComponents;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;
	//�w�i�摜�p�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> backGroundSprites;

	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> particles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*>textures;
	// �X�P���g�����b�V���̕`��Ɏg����
	std::vector<class SkeletalMeshComponent*>mSkeletalMeshes;   
	// �F��ς��郁�b�V���̕`��Ɏg����
	std::vector<class ChangeColorMeshComponent*>mChangeColorMeshes;

	// Map for fonts
	std::unordered_map<std::string, class Font*> fonts;



	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* spriteShader;
	VertexArray* spriteVerts;
	//���b�V��
	//Shader* basicShader;
	//Shader* meshShader;
	Shader* switchShader;
	//effect�p���b�V��
	Shader* effectMeshShader;
	//�X�L�����b�V��
	Shader*  mSkinnedShader;  
	//shadow�}�b�v�֘A�V�F�[�_�[
	//shadow�p�i���b�V���j
	Shader* depthMapShader;
	Shader* shadowMapShader;
	//shadow�p�i�X�L�����b�V���j
	Shader* mSkinnedDepthMapShader;
	Shader* mSkinnedShadowMapShader;
	//�f�o�b�N�p�V�F�[�_�[
	Shader* debugShader;

	//�p�[�e�B�N��
	Shader* particleShader;
	// �p�[�e�B�N���p���_��`
	VertexArray* particleVertex;   

	//�r���[�s��
	Matrix4 view;
	//�ˉe�s��
	Matrix4 projection;
	//�r���{�[�h�s��
	Matrix4 mBillboardMat;
	//�X�N���[���̉���
	float screenWidth;
	//�X�N���[���̏c��
	float screenHeight;
	//����
	Vector3 ambientLight;
	//���s����
	DirectionalLight dirLight;
	//�E�B���h�E
	SDL_Window* window;
	//�R���e�L�X�g
	SDL_GLContext context;


	Vector3 lightDir;
	Vector3 playerPos;
	//�f�v�X�}�b�v
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
	// HDR�֘A	
	// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int undefineTexID;


	//���ԕ\���p�̃t�H���gtexture
	std::vector<Texture*> timeFontTextures;
	std::vector<Texture*> timeBlackFontTextures;
	std::vector<Texture*> timeRedFontTextures;


};