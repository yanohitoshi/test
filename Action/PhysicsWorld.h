#pragma once

#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include "Math.h"
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;
class LineSegmentCollider;
class PlaneCollider;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

/*
@file PhysicsWorld.h
@brief 当たり判定を行うclass
*/

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//当たり判定
    void HitCheck();
    void HitCheck(BoxCollider* _box);
    void HitCheck(SphereCollider* _sphere);
	void HitCheck(LineSegmentCollider* _line);


    void AddBox(BoxCollider* _box, onCollisionFunc _func);
    void RemoveBox(BoxCollider* _box);
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	void RemoveSphere(SphereCollider* _sphere);
	void AddLineSegment(LineSegmentCollider* _line, onCollisionFunc _func);
	void RemoveLineSegment(LineSegmentCollider* _line);
	void AddPlane(PlaneCollider* _plane, onCollisionFunc _func);
	void RemovePlane(PlaneCollider* _plane);

	void Debug();


private:
	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	//void SphereAndSphere();
	//void BoxAndBox();
	//void SphereAndBox();

	//それぞれのobjectごとのAABBの可変長配列
	std::vector<BoxCollider*> boxes;
    std::vector<BoxCollider*> playerBoxes;
	std::vector<BoxCollider*> wallBoxes;
	std::vector<BoxCollider*> groundBoxes;
	std::vector<BoxCollider*> moveGroundBoxes;
	std::vector<BoxCollider*> switchBoxes;
	std::vector<BoxCollider*> switchBaseBoxes;
	std::vector<BoxCollider*> needlePlaneBoxes;
	std::vector<BoxCollider*> jumpSwitchBoxes;
	std::vector<BoxCollider*> groundCheckBoxes;
	std::vector<BoxCollider*> footCheckBoxes;
	std::vector<BoxCollider*> cameraBoxes;
	std::vector<BoxCollider*> clearPointBoxes;
	std::vector<BoxCollider*> respownPointBoxes;


	//それぞれのsphereごとのAABBの可変長配列
	std::vector<SphereCollider*> groundCheckSpheres;
	std::vector<SphereCollider*> switchCheckSpheres;
	//std::vector<SphereCollider*> spheres;
	std::vector<LineSegmentCollider*> lines;
	std::vector<PlaneCollider*> planes;
	onCollisionMap collisionFunction;

};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
