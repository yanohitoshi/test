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
@brief ���b�V���f�[�^
*/
class Mesh
{
public:
    Mesh();
    ~Mesh();
	/*
	@brief  ���b�V���f�[�^�̓ǂݍ���
	@param	_fileName ���[�h���������b�V���̃t�@�C����
	@param	_renderer Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ���[�h�������b�V���f�[�^�̉��
	*/
    void Unload();
	//�Q�b�^�[�Z�b�^�[
	/*
	@return	VertexArray�^�̃|�C���^
	*/
	VertexArray* GetVertexArray() { return vertexArray; }

	/*
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(size_t _index);

	/*
	@return Texture�N���X�̃|�C���^
	*/
	const std::string& GetShaderName() const { return shaderName; }

	/*
	@return ���a
	*/
	float GetRadius() const { return radius; }

	/*
	@return ���ʔ��ː���
	*/
	float GetSpecPower() const { return specPower; }

	/*
	@return luminance
	*/
	float GetLuminace() const { return luminance; }

	/*
	@return texture�X�e�[�W���Ƃ�textureID
	*/
	int GetTextureID(TextureStage stage);

	/*
	@return Mesh��AABB
	*/
	const AABB& GetBox() const { return mBox; }

	/*
	@return ���_�f�[�^
	*/
	std::vector<Vector3> GetVerts() { return verts; }

private:

    //���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
    std::vector<Texture*> textures;
	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> verts;
	//�N���X�̃|�C���^
    VertexArray* vertexArray;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string shaderName;
    //�I�u�W�F�N�g��Ԃł̋��E���̔��a
    float radius;
    //���ʔ��ː����̑傫��
    float specPower;
	// ���Ȕ��s���x
	float luminance;
	// �e�N�X�`���X�e�[�W�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	std::unordered_map<TextureStage, int> stageDefTexture;

	// AABB�ϐ�
	AABB mBox;

};