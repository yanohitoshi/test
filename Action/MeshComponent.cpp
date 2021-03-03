#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton スケルトンデータを用いるか。
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton,bool _color)
	:Component(_owner)
	, mesh(nullptr)
	, textureIndex(0)
	, visible(true)
	, isSkelton(_skelton)
	, isColorChange(_color)
{
	//レンダラーにポインターを送る
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveMeshComponent(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());

			_shader->SetFloatUniform("uLuminance", mesh->GetLuminace());

			SetTextureToShader(_shader);

			// Set the argMesh's vertex array as active
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void MeshComponent::SetTextureToShader(Shader* shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DiffuseMap); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::NormalMap); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::SpecularMap); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::EmissiveMap); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}
