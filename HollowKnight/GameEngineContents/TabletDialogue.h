#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsFontRenderer.h"
// Ό³Έν :
class TabletDialogue : public GameEngineActor
{
public:
	// constrcuter destructer
	TabletDialogue();
	~TabletDialogue();

	// delete Function
	TabletDialogue(const TabletDialogue& _Other) = delete;
	TabletDialogue(TabletDialogue&& _Other) noexcept = delete;
	TabletDialogue& operator=(const TabletDialogue& _Other) = delete;
	TabletDialogue& operator=(TabletDialogue&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool isDialougueFull_;

	int CurrentDialoguePage_;

	float Alpha_;
	float4 SaveDialogueScale_;

	std::vector<ContentsFontRenderer*> DialogueList_;

	GameEngineUIRenderer* NextArrow_;
	GameEngineUIRenderer* DialogueBack_;
	GameEngineUIRenderer* Back_;

	GameEngineStateManager TabletDoalogueManager_;

public:
	//================================
	//     Getter
	//================================
	bool GetDialougueFull()
	{
		return isDialougueFull_;
	}

	GameEngineUIRenderer* GetArrow()
	{
		return NextArrow_;
	}


	//================================
	//    Setter
	//================================

	void SetOnePage()
	{
		isDialougueFull_ = true;
		NextArrow_->ChangeFrameAnimation("ARROW_FULL_ANIMATION");
		NextArrow_->GetTransform().SetLocalScale(NextArrow_->GetCurTexture()->GetCutScale(0));

	}

	void SetDialogueOn()
	{
		this->On();
		Back_->On();
		DialogueBack_->On();
		NextArrow_->On();

		DialogueList_.front()->GetFontRenderer()->On();
		DialogueList_.front()->FontOn();
		TabletDoalogueManager_.ChangeState("APPEAR");

	}

	void SetDialogueOff()
	{
		CurrentDialoguePage_ = 0;
		if (DialogueList_.size() == 1)
		{
			isDialougueFull_ = true;
		}
		else
		{
			isDialougueFull_ = false;
		}

		for (int i = 0; i < DialogueList_.size(); ++i)
		{
			DialogueList_[i]->GetFontRenderer()->Off();
		}

		NextArrow_->Off();
		TabletDoalogueManager_.ChangeState("CLOSE");


	}


	void PushDialogue(std::string _Dialougue, float _MarginY)
	{
		DialogueList_.push_back(GetLevel()->CreateActor<ContentsFontRenderer>());
		DialogueList_.back()->CreateFontRenderer(
			_Dialougue
			, 37
			, { GameEngineWindow::GetInst()->GetScale().hx() , GameEngineWindow::GetInst()->GetScale().hy()-(370.f - _MarginY) },
			true,
			true,
			27
		);

		//DialogueList_.back()->Ge SetParent(this);
		DialogueList_.back()->Off();
		DialogueList_.back()->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);

		if (DialogueList_.size() == 1)
		{
			isDialougueFull_ = true;
		}
		else
		{
			isDialougueFull_ = false;
		}

	}

	void SetNextDialogue()
	{
		if (isDialougueFull_ == false)
		{

			//if (CurrentDialoguePage_ == DialogueList_.size() - 1)
			//{
			//	isDialougueFull_ = true;
			//	return;
			//}

			++CurrentDialoguePage_;


			if (CurrentDialoguePage_ == DialogueList_.size()-1 )
			{
				CurrentDialoguePage_ = DialogueList_.size() - 1;
				isDialougueFull_ = true;
				NextArrow_->ChangeFrameAnimation("ARROW_FULL_ANIMATION");
				NextArrow_->GetTransform().SetLocalScale(NextArrow_->GetCurTexture()->GetCutScale(0));

				//return;

			}
			NextArrow_->ChangeFrameAnimation("ARROW_NEXT_ANIMATION");
			NextArrow_->GetTransform().SetLocalScale(NextArrow_->GetCurTexture()->GetCutScale(0));

			for (int i = 0; i < DialogueList_.size(); ++i)
			{
				if (CurrentDialoguePage_ == i)
				{
					continue;
				}
				DialogueList_[i]->GetFontRenderer()->Off();
			}

			DialogueList_[CurrentDialoguePage_]->GetFontRenderer()->On();
			DialogueList_[CurrentDialoguePage_]->FontOn();



		}
	}

private:
	void DialougeIdleStart(const StateInfo& _Info);
	void DialougeIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void DialougeIdleEnd(const StateInfo& _Info);


	void DialougeAppearStart(const StateInfo& _Info);
	void DialougeAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void DialougeAppearEnd(const StateInfo& _Info);

	void DialougeCloseStart(const StateInfo& _Info);
	void DialougeCloseUpdate(float _DeltaTime, const StateInfo& _Info);
	void DialougeCloseEnd(const StateInfo& _Info);
};

