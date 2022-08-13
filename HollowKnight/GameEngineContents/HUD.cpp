#include "PreCompile.h"
#include "HUD.h"
#include "KnightData.h"

HUD::HUD() 
	:
	VesselFrame_(nullptr),

	MaskesAppearEnd_(false),

	MaskesSize_(0),
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
	VesselFrame_ = GetLevel() ->CreateActor<VesselFrame>();
	VesselFrame_ -> GetTransform().SetLocalPosition({ -(GameEngineWindow::GetInst()->GetScale().hx() - 70.f), GameEngineWindow::GetInst()->GetScale().hy() - 50.f, -100 });

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

	HUDManager_.CreateStateMember("MASK_APPEAR"
		, std::bind(&HUD::MaskAppearUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&HUD::MaskAppearStart, this, std::placeholders::_1), std::bind(&HUD::MaskAppearEnd, this, std::placeholders::_1));

	HUDManager_.CreateStateMember("IDLE"
		, std::bind(&HUD::HUDIdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&HUD::HUDIdleStart, this, std::placeholders::_1), std::bind(&HUD::HUDIdleEnd, this, std::placeholders::_1));

	HUDManager_.ChangeState("MASK_APPEAR");

}

void HUD::Update(float _DeltaTime)
{
	HUDManager_.Update(_DeltaTime);

}

void HUD::NewMask()
{
	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });
	MaskesSize_ = Maskes_.size();

	
	Maskes_[MaskesSize_-1]->SetNewAppearState();
	

}

void HUD::RefillMask()
{
	// 가장 앞 + 이미 채워진 가면 뒤에것 먼저 채운다


	std::vector<Mask*>::iterator MaskStart_ = Maskes_.begin();
	std::vector<Mask*>::iterator MaskEnd_ = Maskes_.end();

	for (; MaskStart_ != MaskEnd_; ++MaskStart_)
	{

		if ((*MaskStart_)->GetisBroken() == true)
		{
			(*MaskStart_)->SetisRefill();
		}

	}

}

void HUD::BreakMask()
{
	// 가장 뒤에 있는 가면 먼저 깍는다
	for (int i = Maskes_.size(); i >= 0; --i)
	{
		if (Maskes_[i]->GetisIdle() == true)
		{
			Maskes_[i]->SetisBroken();
			return;
		}

	}
}

void HUD::MaskAppearStart(const StateInfo& _Info)
{
	MaskesSize_ = Maskes_.size();

}

void HUD::MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MaskAppearTimer_ += _DeltaTime;

	if (MaskAppearTimer_ > 0.3f * MakesAppearCount_)
	{
		//마지막 가면도 반짝! 하기 위해서.
		if (MakesAppearCount_ == Maskes_.size())
		{
			HUDManager_.ChangeState("IDLE");
		}
		else
		{
			Maskes_[MakesAppearCount_]->SetAppearState();
			++MakesAppearCount_;
		}
	}
}

void HUD::MaskAppearEnd(const StateInfo& _Info)
{
	MaskAppearTimer_ = 0.0f;
	MakesAppearCount_ = 0;

	for (int i = 0; i < MaskesSize_; ++i)
	{
		Maskes_[i]->SetIdleState();
	}
}

void HUD::HUDIdleStart(const StateInfo& _Info)
{
}

void HUD::HUDIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (KnightData::GetInst()->GetisRefill() == true)
	{
		NewMask();
		KnightData::GetInst()->SetisRefill(false);
	}

}

void HUD::HUDIdleEnd(const StateInfo& _Info)
{
}

