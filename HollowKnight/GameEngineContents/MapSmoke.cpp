#include "PreCompile.h"
#include "MapSmoke.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "HollowKnightLevel.h"

MapSmoke::MapSmoke() 
	:
	RotatinSpeed_(0.f),
	Speed_(0.f),

	ParticleRenderer_(nullptr)

{
}

MapSmoke::~MapSmoke() 
{
}

void MapSmoke::Start()
{
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ParticleRenderer_->SetTexture("hot_spring_smoke.png");

	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(5.5f, 7.3f);
	ParticleRenderer_->GetTransform().SetLocalScale({ 118.f * RamdomScale, 109.f * RamdomScale });
	ParticleRenderer_->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.3f);

	Speed_ = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);
	RotatinSpeed_ = GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f);


	MapMaxX_ = GetLevel<HollowKnightLevel>()->GetMapSize().x;

	float RamY = GameEngineRandom::MainRandom.RandomFloat(-GetLevel<HollowKnightLevel>()->GetMapSize().y, 0);
	GetTransform().SetLocalPosition({ -GameEngineWindow::GetInst()->GetScale().hx(), RamY , static_cast<float>(Z_ORDER::Back_Back_Object)});

	int RamZ = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (RamZ == 0)
	{
		GetTransform().SetLocalMove({0, 0, -500});

	}

}

void MapSmoke::Update(float _DeltaTime)
{
	if (Speed_ > 0.f)
	{
		float4 Move = float4::RIGHT * Speed_ * _DeltaTime;

		GetTransform().SetLocalMove(Move);
		GetTransform().SetLocalRotate({ 0,0, RotatinSpeed_ * _DeltaTime });


		if (GetTransform().GetLocalPosition().x > MapMaxX_ + 300.f)
		{
			this->Death();
		}
	}


}

void MapSmoke::SetSpeed(float _f)
{
	Speed_ = _f;

	float X = GameEngineRandom::MainRandom.RandomFloat(0, GetLevel<HollowKnightLevel>()->GetMapSize().x );
	float Y = GameEngineRandom::MainRandom.RandomFloat(-GetLevel<HollowKnightLevel>()->GetMapSize().y, 0 );

	float4 Pos = { X ,Y, static_cast<float>(Z_ORDER::Back_Back_Object) };

	int RamZ = GameEngineRandom::MainRandom.RandomInt(0,3);

	if (RamZ == 0)
	{
		Pos.z = -300;
	}

	GetTransform().SetLocalPosition(Pos);


}

