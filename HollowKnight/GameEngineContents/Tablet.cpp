#include "PreCompile.h"
#include "Tablet.h"
#include "GlobalContentsValue.h"

Tablet::Tablet() 
	:
	isOpenDialogue_(false),

	Alpha_(0.0f),

	BackRenderer_(nullptr),
	LightRenderer_(nullptr),

	Collision_(nullptr),
	PromptSet_(nullptr),
	TabletDialogue_(nullptr)

{
}

Tablet::~Tablet() 
{
}

void Tablet::Start()
{
	TabletManager_.CreateStateMember("IDLE"
		, std::bind(&Tablet::TabletIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletIdleStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletIdleEnd, this, std::placeholders::_1));

	TabletManager_.CreateStateMember("APPEAR"
		, std::bind(&Tablet::TabletAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletAppearStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletAppearEnd, this, std::placeholders::_1));

	TabletManager_.ChangeState("IDLE");
}

void Tablet::Update(float _DeltaTime)
{
	TabletManager_.Update(_DeltaTime);
}

void Tablet::CreateTablet(std::string _BackFilePath, std::string _LightFilePath, float4 _CollSize, TabletType _TabletType)
{
	BackRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackRenderer_->SetTexture(_BackFilePath);
	BackRenderer_->GetTransform().SetLocalScale(BackRenderer_->GetCurTexture()->GetScale());
	BackRenderer_->SetPivot(PIVOTMODE::BOT);

	LightRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LightRenderer_->SetTexture(_LightFilePath);
	LightRenderer_->GetTransform().SetLocalScale(LightRenderer_->GetCurTexture()->GetScale());
	LightRenderer_->SetPivot(PIVOTMODE::BOT);
	LightRenderer_->GetPixelData().MulColor.a = 0.0f;

	LightRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_CollSize);
	Collision_->ChangeOrder(COLLISION_ORDER::Tablet);

	PromptSet_ = GetLevel()->CreateActor<PromptSet>();
	PromptSet_->CreatePrompSet(PromptSetType::SEARCH);
	PromptSet_->SetParent(this);
	PromptSet_->GetTransform().SetLocalPosition({0, 350});
	PromptSet_->GetCollision()->GetTransform().SetLocalPosition({0, -350});

	TabletDialogue_ = GetLevel()->CreateActor<TabletDialogue>();

	switch (_TabletType)
	{
	case TabletType::FocusSpell:
		SpellFocusInfo_ = GetLevel()->CreateActor<SpellFocusInfo>();
		SpellFocusInfo_->SetSpellFocusInfoOff();

		TabletDialogue_->PushDialogue("고귀한 존재들, 당신들을 위해 말한다.\n우리 일원이기에 위대한 힘이 있다.영혼을 집중해 꿈만 같은 일을 이룰 수 있다.", 0);

		break;
	case TabletType::Tu_Story:
		TabletDialogue_->PushDialogue("고귀한 존재들, 당신들을 위해 말한다.\n이곳 너머엔 왕과 창조주의 땅에 들어서게 된다.이 경계를 건넌다면, 우리의 법을 준수하라.", 100);
		TabletDialogue_->PushDialogue("최후이자 유일한 문명, 영원한 왕국을 목격하라.\n신성둥지", 100);
		TabletDialogue_->GetArrow()->GetTransform().SetLocalPosition({0,-50});
		PromptSet_->GetTransform().SetLocalPosition({ 0, 450 });

		break;
	default:
		break;
	}


}

void Tablet::TabletDialogueOn()
{
	TabletDialogue_->On();
	TabletDialogue_->SetDialogueOn();

	if (SpellFocusInfo_ != nullptr)
	{
		SpellFocusInfo_->SetSpellFocusInfoOn();
	}


	isOpenDialogue_ = true;
	PromptSet_->Off();
	GameEngineSound::SoundPlayOneShot("Lore_Tablet_activate_temp.ogg");
}

void Tablet::TabletDialogueOff()
{
	TabletDialogue_->Off();

	TabletDialogue_->SetDialogueOff();
	if (SpellFocusInfo_ != nullptr)
	{
		SpellFocusInfo_->SetSpellFocusInfoOff();
	}
	isOpenDialogue_ = false;
	PromptSet_->On();

}

void Tablet::TabletIdleStart(const StateInfo& _Info)
{
}

void Tablet::TabletIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Alpha_ -= _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ <= 0.0f)
	{
		Alpha_ = 0.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		TabletManager_.ChangeState("APPEAR");
		return;
	}
}

void Tablet::TabletIdleEnd(const StateInfo& _Info)
{
}

void Tablet::TabletAppearStart(const StateInfo& _Info)
{
	LightRenderer_->On();
	//GameEngineSound::SoundPlayOneShot("ui_button_confirm.ogg", 0.1f);

}

void Tablet::TabletAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	Alpha_ += _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ >= 1.0f)
	{
		Alpha_ = 1.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == false
		)
	{
		TabletManager_.ChangeState("IDLE");
		return;
	}


}

void Tablet::TabletAppearEnd(const StateInfo& _Info)
{
	//Alpha_ = 1.0f;
}

void Tablet::TabletOnDialougueStart(const StateInfo& _Info)
{
}

void Tablet::TabletOnDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Tablet::TabletOnDialougueEnd(const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueStart(const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueEnd(const StateInfo& _Info)
{
}

bool Tablet::TabletVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
