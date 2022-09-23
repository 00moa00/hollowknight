#include "PreCompile.h"
#include "TabletDialogue.h"

TabletDialogue::TabletDialogue()
	:
	SaveDialogueScale_(),

	CurrentDialoguePage_(0),
	Alpha_(0.f),

	isDialougueFull_(false),

	NextArrow_(nullptr),
	DialogueBack_(nullptr),
	Back_(nullptr)
{
}

TabletDialogue::~TabletDialogue() 
{
}

void TabletDialogue::Start()
{


	Back_ = CreateComponent<GameEngineUIRenderer>();
	Back_->SetTexture("BlackBoard.png");
	Back_->GetTransform().SetLocalScale(Back_->GetCurTexture()->GetScale());
	Back_->GetPixelData().MulColor.a = 0.6f;
	Back_->Off();

	DialogueBack_ = CreateComponent<GameEngineUIRenderer>();
	DialogueBack_->SetTexture("lore_prompt_new.png");
	DialogueBack_->GetTransform().SetLocalScale(DialogueBack_->GetCurTexture()->GetScale()*1.6f);
	DialogueBack_->GetPixelData().MulColor.a = 0.3f;

	SaveDialogueScale_ = DialogueBack_->GetTransform().GetWorldScale();

	NextArrow_ = CreateComponent<GameEngineUIRenderer>();
	NextArrow_->SetTexture("Dialogue Cln_arrow_down0000-Sheet.png");
	NextArrow_->GetTransform().SetLocalScale(NextArrow_->GetCurTexture()->GetCutScale(0));

	NextArrow_->CreateFrameAnimationCutTexture("ARROW_NEXT_ANIMATION", FrameAnimation_DESC("Dialogue Cln_arrow_down0000-Sheet.png", 0, 5, 0.120f));
	NextArrow_->CreateFrameAnimationCutTexture("ARROW_FULL_ANIMATION", FrameAnimation_DESC("Dialogue Cln_fullstop0000-Sheet.png", 0, 3, 0.120f));
	NextArrow_->ChangeFrameAnimation("ARROW_NEXT_ANIMATION");
	NextArrow_->Off();


	DialogueBack_->Off();


	TabletDoalogueManager_.CreateStateMember("IDLE"
		, std::bind(&TabletDialogue::DialougeIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TabletDialogue::DialougeIdleStart, this, std::placeholders::_1)
		, std::bind(&TabletDialogue::DialougeIdleEnd, this, std::placeholders::_1));

	TabletDoalogueManager_.CreateStateMember("APPEAR"
		, std::bind(&TabletDialogue::DialougeAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TabletDialogue::DialougeAppearStart, this, std::placeholders::_1)
		, std::bind(&TabletDialogue::DialougeAppearEnd, this, std::placeholders::_1));

	TabletDoalogueManager_.CreateStateMember("CLOSE"
		, std::bind(&TabletDialogue::DialougeCloseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TabletDialogue::DialougeCloseStart, this, std::placeholders::_1)
		, std::bind(&TabletDialogue::DialougeCloseEnd, this, std::placeholders::_1));

	TabletDoalogueManager_.ChangeState("IDLE");
}

void TabletDialogue::Update(float _DeltaTime)
{
	TabletDoalogueManager_.Update(_DeltaTime);
}

void TabletDialogue::DialougeIdleStart(const StateInfo& _Info)
{
}

void TabletDialogue::DialougeIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void TabletDialogue::DialougeIdleEnd(const StateInfo& _Info)
{
}

void TabletDialogue::DialougeAppearStart(const StateInfo& _Info)
{
	Alpha_ = 0.0f;
}

void TabletDialogue::DialougeAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	Alpha_ += 0.8f * _DeltaTime;
	Back_->GetPixelData().MulColor.a = Alpha_;
	if (Alpha_ > 0.7f)
	{
		TabletDoalogueManager_.ChangeState("IDLE");
		return;
	}

	float4 Currnet = DialogueBack_->GetTransform().GetWorldScale();
	float4 Dest = SaveDialogueScale_ + 100.f;
	float4 Move = float4::Lerp(Currnet, Dest, GameEngineTime::GetDeltaTime() * 30.f);

	DialogueBack_->GetTransform().SetWorldScale({ Move.x,Move.y });


}

void TabletDialogue::DialougeAppearEnd(const StateInfo& _Info)
{
}

void TabletDialogue::DialougeCloseStart(const StateInfo& _Info)
{
}

void TabletDialogue::DialougeCloseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Alpha_ -= 0.8f * _DeltaTime;
	Back_->GetPixelData().MulColor.a = Alpha_;
	if (Alpha_ <= 0.f)
	{
		TabletDoalogueManager_.ChangeState("IDLE");
		return;
	}

	float4 Currnet = DialogueBack_->GetTransform().GetWorldScale();
	float4 Dest = SaveDialogueScale_ ;
	float4 Move = float4::Lerp(Currnet, Dest, GameEngineTime::GetDeltaTime() * 30.f);

	DialogueBack_->GetTransform().SetWorldScale({ Move.x,Move.y });

}

void TabletDialogue::DialougeCloseEnd(const StateInfo& _Info)
{
	this->Off();
	Back_->Off();
	DialogueBack_->Off();
}
