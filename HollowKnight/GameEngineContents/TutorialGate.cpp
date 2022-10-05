#include "PreCompile.h"
#include "TutorialGate.h"
#include "HollowKnightLevel.h"
#include "KnightSlashEffect.h"

TutorialGate::TutorialGate()
	:
	isColl_(false),
	isGateDeath_(false),

	BlackRenderer_(nullptr)
{
}

TutorialGate::~TutorialGate() 
{
}

void TutorialGate::Start()
{

	BlackRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BlackRenderer_->SetTexture("Black.png");
	BlackRenderer_->GetTransform().SetLocalScale({3000.f, 3000.f});
	BlackRenderer_->Off();

	CreateRendererComponent({ 964.f, 1061.f, 1 }, "Tute Great Door_door_v01.png");
	//GetR

	CreateCollisionComponent({ 250.f, 1061.f, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	CreateWallCollisionComponent({ 250.f, 1061.f});

	GetWallCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });

	SetHitCount(10);

}

void TutorialGate::Update(float _DeltaTime)
{
	//if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight_Slash, CollisionType::CT_OBB2D,
	//	std::bind(&TutorialGate::ObjectVSEffectCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	//{
	//	//DoorStoneParticle* DoorStoneParticle_ = GetLevel()->CreateActor<DoorStoneParticle>();
	//	//DoorStoneParticle_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y + 100.f });
	//	//DoorStoneParticle_->SetDir(GetLevel<HollowKnightLevel>()->GetKnight()->GetKnightSlashEffect()->GetDir());
	//	//this->Death();
	//}
	if (isColl_ == true)
	{
		if (GetAccTime() > 1.0f)
		{
			isColl_ = false;
			ReSetAccTime();
			GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);

		}
	}

	if (isGateDeath_ == true)
	{
		if (GetAccTime() > 1.0f)
		{
			GEngine::ChangeLevel("DirtmouthLevel1");
			return;

		}
	}
}

void TutorialGate::LevelEndEvent()
{
	if (isGateDeath_ == true)
	{
		Death();
	}
}

void TutorialGate::SetHitCollision()
{
	if (isGateDeath_ == false)
	{
		SubHitCount();

		if (GetHitCount() == 6)
		{
			GetRenderer()->SetTexture("Tute Great Door_door_v02.png");
		}

		if (GetHitCount() == 3)
		{
			GetRenderer()->SetTexture("Tute Great Door_door_v03.png");
		}

		if (GetHitCount() == 0)
		{
			GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);
			BlackRenderer_->On();
			ReSetAccTime();
			isGateDeath_ = true;

			float4 Pos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

			BlackRenderer_->GetTransform().SetWorldPosition({ Pos.x, Pos.y, -1000 });

			return;
		}

		isColl_ = true;
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);

	}

}

bool TutorialGate::ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;

}
