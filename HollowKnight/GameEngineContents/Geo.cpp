#include "PreCompile.h"
#include "Geo.h"

Geo::Geo() 
	:
	isAppearEnd_(false),
	isGetEnd_(false),
	isIdleEnd_(false),
	isBreakEnd_(false),

	GeoManager_()
{
}

Geo::~Geo() 
{
}

void Geo::Start()
{
	CreateRendererComponent(float4{ 62, 62, 1 }, "HUD Cln_HUD_coin_v020000-Sheet.png", 4, static_cast<int>(RENDERORDER::UI));

	//================================
	//    Create Animation
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("GET_ANIMATION", FrameAnimation_DESC("HUD Cln_coin_get0001-Sheet.png", 0, 1, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("BREAK_ANIMATION", FrameAnimation_DESC("HUD Cln_HUD_coin_break_short0000-Sheet.png", 0, 5, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("APEAR_ANIMATION", FrameAnimation_DESC("HUD Cln_HUD_coin_v020000-Sheet.png", 0, 4, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("HUD Cln_HUD_coin_v020000-Sheet.png", 4, 4, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("BROKEN_ANIMATION", FrameAnimation_DESC("HUD Cln_coin_get0001-Sheet.png", 2, 2, 0.050f, false));

	GetRenderer()->SetScaleModeImage();

	GetRenderer()->ChangeFrameAnimation("APEAR_ANIMATION");
	GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);

	//================================
	//    Create Bind Animation
	//================================
	GetRenderer()->AnimationBindEnd("GET_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isGetEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("BREAK_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isBreakEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("APEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isAppearEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("IDLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isIdleEnd_ = true;
		});

	//================================
	//    Create State
	//================================
	GeoManager_.CreateStateMember("APPEAR",
		std::bind(&Geo::GeoAppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Geo::GeoAppearStart, this, std::placeholders::_1),
		std::bind(&Geo::GeoAppearEnd, this, std::placeholders::_1));

	GeoManager_.CreateStateMember("GET",
		std::bind(&Geo::GeoGetUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Geo::GeoGetStart, this, std::placeholders::_1),
		std::bind(&Geo::GeoGetEnd, this, std::placeholders::_1));

	GeoManager_.CreateStateMember("IDLE",
		std::bind(&Geo::GeoIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Geo::GeoIdleStart, this, std::placeholders::_1),
		std::bind(&Geo::GeoIdleEnd, this, std::placeholders::_1));

	GeoManager_.CreateStateMember("BREAK",
		std::bind(&Geo::GeoBreakUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Geo::GeoBreakStart, this, std::placeholders::_1),
		std::bind(&Geo::GeoBreakEnd, this, std::placeholders::_1));

	GeoManager_.CreateStateMember("BROKEN",
		std::bind(&Geo::GeoBrokenUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Geo::GeoBrokenStart, this, std::placeholders::_1),
		std::bind(&Geo::GeoBrokenEnd, this, std::placeholders::_1));


	GeoManager_.ChangeState("APPEAR");

}

void Geo::Update(float _DeltaTime)
{
	GeoManager_.Update(_DeltaTime);
}

void Geo::GeoAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("APEAR_ANIMATION");

}

void Geo::GeoAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isAppearEnd_ == true)
	{
		isAppearEnd_ = false;
		GeoManager_.ChangeState("IDLE");
	}
}

void Geo::GeoAppearEnd(const StateInfo& _Info)
{
}

void Geo::GeoGetStart(const StateInfo& _Info)
{
}

void Geo::GeoGetUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Geo::GeoGetEnd(const StateInfo& _Info)
{
}

void Geo::GeoIdleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
}

void Geo::GeoIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Geo::GeoIdleEnd(const StateInfo& _Info)
{
}

void Geo::GeoBreakStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("BREAK_ANIMATION");

}

void Geo::GeoBreakUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isBreakEnd_ == true)
	{
		isBreakEnd_ = false;
		GeoManager_.ChangeState("BROKEN");
	}
}

void Geo::GeoBreakEnd(const StateInfo& _Info)
{
	
}

void Geo::GeoBrokenStart(const StateInfo& _Info)
{
}

void Geo::GeoBrokenUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GeoManager_.ChangeState("IDLE");

}

void Geo::GeoBrokenEnd(const StateInfo& _Info)
{
}
