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
	isOverlayflag_(true),
	SavedPaletteInit_(false),
	isBossBattle_(false),
	isBreak_(false),
	isCameraGUI_(false),
	isDeath_(false),
	isKnihgt_(false),
	isNewMask_(false),
	isSitting_(false),
	isEffectGUI_(false),
	isIntroFallEvent_(false),

	MainLightMulColor_({1.0f, 1.0f, 1.0f, 0.7f}),
	MainLightPlusColor_({ 0.0f, 0.0f, 0.0f, 0.0f }),
		
	SlibingLightMulColor_({ 1.0f, 1.0f, 1.0f, 1.0f }),
	SlibingLightPlusColor_({ 0.348f, 0.564f, 0.653f, 0.0f }),

	DounutLightMulColor_({ 1.0f, 1.0f, 1.0f, 0.3f }),
	DounutLightPlusColor_({ 0.0f, 0.0f, 0.0f, 0.0f }),

	MaxSkew(0.2f),
	MaxSway(1.5f),
	SeedShiftingFactor(10.00f),

	CurSoul_(0),
	AllMask_(4),
	CurMask_(4),
	CharmNotches_(5),
	UsingCharmNotches_(0),
	HitDamage_(0),


	OverlayColor_(0.499f, 0.592f, 0.726f, 1.0f),

	MainLighBlend_(BlendMode::Alpha),
	SlibingLighBlend_(BlendMode::Alpha),
	DounutLighBlend_ (BlendMode::Alpha),

	PrevLevel_(""),
	CurrentLevel_("")
{
}

KnightData::~KnightData()
{
}

