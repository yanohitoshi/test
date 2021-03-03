#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "GameObject.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* owner)
	:MeshComponent(owner, true,false)
	, skeleton(nullptr)
	, color(Vector3(0,0,0))
{
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::Draw(Shader* shader)                 
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			//���[���h�ϊ����Z�b�g
			shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// �s��p���b�g���Z�b�g    
			shader->SetMatrixUniforms("uMatrixPalette", &palette.mEntry[0],
				MAX_SKELETON_BONES);
			//�X�y�L�����[���x���Z�b�g
			shader->SetFloatUniform("uSpecPower", 25);

			shader->SetVectorUniform("uColor", color);

			shader->SetFloatUniform("uLuminance", mesh->GetLuminace());

			SetTextureToShader(shader);

			//���b�V���̒��_�z����A�N�e�B�u��
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			//�`��
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
		if (animation && skeleton)
		{
			animTime += deltaTime * animPlayRate;
			if (animation->IsLoopAnimation())
			{
				//  �A�j���������߂��čĐ�
				while (animTime > animation->GetDuration())
				{
					animTime -= animation->GetDuration();
				}
			}
			// ���[�v���Ȃ��A�j���ōĐ����Ԓ�������ŏI���Ԃ܂łƂ���
			else if (animTime > animation->GetDuration())
			{
				animTime = animation->GetDuration();
			}

			////  �A�j���������߂��čĐ�
			//while (animTime > animation->GetDuration())
			//{
			//	animTime -= animation->GetDuration();
			//}


			// �s��p���b�g�̍Čv�Z
			ComputeMatrixPalette();
		}
	
}

float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	animation = _anim;
	animTime = 0.0f;
	animPlayRate = _playRate;

	if (!animation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return animation->GetDuration();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// �O���[�o���t�o�C���h�s��z��̎擾
	const std::vector<Matrix4>& globalInvBindPoses = skeleton->GetGlobalInvBindPoses();   
	// ���݂̃|�[�Y�s��
	std::vector<Matrix4> currentPoses;                                        
	// �A�j���������_�̃O���[�o���|�[�Y�̎擾
	animation->GetGlobalPoseAtTime(currentPoses, skeleton, animTime);      
	// ���ꂼ��̃{�[���̍s��p���b�g�̃Z�b�g                                    
	for (size_t i = 0; i < skeleton->GetNumBones(); i++)
	{
		//�s��p���b�g[i] = �O���[�o���t�o�C���h�s��[i]�@�~�@���݂̃|�[�Y�s��[i]  (i�̓{�[��ID)         
		palette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}

bool SkeletalMeshComponent::IsPlaying()
{

	if (!animation->IsLoopAnimation())
	{
		if (animTime >= animation->GetDuration())
		{
			return false;
		}
	}

	return true;
}


void SkeletalMeshComponent::SetTextureToShader(Shader* shader)
{
	// ���b�V���e�N�X�`���Z�b�g
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DiffuseMap); // �f�B�t���[�Y
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::NormalMap); // �@���}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::SpecularMap); // �X�y�L�����[�}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::EmissiveMap); // ���ȕ��˃}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}
