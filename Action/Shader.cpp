#include "Shader.h"
#include "Texture.h"
#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
	:vertexShader(0)
	, fragShader(0)
	,shaderProgram(0)
{
}

Shader::~Shader()
{
}

/*
@brief	頂点シェーダーとフラグメントシェーダーのロード
@param	_vertName 頂点シェーダーのファイル名
@param	_fragName 頂点シェーダーのファイル名
@return	true : 成功 , false : 失敗
*/
bool Shader::Load(const std::string & _vertName, const std::string & _fragName)
{
	if (!CompileShader(_vertName,GL_VERTEX_SHADER,vertexShader) ||
		!CompileShader(_fragName,GL_FRAGMENT_SHADER, fragShader))
	{
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	if (!IsVaildProgram())
	{
		return false;
	}

	return true;
}

/*
@brief	ロードしたシェーダーの解放
*/
void Shader::Unload()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

/*
@brief	シェーダープログラムをアクティブにする
*/
void Shader::SetActive()
{
	glUseProgram(shaderProgram);
}

/*
	@brief	行列のUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_matrix 設定する行列
*/
void Shader::SetMatrixUniform(const char * _name, const Matrix4 & _matrix)
{
	GLuint loc = glGetUniformLocation(shaderProgram,_name);
	// シェーダーに行列データを送る
	glUniformMatrix4fv(loc, 1, GL_TRUE, _matrix.GetAsFloatPtr());
}

void Shader::SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count)
{
	GLuint loc = glGetUniformLocation(shaderProgram, _name);
	// 行列配列データをシェーダー変数に送る
	glUniformMatrix4fv(loc, _count, GL_TRUE, _matrices->GetAsFloatPtr());
}

/*
@brief	Vector3のUniform変数を設定する
@param	_name 設定するUniform変数名
@param	_vector 設定するVector3
*/
void Shader::SetVectorUniform(const char * _name, const Vector3 & _vector)
{
    GLuint loc = glGetUniformLocation(shaderProgram, _name);

    // シェーダーにVectorデータを送る
    glUniform3fv(loc, 1, _vector.GetAsFloatPtr());
}

/*
@brief	floatのUniform変数を設定する
@param	_name 設定するUniform変数名
@param	_value 設定するfloat
*/
void Shader::SetFloatUniform(const char * _name, const float & _value)
{
    GLuint loc = glGetUniformLocation(shaderProgram, _name);
    // シェーダーにfloatデータを送る
    glUniform1f(loc, _value);
}

void Shader::SetIntUniform(const char* name, int value)
{
	GLuint loc = glGetUniformLocation(shaderProgram, name);
	// int値をシェーダー変数に送る
	glUniform1i(loc, value);
}


/*
@brief	シェーダーをコンパイルする
@param	_fileName コンパイルするシェーダーのファイル名
@param	_shaderType シェーダーの種類
@param	_outShader シェーダーのID用の参照変数
@return	true : 成功 , false : 失敗
*/
bool Shader::CompileShader(const std::string & _fileName, GLenum _shaderType, GLuint & _outShader)
{
	std::ifstream shaderFile(_fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::ifstream().swap(shaderFile);
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		_outShader = glCreateShader(_shaderType);

		glShaderSource(_outShader, 1, &(contentsChar), nullptr);
		glCompileShader(_outShader);

		if (!IsCompiled(_outShader))
		{
			SDL_Log("Failed to compile shader %s", _fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", _fileName.c_str());
		return false;
	}

	return true;
}

/*
@brief	シェーダーがコンパイル出来ているか確認
@param	_shader シェーダーのID
@return	true : 成功 , false : 失敗
*/
bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	glGetShaderiv(_shader,GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetShaderInfoLog(_shader,411,nullptr,buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/*
@brief	シェーダーがリンク出来ているか確認
@param	シェーダーのID
@return	true : 成功 , false : 失敗
*/
bool Shader::IsVaildProgram()
{
	GLint status;

	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetProgramInfoLog(shaderProgram,511,nullptr,buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}



//シェーダー用関数
//void glUniform1f(GLint location, GLfloat v0);
//void glUniform1fv(GLint location, GLsizei count, const GLfloat* value);
//void glUniform1i(GLint location, GLint v0);
//void glUniform1iv(GLint location, GLsizei count, const GLint* value);
//void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
//void glUniform2fv(GLint location, GLsizei count, const GLfloat* value);
//void glUniform2i(GLint location, GLint v0, GLint v1);
//void glUniform2iv(GLint location, GLsizei count, const GLint* value);
//void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//void glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
//void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
//void glUniform3iv(GLint location, GLsizei count, const GLint* value);
//void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//void glUniform4fv(GLint location, GLsizei count, const GLfloat* value);
//void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//void glUniform4iv(GLint location, GLsizei count, const GLint* value);
//void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);