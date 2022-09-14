#include "PreCompile.h"
#include "KnightData.h"


KnightData* KnightData::Inst_ = new KnightData();

KnightData::KnightData()
	:
	isRefill_(false),
	isShadow_(false),
	isGrowSoul_(false),
	isSetting_(false),
	isHUD_(false),
	isRevive_(false),
	isOverlayflag_(false),
	SavedPaletteInit_(false),

	MainLightMulColor_(),
	MainLightPlusColor_(),
		
	SlibingLightMulColor_(),
	SlibingLightPlusColor_(),

	DounutLightMulColor_(),
	DounutLightPlusColor_(),

	MaxSkew(0.2f),
	MaxSway(1.5f),
	SeedShiftingFactor(10.00f),

	CurSoul_(0),
	AllMask_(4),
	CurMask_(4),
	CharmNotches_(5),
	UsingCharmNotches_(0),
	OverlayColor_({0.282, 0.333, 0.482, 1.000}),

	MainLighBlend_(BlendMode::Alpha),
	SlibingLighBlend_(BlendMode::Alpha),
	DounutLighBlend_ (BlendMode::Alpha)
{
}

KnightData::~KnightData()
{
}

