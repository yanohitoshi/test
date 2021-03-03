#include "VertexArray.h"
#include <glew.h>

/*
@param	頂点バッファの配列のポインタ
@param	頂点数
@param	インデックスバッファの配列のポインタ
@param	インデックスの数
*/
VertexArray::VertexArray(const float* _verts, unsigned int _numVerts,
	const unsigned int* _indices, unsigned int _numIndices)
	:numVerts(_numVerts)
	,numIndices(_numIndices)
{
	// 頂点配列の作成
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// 頂点バッファの作成
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 8 * sizeof(float), _verts, GL_STATIC_DRAW);

	// インデクスバッファの作成
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	//最初の頂点属性を有効に（位置座標）
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//頂点属性インデックス（位置座標）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		0						//頂点データの開始位置からこの属性までのオフセット
	);
	//第2の頂点属性を有効に（法線ベクトル）
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//頂点属性インデックス（法線ベクトル）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		reinterpret_cast<void*>(sizeof(float) * 3));	//オフセットポインタ
    //第3の頂点属性を有効に（テクスチャ座標）
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,						//頂点属性インデックス（テクスチャ座標）
        2,						//要素の数（UVは2個）
        GL_FLOAT,				//要素の型
        GL_FALSE,				//（GL_FLOATには使わない）
        sizeof(float) * 8,		//各頂点のサイズ
        reinterpret_cast<void*>(sizeof(float) * 6));	//オフセットポインタ
}

VertexArray::VertexArray(const void * verts, unsigned int _numVerts, Layout layout, const unsigned int * indices, unsigned int _numIndices)
	:numVerts(_numVerts)
	, numIndices(_numIndices)
{
	// 頂点配列の作成
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// 頂点レイアウトが スケルタルモデルなら　ボーンID、影響度分をサイズ増やす
	unsigned vertexSize = 8 * sizeof(float);
	if (layout == PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// 頂点バッファの作成
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, verts, GL_STATIC_DRAW);

	// インデックスバッファの作成
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// 頂点属性
	if (layout == PosNormTex)
	{
		// float 3個分　→　位置 x,y,z　位置属性をセット
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// 次のfloat 3個分 → 法線 nx, ny, nz　法線属性をセット
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// 次のfloat 2個分 u, v  テクスチャ座標属性をセット
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == PosNormSkinTex)
	{
		// float 3個分　→　位置 x,y,z　位置属性をセット
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// 次のfloat 3個分 → 法線 nx, ny, nz　法線属性をセット
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		//　影響受けるボーンインデックス番号  (int型をキープ)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// ボーンウェイト情報 (float に変換)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// 次のfloat 2個分 u, v  テクスチャ座標属性をセット
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}


VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

/*
@brief	頂点配列をアクティブにする
*/
void VertexArray::SetActive()
{
	glBindVertexArray(vertexArray);
}
