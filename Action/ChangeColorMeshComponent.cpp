#include "ChangeColorMeshComponent.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"

ChangeColorMeshComponent::ChangeColorMeshComponent(GameObject* _owner, bool _skelton,bool _color)
	:MeshComponent(_owner, _skelton,_color)
{
}

ChangeColorMeshComponent::~ChangeColorMeshComponent()
{
}

void ChangeColorMeshComponent::Draw(Shader* _shader)
{
	_shader->SetVectorUniform("uColor", color);
	//通常のメッシュコンポーネントの描画
	MeshComponent::Draw(_shader);
}
