#pragma once
#include "GameObject.h"

class SpriteComponent;

class GameBackGroundSprite :
    public GameObject
{
public:
    GameBackGroundSprite(SceneState _sceneTag);
    ~GameBackGroundSprite();
    void UpdateGameObject(float _deltaTime)override;
private:

    SpriteComponent* sprite;

};

