#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

/*
@file Shader.h
@brief シェーダーデータ
*/
class Shader
{
public:
    Shader();
    ~Shader();
	/*
	@brief	頂点シェーダーとフラグメントシェーダーのロード
	@param	_vertName 頂点シェーダーのファイル名
	@param	_fragName 頂点シェーダーのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& _vertName,const std::string& _fragName);
	/*
	@brief	ロードしたシェーダーの解放
	*/
	void Unload();

	/*
	@brief	シェーダープログラムをアクティブにする
	*/
	void SetActive();

	/*
	@brief	行列のUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_matrix 設定する行列
	*/
	void SetMatrixUniform(const char* _name , const Matrix4& _matrix);
	void SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count);
    /*
    @brief	Vector3のUniform変数を設定する
    @param	_name 設定するUniform変数名
    @param	_vector 設定するVector3
    */
    void SetVectorUniform(const char* _name, const Vector3& _vector);

    /*
    @brief	floatのUniform変数を設定する
    @param	_name 設定するUniform変数名
    @param	_value 設定するfloat
    */
    void SetFloatUniform(const char* _name, const float& _value);

	/*
	@brief	intのUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_value 設定するfloat
	*/
	void SetIntUniform(const char* name, int value);

private:
	/*
	@brief	シェーダーをコンパイルする
	@param	_fileName コンパイルするシェーダーのファイル名
	@param	_shaderType シェーダーの種類
	@param	_outShader シェーダーのID用の参照変数
	@return	true : 成功 , false : 失敗
	*/
	bool CompileShader(const std::string& _fileName,GLenum _shaderType,GLuint& _outShader);

	/*
	@brief	シェーダーがコンパイル出来ているか確認
	@param	_shader シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsCompiled(GLuint _shader);
	/*
	@brief	シェーダーがリンク出来ているか確認
	@param	シェーダーのID
	@return	true : 成功 , false : 失敗
	*/
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

