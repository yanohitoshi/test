#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

/*
@file Shader.h
@brief �V�F�[�_�[�f�[�^
*/
class Shader
{
public:
    Shader();
    ~Shader();
	/*
	@brief	���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
	@param	_vertName ���_�V�F�[�_�[�̃t�@�C����
	@param	_fragName ���_�V�F�[�_�[�̃t�@�C����
	@return	true : ���� , false : ���s
	*/
	bool Load(const std::string& _vertName,const std::string& _fragName);
	/*
	@brief	���[�h�����V�F�[�_�[�̉��
	*/
	void Unload();

	/*
	@brief	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
	*/
	void SetActive();

	/*
	@brief	�s���Uniform�ϐ���ݒ肷��
	@param	_name �ݒ肷��Uniform�ϐ���
	@param	_matrix �ݒ肷��s��
	*/
	void SetMatrixUniform(const char* _name , const Matrix4& _matrix);
	void SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count);
    /*
    @brief	Vector3��Uniform�ϐ���ݒ肷��
    @param	_name �ݒ肷��Uniform�ϐ���
    @param	_vector �ݒ肷��Vector3
    */
    void SetVectorUniform(const char* _name, const Vector3& _vector);

    /*
    @brief	float��Uniform�ϐ���ݒ肷��
    @param	_name �ݒ肷��Uniform�ϐ���
    @param	_value �ݒ肷��float
    */
    void SetFloatUniform(const char* _name, const float& _value);

	/*
	@brief	int��Uniform�ϐ���ݒ肷��
	@param	_name �ݒ肷��Uniform�ϐ���
	@param	_value �ݒ肷��float
	*/
	void SetIntUniform(const char* name, int value);

private:
	/*
	@brief	�V�F�[�_�[���R���p�C������
	@param	_fileName �R���p�C������V�F�[�_�[�̃t�@�C����
	@param	_shaderType �V�F�[�_�[�̎��
	@param	_outShader �V�F�[�_�[��ID�p�̎Q�ƕϐ�
	@return	true : ���� , false : ���s
	*/
	bool CompileShader(const std::string& _fileName,GLenum _shaderType,GLuint& _outShader);

	/*
	@brief	�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
	@param	_shader �V�F�[�_�[��ID
	@return	true : ���� , false : ���s
	*/
	bool IsCompiled(GLuint _shader);
	/*
	@brief	�V�F�[�_�[�������N�o���Ă��邩�m�F
	@param	�V�F�[�_�[��ID
	@return	true : ���� , false : ���s
	*/
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

