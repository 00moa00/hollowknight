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
	SetNPCName("장로벌레");
	SetNPCType(NPC_TYPE::Normal);

	GetTransform().SetWorldPosition({ 4400, -3045.f, static_cast<int>(Z_ORDER::NPC)});
	CreateNameFontRenderer();
	CreatePromptSet();
	//GetPromptSet()->GetTransform().SetLocalPosition({0, 150.f});
	//GetPromptSet()->GetCollision()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	//GetPromptSet()->SetParent(this);

	CreateRendererComponent("Elderbug_idle_01-Sheet.png", 0);
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Elderbug_idle_01-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	//GetRenderer()->GetPixelData().MulColor = { 1,1,1,1 };

	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(COLLISION_ORDER::NPC));

	CreateDialogueSet();
	//GetDialogueSet()->SetParent(this);
	GetDialogueSet()->PushDialogue("이보시오, 여행자.여행자를 맞이할 수 있는 이는 나밖에 안 남은 것 같소.보다시피 마을이 조용해졌소.");
	//GetDialogueSet()->PushDialogue("다른 주민들은 모두 사라졌소.저 우물을 통해 아래로, 하나씩, 아래에 있는 동굴로.");
	//GetDialogueSet()->PushDialogue("우리 마을 아래에는 위대한 왕국이 있었소.폐허가 된지 오래지만, 아직도 그 깊은 곳으로 많은 이들을 유인하지.");
	//GetDialogueSet()->PushDialogue("부와 영광과 깨달음, 저 어둠이 모든 것을 약속하는 것처럼 보이지.분명 당신도 저 아래에 있는 꿈을 쫓고 있겠지.");
	//GetDialogueSet()->PushDialogue("조심하오.역겨운 공기가 그곳을 채우고 있소.생명체들은 미쳐가고 여행자들은 기억을 빼앗기지.");
	//GetDialogueSet()->PushDialogue("아마도 꿈은 그렇게 대단한 것이 아닐지도...");

	GetDialogueSet()->SetDialogueOff();

	
	ElderManager_.CreateStateMember("WAIT"
		, std::bind(&Elderbug::ElderWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Elderbug::ElderWaitStart, this, std::placeholders::_1)
		, std::bind(&Elderbug::ElderWaitEnd, this, std::placeholders::_1));

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


void Elderbug::ElderWaitStart(const StateInfo& _Info)
{
}

void Elderbug::ElderWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Elderbug::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		ElderManager_.ChangeState("IDLE");
	}
}

void Elderbug::ElderWaitEnd(const StateInfo& _Info)
{
}

void Elderbug::ElderIdleStart(const StateInfo& _Info)
{
}

void Elderbug::ElderIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
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
