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

	max_skew(0.2f),
	max_sway(1.5f),
	seed_shifting_factor(10.00f),

	CurSoul_(0),
	AllMask_(4),
	CurMask_(4),
	CharmNotches_(5),
	UsingCharmNotches_(0),
	OverlayColor_({0.282, 0.333, 0.482, 1.000})

{
}

KnightData::~KnightData()
{
}

