#include "PreCompile.h"
#include "KnightData.h"


KnightData* KnightData::Inst_ = new KnightData();

KnightData::KnightData()
	:
	isRefill_(false)

{
}

KnightData::~KnightData()
{
}

