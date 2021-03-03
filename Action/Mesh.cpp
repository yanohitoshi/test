#include "Mesh.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include "Math.h"
#include "Collision.h"
#include "RapidJsonHelper.h"


int LoadStageTextures(const rapidjson::Document& doc, TextureStage texStage, const char* stgString);

namespace
{
	union Vertex
	{
		float f;
		uint8_t b[4];
	};
}


Mesh::Mesh()
	: vertexArray(nullptr)
	, radius(0.0f)
	, specPower(100.0f)
	, luminance(1.0f)
	, mBox(Vector3::Infinity, Vector3::NegInfinity)
{
	stageDefTexture.emplace(TextureStage::DiffuseMap, 0);
	stageDefTexture.emplace(TextureStage::NormalMap, 0);
	stageDefTexture.emplace(TextureStage::SpecularMap, 0);
	stageDefTexture.emplace(TextureStage::EmissiveMap, 0);

}

Mesh::~Mesh()
{
}


/*
@brief  ���b�V���f�[�^�̓ǂݍ���
@param _fileName	���[�h���������b�V���̃t�@�C����
@param _renderer Renderer�N���X�̃|�C���^
@return true : ���� , false : ���s
*/
bool Mesh::Load(const std::string & _fileName, Renderer* _renderer)
{
	std::ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s", _fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s is not valid json", _fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// �o�[�W�����̃`�F�b�N
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", _fileName.c_str());
		return false;
	}

	shaderName = doc["shader"].GetString();

	// Skip the vertex format/shader for now
	// (This is changed in a later chapter's code)
	// ���_���C�A�E�g�ƃT�C�Y���t�@�C������Z�b�g
	VertexArray::Layout layout = VertexArray::PosNormTex;
	size_t vertSize = 8;

	std::string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::PosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s�@1�̒��_�̏W���̐��@�W�@�{�@�Q�i�X�L�j���O���j
		// 3 (�ʒuxyz) + 3(�@��xyz) + 2(Bone�Əd�݁j�{�@2(UV)  �̌v�@10���i40byte) �@
		vertSize = 10;
	}

	// �e�N�X�`���̃��[�h
	const rapidjson::Value& readTextures = doc["textures"];
	if (!readTextures.IsArray() || readTextures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", _fileName.c_str());
		return false;
	}

	specPower = static_cast<float>(doc["specularPower"].GetDouble());

	// �G�~�b�V�u���x�l�i��`����Ă����)
	if (IsExistMember(doc, "luminance"))
	{
		luminance = ForceGetFloat(doc["luminance"]);
	}

	// �e�N�X�`���ǂݍ��݁i���t�@�C���`��)
	for (rapidjson::SizeType i = 0; i < readTextures.Size(); i++)
	{
		// ���łɃ��[�h���ꂽ�e�N�X�`������Ȃ������ׂ�
		std::string texName = readTextures[i].GetString();
		Texture* t = _renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// �e�N�X�`�������[�h����
			t = _renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// �e�N�X�`�������[�h�ł��Ȃ������ꍇ�A�f�t�H���g�̃e�N�X�`�����g�p
				t = _renderer->GetTexture("Assets/Default.png");
			}
		}
		textures.emplace_back(t);

		if (readTextures.Size() == 1)
		{
			stageDefTexture[TextureStage::DiffuseMap] = t->GetTextureID();
		}
	}

	// �e�N�X�`���ǂݍ���(�V�t�@�C���`��)
	if (IsExistMember(doc, "diffusemap"))
	{
		stageDefTexture[TextureStage::DiffuseMap] = LoadStageTextures(doc, TextureStage::DiffuseMap, "diffusemap");
	}
	stageDefTexture[TextureStage::NormalMap] = LoadStageTextures(doc, TextureStage::NormalMap, "normalmap");
	stageDefTexture[TextureStage::SpecularMap] = LoadStageTextures(doc, TextureStage::SpecularMap, "specularmap");
	stageDefTexture[TextureStage::EmissiveMap] = LoadStageTextures(doc, TextureStage::EmissiveMap, "emissivemap");


	// ���_�z��f�[�^�����[�h
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", _fileName.c_str());
		return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	radius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// ���̂Ƃ���͂W�̗v�f�Ƃ���
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
			SDL_Log("Unexpected vertex format for %s", _fileName.c_str());
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////
		Vector3 pos(static_cast<float>(vert[0].GetDouble()),
			static_cast<float>(vert[1].GetDouble()),
			static_cast<float>(vert[2].GetDouble()));
		//verts.push_back(pos);
		radius = Math::Max(radius, pos.LengthSq());

		if (i == 0)
		{
			mBox.InitMinMax(pos);
		}
		mBox.UpdateMinMax(pos);

		// ���_���C�A�E�g�� PosNormTex�Ȃ�i�{�[���������j
		if (layout == VertexArray::PosNormTex)
		{
			Vertex v;
			// Add the floats�@float�l��ǉ�
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal�@���_�Ɩ@����ǉ��@6��
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information�@�X�L�����ǉ��i�{�[���ԍ�:unsigned char��1�o�C�g���j
			for (rapidjson::SizeType j = 6; j < 14; j += 4)  //���[�v�Ƃ��Ă�2��]����@1��]�ڂ̓{�[���ԍ��A2��]�ڂ̓{�[���E�F�C�g��int�Ƃ��Ď���Ă���i�g�p���ɕ���������������ۂ��j
			{
				v.b[0] = vert[j].GetUint();
				v.b[1] = vert[j + 1].GetUint();
				v.b[2] = vert[j + 2].GetUint();
				v.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords�@�e�N�X�`�����W
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
	}

	// ���a��2�悷��
	radius = Math::Sqrt(radius);

	// �v�f�z��f�[�^�̃��[�h
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", _fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", _fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// ������VertexArray�N���X�̍쐬
	vertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		layout,indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

/*
@brief  ���[�h�������b�V���f�[�^�̉��
*/
void Mesh::Unload()
{
	delete vertexArray;
	vertexArray = nullptr;
}

/*
@brief  �e�N�X�`����Getter
*/
Texture* Mesh::GetTexture(size_t _index)
{
	if (_index < textures.size())
	{
		return textures[_index];
	}
	else
	{
		return nullptr;
	}
}

int Mesh::GetTextureID(TextureStage stage)
{
	return stageDefTexture[stage];
}

int LoadStageTextures(const rapidjson::Document& doc, TextureStage texStage, const char* stgString)
{
	std::string noneTexture("none");
	std::string texName;
	Texture* t;
	if (IsExistMember(doc, stgString))
	{
		texName = doc[stgString].GetString();
		if (texName != noneTexture)
		{
			t = RENDERER->GetTexture(texName);
			if (t == nullptr)
			{
				t = RENDERER->GetTexture("Assets/Default.png");
			}
			return t->GetTextureID();
		}
	}
	return 0;
}

