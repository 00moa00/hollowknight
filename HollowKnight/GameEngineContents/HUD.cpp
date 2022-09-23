#include "PreCompile.h"
#include "HUD.h"
#include "KnightData.h"

HUD::HUD() 
	:
	VesselFrame_(nullptr),
	Soul_(nullptr),
	Geo_(nullptr),
	Maskes_(),

	MaskesAppearEnd_(false),

	MaskesSize_(0),
	CurMask_(4),
	MakesAppearCount_(0),
	MaskAppearTimer_(0.f),

	HUDManager_()
{
}

HUD::~HUD() 
{
}

void HUD::Start()
{
	Geo_ = GetLevel()->CreateActor<Geo>();
	Geo_->GetTransform().SetLocalPosition({ -(GameEngineWindow::GetInst()->GetScale().hx() - 220.f), GameEngineWindow::GetInst()->GetScale().hy() - 160.f, -100 });
	

	VesselFrame_ = GetLevel() ->CreateActor<VesselFrame>();
	VesselFrame_ -> GetTransform().SetLocalPosition({ -(GameEngineWindow::GetInst()->GetScale().hx() - 70.f), GameEngineWindow::GetInst()->GetScale().hy() - 50.f, -100 });
	
	Soul_ = GetLevel()->CreateActor<Soul>();

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size()-1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100});

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ - ((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	//CurMask_ = Maskes_.size() - 1;

	//KnightData::GetInst()->SetAllMask(CurMask_);
//	KnightData::GetInst()->SetCurMask(CurMask_);
	CurMask_ = KnightData::GetInst()->GetAllMask();

	HUDManager_.CreateStateMember("MASK_APPEAR"
		, std::bind(&HUD::MaskAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HUD::MaskAppearStart, this, std::placeholders::_1)
		, std::bind(&HUD::MaskAppearEnd, this, std::placeholders::_1));

	HUDManager_.CreateStateMember("IDLE"
		, std::bind(&HUD::HUDIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HUD::HUDIdleStart, this, std::placeholders::_1)
		, std::bind(&HUD::HUDIdleEnd, this, std::placeholders::_1));

	HUDManager_.CreateStateMember("HIDE"
		, std::bind(&HUD::HUDHideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HUD::HUDHideStart, this, std::placeholders::_1)
		, std::bind(&HUD::HUDHideEnd, this, std::placeholders::_1));



	HUDManager_.ChangeState("MASK_APPEAR");

}

void HUD::Update(float _DeltaTime)
{
	HUDManager_.Update(_DeltaTime);
}

void HUD::LevelStartEvent()
{

	if (KnightData::GetInst()->GetisHUD() == true)
	{
		HUDManager_.ChangeState("IDLE");
		CurMask_ = KnightData::GetInst()->GetCurMask();
		VesselFrame_->SetIdleAnimation();
		Geo_->SetIdleState();

		for (int i = 0; i < MaskesSize_  ; ++i)
		{
			

			if (i > CurMask_)
			{
				Maskes_[i]->SetisBroken();
				Maskes_[i]->SetBrokenAnimation();

			}

			else
			{
				Maskes_[i]->SetisIdle();
			}

		}
	}
	KnightData::GetInst()->SetisHUD(true);
	Soul_ -> SetSoul(KnightData::GetInst()->GetCurSoul());
}

void HUD::LevelEndEvent()
{
	CurMask_;
	KnightData::GetInst()->SetCurSoul(Soul_->GetSoulLevel());
}

void HUD::NewMask()
{
	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1.f) * 60.f)), GameEngineWindow::GetInst()->GetScale().hy() - 55.f, -100.f });
	MaskesSize_ = Maskes_.size();

	
	Maskes_[MaskesSize_-1]->SetNewAppearState();
	KnightData::GetInst()->SetAllMask(MaskesSize_);
}

void HUD::RefillMask()
{
	// 가장 앞 + 이미 채워진 가면 뒤에것 먼저 채운다
	for (int i = 0; i < MaskesSize_; ++i)
	{
		if (Maskes_[i]->GetisBroken() == true)
		{
			Maskes_[i]->SetisRefill();
			CurMask_ = i;

			KnightData::GetInst()->SetCurMask(CurMask_);
			return;
		}
	}
}

void HUD::BreakMask()
{
	// 가장 뒤에 있는 가면 먼저 깍는다
	for (int i = Maskes_.size()-1; i >= 0; --i)
	{
		if (Maskes_[i]->GetisIdle() == true)
		{
			Maskes_[i]->SetisBroken();
			--CurMask_;

			KnightData::GetInst()->SetCurMask(CurMask_);
			return;
		}
	}
}

void HUD::AllRefillMask()
{
	for (int   i = 0; i < MaskesSize_; ++i)
	{
		Maskes_[i]->SetisRefill();
	}
	KnightData::GetInst()->SetCurMask(MaskesSize_);
}

void HUD::SetAppearAnimation()
{

}



void HUD::MaskAppearStart(const StateInfo& _Info)
{
	MaskesSize_ = static_cast<int>(Maskes_.size());
}

void HUD::MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MaskAppearTimer_ += _DeltaTime;

	if (MaskAppearTimer_ > 0.3f )
	{
		MaskAppearTimer_ = 0.0f;

		//마지막 가면도 반짝! 하기 위해서.
		if (MakesAppearCount_ == Maskes_.size())
		{
			HUDManager_.ChangeState("IDLE");
		}
		else
		{
			//Maskes_[MakesAppearCount_]->SetisIdle();p
			Maskes_[MakesAppearCount_]->SetAppearState();
			++MakesAppearCount_;
		}
	}
}

void HUD::MaskAppearEnd(const StateInfo& _Info)
{
	MakesAppearCount_ = 0;

	for (int i = 0; i < MaskesSize_; ++i)
	{
		//Maskes_[i]->SetisIdle();
		Maskes_[i]->SetIdleState();
	}
}

void HUD::HUDIdleStart(const StateInfo& _Info)
{
}

void HUD::HUDIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (KnightData::GetInst()->GetisSetting() == true)
	{
		HUDManager_.ChangeState("HIDE");

	}

	//리필
	if (KnightData::GetInst()->GetisRefill() == true)
	{
		RefillMask();
		KnightData::GetInst()->SetisRefill(false);
	}

	//깨짐
	if (KnightData::GetInst()->GetisBreak() == true)
	{
		BreakMask();
		KnightData::GetInst()->SetisBreak(false);
	}

	// 나이트 죽음
	if (KnightData::GetInst()->GetisDeath() == true)
	{
		KnightData::GetInst()->SetisDeath(false);

		for (int i = 0; i < MaskesSize_; ++i)
		{
			Maskes_[i]->SetIdleState();
		}
		KnightData::GetInst()->SetCurMask(MaskesSize_-1);
		CurMask_ = MaskesSize_ - 1;
		Geo_->SetBreakState();
	}

	// 영혼 성장
	if (KnightData::GetInst()->GetisGrowSoul() == true)
	{
		KnightData::GetInst()->SetisSoulGrow(false);
		Soul_->GrowSoulLevel();
	}

}

void HUD::HUDIdleEnd(const StateInfo& _Info)
{

}

void HUD::HUDHideStart(const StateInfo& _Info)
{

	Geo_->Off();
	VesselFrame_->Off();
	Soul_->Off();

	for (int i = 0; i < Maskes_.size(); ++i)
	{
		Maskes_[i]->Off();
	}

}

void HUD::HUDHideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (KnightData::GetInst()->GetisSetting() == false)
	{
		HUDManager_.ChangeState("IDLE");
	}

}

void HUD::HUDHideEnd(const StateInfo& _Info)
{
	Geo_->On();
	VesselFrame_->On();
	Soul_->On();

	for (int i = 0; i < Maskes_.size(); ++i)
	{
		Maskes_[i]->On();
	}
}

