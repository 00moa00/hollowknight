#include "PreCompile.h"

#include "Bench.h"
#include "GlobalContentsValue.h"

Bench::Bench() 
{
}

Bench::~Bench() 
{
}

void Bench::Start()
{
	CreateRendererComponent({187, 97, 1}, "bench.png");
	CreateCollisionComponent({ 187, 97, 1 }, static_cast<int>(COLLISION_ORDER::Bench));

	GetTransform().SetLocalPosition({4600, -3080.f, static_cast<float>(Z_ORDER::Object)});
}

void Bench::Update(float _DeltaTime)
{
}

