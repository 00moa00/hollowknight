#include "PreCompile.h"
#include "BossRoomGate.h"
#include "BossGateEffect.h"

BossRoomGate::BossRoomGate() 
{
}

BossRoomGate::~BossRoomGate() 
{
}

void BossRoomGate::Start()
{
	CreateRendererComponent( "Switches and gates_gate_resize0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("DOOR_ANIMATION", FrameAnimation_DESC("Switches and gates_gate_resize0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->ChangeFrameAnimation("DOOR_ANIMATION");

	CreateWallCollisionComponent({ 100, 800 });
	GetWallCollision()->GetTransform().SetWorldPosition({0, 800 /2});

	GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->GetTransform().SetLocalPosition({ 0, GetRenderer()->GetCurTexture()->GetScale().y/2 });


	BossGateEffect* BossGateEffect_ = GetLevel()->CreateActor<BossGateEffect>();
	BossGateEffect_->SetParent(this);

}

void BossRoomGate::Update(float _DeltaTime)
{
}

