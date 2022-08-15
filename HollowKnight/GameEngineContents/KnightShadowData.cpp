#include "PreCompile.h"
#include "KnightShadowData.h"

KnightShadowData* KnightShadowData::Inst_ = new KnightShadowData();


KnightShadowData::KnightShadowData() 
	:
	ShadowPosition_(),
	isShadowDepart_(false)
{
}

KnightShadowData::~KnightShadowData() 
{
}

