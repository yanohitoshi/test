#pragma once
#include "MeshComponent.h"
#include "Math.h"

/*
 @file ChangeColorMeshComponent.h
 @brief MeshComponent���p�������Q�[������shader���g�p���ĐF��ύX���邱�Ƃ��ł���Component�N���X
*/

class ChangeColorMeshComponent :
    public MeshComponent
{
public:

    ChangeColorMeshComponent(GameObject* _owner, bool _skelton, bool _color);
    ~ChangeColorMeshComponent();

    void Draw(Shader* _shader)override;
    void SetColor(const Vector3& _color) { color = _color; }
    
private:
    Vector3 color;

};

