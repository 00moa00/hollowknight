#include "PreCompile.h"
#include "TutorialGate.h"
#include "HollowKnightLevel.h"
#include "KnightSlashEffect.h"

#include "DoorStoneParticle.h"
#include "LargeStoneParticle.h"

#include <GameEngineBase/GameEngineRandom.h>

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
	CreateCollisionComponent({ 250.f, 1061.f, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	CreateWallCollisionComponent({ 250.f, 1061.f});

	GetWallCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });

	SetHitCount(10);
}

void TutorialGate::Update(float _DeltaTime)
{
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
			GEngine::ChangeLevel("FireballPromptLevel");
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
		int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (RamSound == 0)
		{
			GameEngineSound::SoundPlayOneShot("breakable_wall_hit_2.ogg");
		}

		else if (RamSound == 1)
		{
			GameEngineSound::SoundPlayOneShot("breakable_wall_hit_1.ogg");
		}

		GameEngineSound::SoundPlayOneShot("breakable_wall_death.ogg");

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
			GameEngineSound::SoundPlayOneShot("breakable_wall_death.ogg");
			return;
		}

		isColl_ = true;
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);

		for (int i = 0; i < 4; ++i)
		{
			DoorStoneParticle* DoorStoneParticle_ = GetLevel()->CreateActor<DoorStoneParticle>();
			DoorStoneParticle_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x , GetTransform().GetWorldPosition().y + 1061.f / 2 });
			DoorStoneParticle_->SetDir(float4::LEFT);
			DoorStoneParticle_->SetRamPos(0, 1061.f );
			DoorStoneParticle_->SetSpeed(2500.f);
		}

		for (int i = 0; i < 2; ++i)
		{
			LargeStoneParticle* LargeStoneParticle_ = GetLevel()->CreateActor<LargeStoneParticle>();
			LargeStoneParticle_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x  , GetTransform().GetWorldPosition().y + 1061.f / 2 });
			LargeStoneParticle_->SetDir(float4::LEFT);
			LargeStoneParticle_->SetRamPos(0, 1061.f);
		}
	}

}

bool TutorialGate::ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;

}
