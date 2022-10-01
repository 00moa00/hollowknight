#include "PreCompile.h"
#include "MapSpike.h"

MapSpike::MapSpike() 
{
}

MapSpike::~MapSpike() 
{
}

void MapSpike::Start()
{
	CreateCollisionComponent(float4{ 100, 100, 1 }, static_cast<int>(COLLISION_ORDER::Monster));
	GetCollision()->GetTransform().SetWorldPosition({ 0, 105/2, 0 });

	CreateRendererComponent(float4{ 139, 105, 1 }, "spikes0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));

	std::vector<unsigned int>CustomAni;
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(0);
	CustomAni.push_back(1);
	CustomAni.push_back(2);
	CustomAni.push_back(3);

	GetRenderer()->CreateFrameAnimationCutTexture("LIGHT_ANIMATION", FrameAnimation_DESC("spikes0000-Sheet.png", CustomAni, 0.100f, true));
	
	GetRenderer()->ChangeFrameAnimation("LIGHT_ANIMATION");

	SetMoveDirection(float4::UP);

	SetMonsterType(MonsterType::Spike);

}

void MapSpike::Update(float _DeltaTime)
{
}

