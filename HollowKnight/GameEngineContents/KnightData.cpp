#include "PreCompile.h"
#include "KnightData.h"


KnightData* KnightData::Inst_ = new KnightData();

KnightData::KnightData()
	:
	isRefill_(false),
	isShadow_(false),
	isGrowSoul_(false),
	AllMask_(4),
	CurMask_(4)

{
}

KnightData::~KnightData()
{
}

