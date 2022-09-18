#include "PreCompile.h"
#include "Potal.h"
#include "FadeOut.h"
#include "Knight.h"

Potal::Potal() 
	:
	Level_(""),
	FadeMode_(FadeMode::Max),

	FadeOut_(nullptr),
	FadeIn_(nullptr)
{
}

Potal::~Potal() 
{
}

void Potal::Start()
{
	CreateCollisionComponent({40,40}, static_cast<int>(COLLISION_ORDER::Potal));
	//GetCollision()->SetCollisionMode(CollisionMode::Ex);

}

void Potal::Update(float _DeltaTime)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Potal::PotalVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{

		if (FadeMode_ == FadeMode::FadeOut)
		{
			if (FadeOut_ == nullptr)
			{
				FadeOut_ = GetLevel()->CreateActor<FadeOut>();

			}

		}
		//return;
	}

	if (FadeOut_ != nullptr)
	{
		if (FadeOut_->GetDeathflag() == true)
		{
			GEngine::ChangeLevel(Level_);
			//FadeOut_->Death();
			//FadeOut_ = nullptr;
		}
	}




}

void Potal::LevelStartEvent()
{
}

void Potal::LevelEndEvent()
{
	if (FadeOut_ != nullptr)
	{
		if (FadeOut_->GetDeathflag() == true)
		{
		//	GEngine::ChangeLevel(Level_);
			FadeOut_->Death();
			FadeOut_ = nullptr;
		}
	}
}

void Potal::CreatePotal(std::string _ChangeLevel, FadeMode _Mode)
{
	Level_ = _ChangeLevel;
	FadeMode_ = _Mode;
}

bool Potal::PotalVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Knight* Knight_ = dynamic_cast<Knight*>(_Other->GetActor());
	Knight_->SetKnightisPotal(true);
	return true;
}

