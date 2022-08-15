#include "PreCompile.h"
#include "Mask.h"
#include <GameEngineBase/GameEngineTime.h>

Mask::Mask()
	:
	IdleAnimationTimer_(0.f),

	isAppearEnd_(false),
	isBreakEnd_(false),
	isRefillEnd_(false),
	isNewAppearEnd_(false),
	isIdleAnimationEnd_(false),

	MaskManager_()
{
}

Mask::~Mask()
{
}

void Mask::Start()
{
	CreateRendererComponent(float4{ 113, 150, 1 }, "HUD Cln_idle_v020000-Sheet.png", 0, static_cast<int>(RENDERORDER::UI));
	//GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hy() - 100, -100 });
	
	//================================
	//    Create Animation
	//================================

	GetRenderer()->CreateFrameAnimationCutTexture("MASK_WAIT", FrameAnimation_DESC("MaskWait.png", 0, 0, 0.050f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("MASK_IDLE_ANIMATION", FrameAnimation_DESC("HUD Cln_idle_v020000-Sheet.png", 0, 5, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_IDLE", FrameAnimation_DESC("HUD Cln_idle_v020000-Sheet.png", 0, 0, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_APPEAR", FrameAnimation_DESC("HUD Cln_appear_v020000-Sheet.png", 0, 4, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_NEW_APPEAR", FrameAnimation_DESC("HUD Cln_add_health_appear0000-Sheet.png", 0, 13, 0.150f, false));	
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_REFILL", FrameAnimation_DESC("HUD Cln_refill0000-Sheet.png", 0, 5, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_BREAK", FrameAnimation_DESC("HUD Cln_break_backboard0000-Sheet.png", 0, 5, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MASK_BROKEN", FrameAnimation_DESC("HUD Cln_refill0000-Sheet.png", 0, 0, 0.050f, false));
	
	GetRenderer()->SetScaleModeImage();

	GetRenderer()->ChangeFrameAnimation("MASK_WAIT");
	GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);


	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("MASK_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isAppearEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MASK_REFILL", [=](const FrameAnimation_DESC& _Info)
		{
			isAppearEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MASK_BREAK", [=](const FrameAnimation_DESC& _Info)
		{
			isBreakEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MASK_NEW_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isNewAppearEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MASK_IDLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isIdleAnimationEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MASK_REFILL", [=](const FrameAnimation_DESC& _Info)
		{
			isRefillEnd_ = true;
		});


	//================================
	//    Create State
	//================================

	MaskManager_.CreateStateMember("WAIT"
		, std::bind(&Mask::MaskWaitUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskWaitStart, this, std::placeholders::_1), std::bind(&Mask::MaskWaitEnd, this, std::placeholders::_1));

	MaskManager_.CreateStateMember("APPEAR"
		, std::bind(&Mask::MaskAppearUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskAppearStart, this, std::placeholders::_1), std::bind(&Mask::MaskAppearEnd, this, std::placeholders::_1));

	MaskManager_.CreateStateMember("IDLE"
		, std::bind(&Mask::MaskIdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskIdleStart, this, std::placeholders::_1), std::bind(&Mask::MaskIdleEnd, this, std::placeholders::_1));
	
	MaskManager_.CreateStateMember("NEW_APPEAR"
		, std::bind(&Mask::MaskNewAppearUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskNewAppearStart, this, std::placeholders::_1), std::bind(&Mask::MaskNewAppearEnd, this, std::placeholders::_1));

	MaskManager_.CreateStateMember("BREAK"
		, std::bind(&Mask::MaskBreakUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskBreakStart, this, std::placeholders::_1), std::bind(&Mask::MaskBreakEnd, this, std::placeholders::_1));

	MaskManager_.CreateStateMember("BROKEN"
		, std::bind(&Mask::MaskBrokenUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskBrokenStart, this, std::placeholders::_1), std::bind(&Mask::MaskBrokenEnd, this, std::placeholders::_1));

	MaskManager_.CreateStateMember("REFILL"
		, std::bind(&Mask::MaskRefillUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Mask::MaskRefillStart, this, std::placeholders::_1), std::bind(&Mask::MaskRefillEnd, this, std::placeholders::_1));

	MaskManager_.ChangeState("WAIT");

}

void Mask::Update(float _DeltaTime)
{
	MaskManager_.Update(_DeltaTime);




}

void Mask::SetWaitState()
{
	MaskManager_.ChangeState("WAIT");
}

void Mask::SetAppearState()
{
	MaskManager_.ChangeState("APPEAR");
}

void Mask::SetNewAppearState()
{
	MaskManager_.ChangeState("NEW_APPEAR");

}

void Mask::SetIdleState()
{
	MaskManager_.ChangeState("IDLE");
}

void Mask::MaskWaitStart(const StateInfo& _Info)
{
	IdleAnimationTimer_ = 0.0f;

	GetRenderer()->ChangeFrameAnimation("MASK_WAIT");

}

void Mask::MaskWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Mask::MaskWaitEnd(const StateInfo& _Info)
{
}

void Mask::MaskAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("MASK_APPEAR");

}

void Mask::MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isAppearEnd_ == true)
	{
		isAppearEnd_ = false;
		GetRenderer()->ChangeFrameAnimation("MASK_IDLE");
	}
}

void Mask::MaskAppearEnd(const StateInfo& _Info)
{
	

}

void Mask::MaskIdleStart(const StateInfo& _Info)
{
	IdleAnimationTimer_ = 0.0f;

	SetisIdle();
	GetRenderer()->ChangeFrameAnimation("MASK_IDLE");
}

void Mask::MaskIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//GameEngineTime::GetInst()->SetTimeScale(1, 1.0f);

	if (GetisBroken() == true)
	{
		MaskManager_.ChangeState("BREAK");
	}

	else if (GetisRefill() == true)
	{
		MaskManager_.ChangeState("REFILL");
	}

	else if (GetisAppear() == true)
	{
		MaskManager_.ChangeState("APPEAR");
	}

	else if (GetisNewAppear() == true)
	{
		MaskManager_.ChangeState("NEW_APPEAR");
	}


	IdleAnimationTimer_ += _DeltaTime;

	if (IdleAnimationTimer_ > 3.0f && isIdleAnimationEnd_ == false)
	{
		IdleAnimationTimer_ = 0.0f;
		GetRenderer()->ChangeFrameAnimation("MASK_IDLE_ANIMATION");
	}

	if (isIdleAnimationEnd_ == true)
	{
		isIdleAnimationEnd_ = false;
		GetRenderer()->ChangeFrameAnimation("MASK_IDLE");
	}
}

void Mask::MaskIdleEnd(const StateInfo& _Info)
{
}

void Mask::MaskBreakStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("MASK_BREAK");

}

void Mask::MaskBreakUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isBreakEnd_ == true)
	{
		isBreakEnd_ = false;
		MaskManager_.ChangeState("BROKEN");
	}



}

void Mask::MaskBreakEnd(const StateInfo& _Info)
{
}

void Mask::MaskBrokenStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("MASK_BROKEN");

}

void Mask::MaskBrokenUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GetisRefill() == true)
	{
		MaskManager_.ChangeState("REFILL");
	}

	else if (GetisAppear() == true)
	{
		MaskManager_.ChangeState("APPEAR");
	}

	else if (GetisNewAppear() == true)
	{
		MaskManager_.ChangeState("NEW_APPEAR");
	}

}

void Mask::MaskBrokenEnd(const StateInfo& _Info)
{

}

void Mask::MaskRefillStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("MASK_REFILL");

}

void Mask::MaskRefillUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isRefillEnd_ == true)
	{
		isRefillEnd_ = false;
		MaskManager_.ChangeState("IDLE");

	}

}

void Mask::MaskRefillEnd(const StateInfo& _Info)
{
}

void Mask::MaskNewAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("MASK_NEW_APPEAR");

}

void Mask::MaskNewAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isNewAppearEnd_ == true)
	{
		isNewAppearEnd_ = false;
		GetRenderer()->ChangeFrameAnimation("MASK_IDLE");

	}
}

void Mask::MaskNewAppearEnd(const StateInfo& _Info)
{
}
