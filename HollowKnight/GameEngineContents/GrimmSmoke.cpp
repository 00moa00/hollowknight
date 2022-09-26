#include "PreCompile.h"
#include "GrimmSmoke.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmSmoke::GrimmSmoke()
	:
	Alpha_(1.0f),

	RightMoveDir_(float4::ZERO),
	LeftMoveDir_(float4::ZERO)


{
}

GrimmSmoke::~GrimmSmoke() 
{
}

void GrimmSmoke::Start()
{
	for (int i = 0; i < 10; ++i)
	{
		BottomSmoke_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		BottomSmoke_.back()->SetTexture("grimm_smoke2.png", RamdomIndex);
		BottomSmoke_.back()->ScaleToCutTexture(RamdomIndex);

		float RamdomPos = GameEngineRandom::MainRandom.RandomFloat(-150, 150);

		BottomSmoke_.back()->GetTransform().SetLocalPosition({ {GameEngineRandom::MainRandom.RandomFloat(-100, 100), GameEngineRandom::MainRandom.RandomFloat(0, 50) } });
		BottomSmoke_.back()->GetTransform().SetWorldScale({ 102.f * 2.2f, 124.f * 2.2f });
		BottomInitPos_.push_back({ BottomSmoke_ .back()->GetTransform().GetWorldPosition()});

	}
	for (int i = 0; i < 10; ++i)
	{
		TopRightSmoke_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		TopRightSmoke_.back()->SetTexture("grimm_smoke2.png", RamdomIndex);
		TopRightSmoke_.back()->ScaleToCutTexture(RamdomIndex);
		float RamdomPos = GameEngineRandom::MainRandom.RandomFloat(-150, 150);

		TopRightSmoke_.back()->GetTransform().SetLocalPosition({{50 + GameEngineRandom::MainRandom.RandomFloat(-100, 100), 220 + GameEngineRandom::MainRandom.RandomFloat(-100, 100) }});
		TopRightSmoke_.back()->GetTransform().SetWorldScale({ 102.f * 2.0f, 124.f * 2.0f });
		TopRightInitPos_.push_back({ TopRightSmoke_.back()->GetTransform().GetWorldPosition() });


	}

	for (int i = 0; i < 10; ++i)
	{
		TopLeftSmoke_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		TopLeftSmoke_.back()->SetTexture("grimm_smoke2.png", RamdomIndex);
		TopLeftSmoke_.back()->ScaleToCutTexture(RamdomIndex);
		float RamdomPos = GameEngineRandom::MainRandom.RandomFloat(-150, 150);

		TopLeftSmoke_.back()->GetTransform().SetLocalPosition({ {-50 + GameEngineRandom::MainRandom.RandomFloat(-100, 100), 250 + GameEngineRandom::MainRandom.RandomFloat(-100, 100) } });
		TopLeftSmoke_.back()->GetTransform().SetWorldScale({ 102.f * 2.0f, 124.f * 2.0f });
		TopLeftInitPos_.push_back({ TopLeftSmoke_.back()->GetTransform().GetWorldPosition() });

	}

}

void GrimmSmoke::Update(float _DeltaTime)
{
	Alpha_ -= GameEngineRandom::MainRandom.RandomInt(1.2f, 2.0f) * _DeltaTime;
	if (Alpha_ <= 0.f)
	{
		Alpha_ = 0.0f;
	}
	for (int i = 0; i < TopRightSmoke_.size(); ++i)
	{
		float4 Move;
		Move.x = 50.f * GameEngineRandom::MainRandom.RandomFloat(0.f, 0.3f) ;
		Move.y = 20.f ;
		TopRightSmoke_[i]-> GetTransform().SetLocalMove(Move * _DeltaTime);
		TopRightSmoke_[i]->GetPixelData().MulColor.a = Alpha_ ;

	}

	for (int i = 0; i < TopLeftSmoke_.size(); ++i)
	{
		float4 Move;
		Move.x = 60.f * GameEngineRandom::MainRandom.RandomFloat(-0.3f, 0.0f);
		Move.y = 20.f;
		TopLeftSmoke_[i]->GetTransform().SetLocalMove(Move * _DeltaTime);
		//Alpha_ -= GameEngineRandom::MainRandom.RandomInt(0.f, 0.3f);

		TopLeftSmoke_[i]->GetPixelData().MulColor.a = Alpha_ ;

	}


	for (int i = 0; i < BottomSmoke_.size(); ++i)
	{
		float4 Move;
		Move.x = 60.f * GameEngineRandom::MainRandom.RandomFloat(-0.3f, 0.0f);
		Move.y = 10.f;
		BottomSmoke_[i]->GetTransform().SetLocalMove(Move * _DeltaTime);
		//Alpha_ -= GameEngineRandom::MainRandom.RandomInt(0.f, 0.3f);

		BottomSmoke_[i]->GetPixelData().MulColor.a = Alpha_;

	}
}

void GrimmSmoke::SetSmokeOn()
{
	for (int i = 0; i < BottomSmoke_.size(); ++i)
	{
		BottomSmoke_[i]->GetTransform().SetLocalPosition(BottomInitPos_[i]);
		BottomSmoke_[i]->GetPixelData().MulColor.a = 1.0f;
	}

	for (int i = 0; i < TopRightSmoke_.size(); ++i)
	{
		TopRightSmoke_[i]->GetTransform().SetLocalPosition(TopRightInitPos_[i]);
		TopRightSmoke_[i]->GetPixelData().MulColor.a = 1.0f;
	}

	for (int i = 0; i < TopLeftSmoke_.size(); ++i)
	{
		TopLeftSmoke_[i]->GetTransform().SetLocalPosition(TopLeftInitPos_[i]);
		TopLeftSmoke_[i]->GetPixelData().MulColor.a = 1.0f;
	}
	Alpha_ = 1.0f;
	On();
}

void GrimmSmoke::SetSmokeOff()
{
	Off();

}

