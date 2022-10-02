#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsFontRenderer.h"

// Ό³Έν :
class DialogueSet : public GameEngineActor
{
public:
	// constrcuter destructer
	DialogueSet();
	~DialogueSet();

	// delete Function
	DialogueSet(const DialogueSet& _Other) = delete;
	DialogueSet(DialogueSet&& _Other) noexcept = delete;
	DialogueSet& operator=(const DialogueSet& _Other) = delete;
	DialogueSet& operator=(DialogueSet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isDialougueFull_;

	GameEngineUIRenderer* DialogueTop_;
	GameEngineUIRenderer* DialogueBottom_;
	GameEngineUIRenderer* DialogueBack_;

	GameEngineUIRenderer* NextArrow_;

private:

	int CurrentDialoguePage_;
	std::vector<ContentsFontRenderer*> DialogueList_;

public:
	//================================
	//     Getter
	//================================
	bool GetDialougueFull()
	{
		return isDialougueFull_;
	}


	//================================
	//    Setter
	//================================
	void SetDialogueOn()
	{
		this->On();
		DialogueBottom_->ChangeFrameAnimation("BOTTOM_APPEAR_ANIMATION");
		DialogueTop_->ChangeFrameAnimation("TOP_APPEAR_ANIMATION");
		DialogueList_.front()->GetFontRenderer()->On();
		DialogueList_.front()->FontOn();
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

		this->Off();
	}

	void PushDialogue(std::string _Dialougue)
	{
		DialogueList_.push_back(GetLevel()->CreateActor<ContentsFontRenderer>());
		DialogueList_.back()->CreateFontRenderer(
			_Dialougue
			, 36
			, {GameEngineWindow::GetInst()->GetScale().hx() - 430, GameEngineWindow::GetInst()->GetScale().hy()-300 },
			true,
			true,
			31
			);

		//DialogueList_.back()->Ge SetParent(this);
		DialogueList_.back()->Off();
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


			if (CurrentDialoguePage_ == DialogueList_.size() - 1)
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

};

