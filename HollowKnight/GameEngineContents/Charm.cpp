#include "PreCompile.h"
#include "Charm.h"

Charm::Charm() 
	:
	isRendererDeathFlag_(false),
	isDeathFlag_(false),
	CharmPointer_(nullptr)
{
}

Charm::~Charm() 
{
}

void Charm::Start()
{

	//=========================================
	//    SettingPointerInventoyPageManager
	//=========================================

	CharmManager_.CreateStateMember("IDLE"
		, std::bind(&Charm::PointerCharmIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Charm::PointerCharmIdleStart, this, std::placeholders::_1)
		, std::bind(&Charm::PointerCharmIdleEnd, this, std::placeholders::_1));

	CharmManager_.CreateStateMember("MOVE"
		, std::bind(&Charm::PointerCharmMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Charm::PointerCharmMoveStart, this, std::placeholders::_1)
		, std::bind(&Charm::PointerCharmMoveEnd, this, std::placeholders::_1));


	CharmManager_.ChangeState("IDLE");
}

void Charm::Update(float _DeltaTime)
{
	CharmManager_.Update(_DeltaTime);
}

void Charm::CreateCharm(std::string _Name, std::string _FilePath, float4 Scale)
{
	CreateRendererComponent(Scale, _FilePath);
	GetRenderer()->GetTransform().SetLocalScale(
		{ GetRenderer()->GetCurTexture()->GetScale().x * 0.55f 
		,  GetRenderer()->GetCurTexture()->GetScale().y * 0.55f 
		, 1});

	CharmName_ = _Name;

}

void Charm::PointerCharmIdleStart(const StateInfo& _Info)
{

}

void Charm::PointerCharmIdleUpdate(float _DeltaTime, const StateInfo& _Info) 
{

}

void Charm::PointerCharmIdleEnd(const StateInfo& _Info)
{

}

void Charm::PointerCharmMoveStart(const StateInfo& _Info)
{
	GetRenderer()->GetTransform().SetWorldPosition(RendererMove_.StartDir_);
}

void Charm::PointerCharmMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = RendererMove_.EndDir_ - GetRenderer()->GetTransform().GetWorldPosition();
	float Lenth = MoveDir.Length();

	MoveDir.Normalize();
	if (Lenth <= 550.f * _DeltaTime)
	{
		CharmManager_.ChangeState("IDLE");
		return;
	}

	GetRenderer()->GetTransform().SetWorldMove(MoveDir * 550.f * _DeltaTime);
}

void Charm::PointerCharmMoveEnd(const StateInfo& _Info)
{
	GetRenderer()->GetTransform().SetWorldPosition(RendererMove_.EndDir_);
	
	if (isRendererDeathFlag_ == true)
	{
		GetRenderer()->Death();
	}
	
	isRendererDeathFlag_ = false;

	if (CharmPointer_ != nullptr)
	{
		CharmPointer_->GetRenderer()->On();

		CharmPointer_->GetRenderer()->GetPixelData().MulColor.r = 1;
		CharmPointer_->GetRenderer()->GetPixelData().MulColor.g = 1;
		CharmPointer_->GetRenderer()->GetPixelData().MulColor.b = 1;
		CharmPointer_ = nullptr;
	}

	if (isDeathFlag_ == true)
	{
		this->Death();
	}

}