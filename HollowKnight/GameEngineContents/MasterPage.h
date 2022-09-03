#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GlobalContentsValue.h"

class GameEngineUIRenderer;
// 설명 :
class MasterPage : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterPage();
	~MasterPage();

	// delete Function
	MasterPage(const MasterPage& _Other) = delete;
	MasterPage(MasterPage&& _Other) noexcept = delete;
	MasterPage& operator=(const MasterPage& _Other) = delete;
	MasterPage& operator=(MasterPage&& _Other) noexcept = delete;

protected:
	std::string PageName_;

	CURRENT_PAGE_INDEX CurrentPage_;
	PAGE_TYPE PageType_;

public:
	virtual void AllOff();
	virtual void AllOn();


public:
	//================================
	//     Getter
	//================================

	PAGE_TYPE GetPageType()
	{
		return PageType_;
	}

	// 현재 인데스 반환
	CURRENT_PAGE_INDEX GetCurrentPage()
	{
		return CurrentPage_;
	}

	// 현재 인덱스가 0인지
	bool isCurrentPage()
	{
		if (CurrentPage_ == CURRENT_PAGE_INDEX::CurrentPage)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string& GetPageName()
	{
		return PageName_;
	}

	//================================
	//    Setter
	//================================
	void SetCurrentPage(CURRENT_PAGE_INDEX _PageIndex)
	{
		CurrentPage_ = _PageIndex;
	}
	
	void SetPageType(PAGE_TYPE _PageType)
	{
		PageType_ = _PageType;
	}

	void SetPageName(std::string _Name)
	{
		PageName_ = _Name;
	}

};

