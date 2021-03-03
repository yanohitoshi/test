#pragma once

class VertexArray
{
public:
	// 頂点レイアウト列挙
	enum Layout
	{
		PosNormTex,     // 位置&法線&テクスチャUV を持ったフォーマット
		PosNormSkinTex  // 位置&法線& "スキン用の影響ボーン＆重み情報" & テクスチャUV 
	};

	/*
	@param	頂点バッファの配列のポインタ
	@param	頂点数
	@param	インデックスバッファの配列のポインタ
	@param	インデックスの数
	*/
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);
	VertexArray(const void* verts, unsigned int numVerts, Layout layout,  // 頂点配列コンストラクタ 
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	/*
	@brief	頂点配列をアクティブにする（描画に使用できるようにする）
	*/
	void SetActive();

	/*
	@brief	インデックスバッファにあるインデックスの数を取得する
	@return numIndices（インデックスの数）
	*/
	unsigned int GetNumIndices() const { return numIndices; }

	/*
	@brief	頂点バッファにある頂点の数を取得する
	@return numVerts（頂点の数）
	*/
	unsigned int GetNumVerts() const { return numVerts; }

private:
	//頂点バッファにある頂点の数
	unsigned int numVerts;
	//インデクスバッファにあるインデックスの数
	unsigned int numIndices;
	//頂点バッファのOpenGL ID
	unsigned int vertexBuffer;
	//インデックスバッファのOpenGL ID
	unsigned int indexBuffer;
	//頂点配列オブジェクトのOpenGL ID
	unsigned int vertexArray;
};

