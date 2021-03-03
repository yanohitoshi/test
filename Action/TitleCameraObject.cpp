#include "TitleCameraObject.h"
#include "Renderer.h"

TitleCameraObject::TitleCameraObject(const Vector3 _pos)
	:CameraObjectBase(false, Tag::TITLE_OBJECT)
{
	//Title用に表示してるobjectから少し離れた位置に配置
	SetPosition(Vector3(_pos.x - 300.0f, _pos.y, _pos.z + 300.0f));
	//Title用のマップクリエイターから中心になるオブジェクトの位置をカメラのターゲットに保存
	target = _pos;
	target.x = target.x + 800.0f;		//見る位置の微調整
}

TitleCameraObject::~TitleCameraObject()
{
}

void TitleCameraObject::UpdateGameObject(float _deltaTime)
{
	//view行列を生成
	view = Matrix4::CreateLookAt(position, Vector3(target), Vector3(0.0f, 0.0f, 1.0f));
	//レンダラーのview行列にセット
	RENDERER->SetViewMatrix(view);
}

void TitleCameraObject::GameObjectInput(const InputState& _keyState)
{
}
