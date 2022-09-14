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

	CurSoul_(0),
	AllMask_(4),
	CurMask_(4),
	CharmNotches_(5),
	UsingCharmNotches_(0)

{
}

KnightData::~KnightData()
{
}

