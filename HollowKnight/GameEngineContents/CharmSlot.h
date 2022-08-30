#pragma once
#include "SettingUIMaster.h"
#include "Charm.h"

// 해당 슬롯에 내가 가지고 있는 부적인지, 그리고 장착하고 있는 부적인지 상태를 알 수 있어야한다
// 부적위치는 늘 고정(바뀔 일이 없다.)

// 포인터 엑터는 해당 클래스이다(슬롯)이다.

// 슬롯은 부적에 대한 정보와, 부적을 가지고 있다.

// 해당 게임은 부적의 종류가 바뀌어도(강화) 갯수와 위치는 고정이기때문에 유동적으로 짤 이유가 없다

struct CharmState 
{
public :
	int SlotNum_;		//슬롯 번호
	int SlotCount_;		//슬롯 몇개가 필요한지
	bool KnihgistHas_;	//나이트가 가지고 있는지
	bool isUsing_;		//사용 하고 있는지

	bool isEquippedSlot_; //장착 슬롯인지
	bool isEquippedSlotUsing_; //장착 슬롯이 사용중인지

	int UsingSlotNum_; //장착한 슬롯의 번호


	std::string CharmFilePath_; // 파일 패스
	std::string CharmName_;
};

// 설명 :
class CharmSlot : public SettingUIMaster
{
public:
	// constrcuter destructer
	CharmSlot();
	~CharmSlot();

	// delete Function
	CharmSlot(const CharmSlot& _Other) = delete;
	CharmSlot(CharmSlot&& _Other) noexcept = delete;
	CharmSlot& operator=(const CharmSlot& _Other) = delete;
	CharmSlot& operator=(CharmSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	//bool
	
	Charm* Charm_;
	CharmState CharmState_;

public:

	void CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState, CHARM_SLOT _slot);
	void CreateEquippedCharmSlot(CharmState _CharmState);
	void CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath);

	void CharmSetMoveLeft();



	//================================
	//    Getter 
	//================================

	Charm* GetCharm()
	{
		return Charm_;
	}

	int GetSlotNum()
	{
		return CharmState_.SlotNum_;
	}

	int GetSlotCount()
	{
		return CharmState_.SlotCount_;
	}

	bool GetKnightHas()
	{
		return CharmState_.KnihgistHas_;
	}

	bool GetisUsing()
	{
		return CharmState_.isUsing_;
	}

	bool GetisEquippedSlot()
	{
		return CharmState_.isEquippedSlot_;
	}
	bool GetisEquippedSlotUsing()
	{
		return  CharmState_.isEquippedSlotUsing_;
	}


	int GetUsingSlotNum()
	{
		return  CharmState_.UsingSlotNum_;
	}

	CharmState& GetCharmState()
	{
		return CharmState_;
	}

	std::string& GetFilePath()
	{
		return CharmState_.CharmFilePath_;
	}

	std::string& GetCharmName()
	{
		return CharmState_.CharmName_;
	}

	//================================
	//    Setter 
	//================================

	void SetCharmisHas(bool _b)
	{
		CharmState_.KnihgistHas_ = _b;
		
		if (CharmState_.KnihgistHas_ == true)
		{
			Charm_->GetRenderer()->On();
			this->GetRenderer()->Off();
		}

		else
		{
			Charm_->GetRenderer()->Off();
			this->GetRenderer()->On();
		}
	}

	void SetisEquippedSlotUsing(bool _b)
	{
		CharmState_.isEquippedSlotUsing_ = _b;
	}
	

	void SetisUsing(bool _b)
	{
		CharmState_.isUsing_ = _b;
	}

	void SetUsingSlotNum(int _i)
	{
		CharmState_.UsingSlotNum_ = _i;
	}
	

};

