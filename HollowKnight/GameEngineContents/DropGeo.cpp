#include "PreCompile.h"
#include "DropGeo.h"

DropGeo::DropGeo() 
{
}

DropGeo::~DropGeo() 
{
}

void DropGeo::Start()
{
	CreateRendererComponent(float4{ 62, 62, 1 }, "HUD Cln_HUD_coin_v020000-Sheet.png", 4, static_cast<int>(RENDERORDER::UI));
	CreateCollisionComponent(float4{ 60, 120, 1 }, static_cast<int>(OBJECTORDER::Geo));

	//================================
	//    Create Animation
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("AIR_ANIMATION", FrameAnimation_DESC("Geo_coin_air000-Sheet.png", 0, 8, 0.050f));
	GetRenderer()->CreateFrameAnimationCutTexture("GROUND_ANIMATION", FrameAnimation_DESC("Geo_coin0000-Sheet.png", 0, 8, 0.050f));
	
	GetRenderer()->SetScaleModeImage();

	GetRenderer()->ChangeFrameAnimation("AIR_ANIMATION");
	GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);


	//================================
	//    Create Bind Animation
	//================================

	//================================
	//    Create State
	//================================
	DropGeoManager_.CreateStateMember("AIR",
		std::bind(&DropGeo::DropGeoAirUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&DropGeo::DropGeoAirStart, this, std::placeholders::_1),
		std::bind(&DropGeo::DropGeoAirEnd, this, std::placeholders::_1));

	DropGeoManager_.CreateStateMember("DROP",
		std::bind(&DropGeo::DropDeoOnGroundUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&DropGeo::DropDeoOnGroundStart, this, std::placeholders::_1),
		std::bind(&DropGeo::DropDeoOnGroundEnd, this, std::placeholders::_1));

	DropGeoManager_.ChangeState("AIR");

}

void DropGeo::Update(float _DeltaTime)
{
}

void DropGeo::DropGeoAirStart(const StateInfo& _Info)
{
}

void DropGeo::DropGeoAirUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void DropGeo::DropGeoAirEnd(const StateInfo& _Info)
{
}

void DropGeo::DropDeoOnGroundStart(const StateInfo& _Info)
{
}

void DropGeo::DropDeoOnGroundUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void DropGeo::DropDeoOnGroundEnd(const StateInfo& _Info)
{
}

