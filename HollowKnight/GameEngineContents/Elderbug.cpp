#include "PreCompile.h"
#include "Elderbug.h"

Elderbug::Elderbug() 
{
}

Elderbug::~Elderbug() 
{
}

void Elderbug::Start()
{
	SetNPCName("Àå·Î¹ú·¹");

	GetTransform().SetWorldPosition({ 4400, -3050.f, static_cast<int>(Z_ORDER::NPC)});
	
	CreatePromptSet();
	GetPromptSet()->GetTransform().SetLocalPosition({0, 150.f});
	GetPromptSet()->GetCollision()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	CreateRendererComponent("Elderbug_idle_01-Sheet.png", 0);
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Elderbug_idle_01-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

	CreateCollisionComponent(float4{ 500, 120, 1 }, static_cast<int>(OBJECTORDER::Elderbug));

	ElderManager_.CreateStateMember("WAIT"
		, std::bind(&Elderbug::EldeWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Elderbug::EldeWaitStart, this, std::placeholders::_1)
		, std::bind(&Elderbug::EldeWaitEnd, this, std::placeholders::_1));

	ElderManager_.CreateStateMember("IDLE"
		, std::bind(&Elderbug::ElderIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Elderbug::ElderIdleStart, this, std::placeholders::_1)
		, std::bind(&Elderbug::ElderIdleEnd, this, std::placeholders::_1));

	ElderManager_.CreateStateMember("CHANGE_DIR"
		, std::bind(&Elderbug::ElderChangeDirUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Elderbug::ElderChangeDirStart, this, std::placeholders::_1)
		, std::bind(&Elderbug::ElderChangeDirEnd, this, std::placeholders::_1));

	ElderManager_.CreateStateMember("LEAVE"
		, std::bind(&Elderbug::ElderChangeLeaveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Elderbug::ElderChangeLeaveStart, this, std::placeholders::_1)
		, std::bind(&Elderbug::ElderChangeLeaveEnd, this, std::placeholders::_1));

	ElderManager_.ChangeState("WAIT");

}

void Elderbug::Update(float _DeltaTime)
{
	ElderManager_.Update(_DeltaTime);


}

bool Elderbug::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}


void Elderbug::EldeWaitStart(const StateInfo& _Info)
{
}

void Elderbug::EldeWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Elderbug::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		ElderManager_.ChangeState("IDLE");
	}
}

void Elderbug::EldeWaitEnd(const StateInfo& _Info)
{
}

void Elderbug::ElderIdleStart(const StateInfo& _Info)
{
}

void Elderbug::ElderIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Elderbug::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{		
		ElderManager_.ChangeState("LEAVE");
	}


}

void Elderbug::ElderIdleEnd(const StateInfo& _Info)
{

}

void Elderbug::ElderChangeDirStart(const StateInfo& _Info)
{
}

void Elderbug::ElderChangeDirUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ElderManager_.ChangeState("IDLE");

}

void Elderbug::ElderChangeDirEnd(const StateInfo& _Info)
{
}

void Elderbug::ElderChangeLeaveStart(const StateInfo& _Info)
{
}

void Elderbug::ElderChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Elderbug::ElderChangeLeaveEnd(const StateInfo& _Info)
{
}
