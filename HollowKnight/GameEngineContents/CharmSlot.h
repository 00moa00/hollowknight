#pragma once
#include "SettingUIMaster.h"
#include "Charm.h"

// 해당 슬롯에 내가 가지고 있는 부적인지, 그리고 장착하고 있는 부적인지 상태를 알 수 있어야한다
// 부적위치는 고정이니까 글로벌벨류에서 우선 ㅅ[ㅔ팅

// 포인터 엑터는 슬롯이다.

// 슬롯은 이미 부적에 대한 정보와, 부적을 가지고 있음.

struct CharmState 
{
public :
	int SlotNum_;		//슬롯 번호
	int SlotCount_;		//슬롯 몇개가 필요한지
	bool KnihgistHas_;	//나이트가 가지고 있는지
	bool isUsing_;		//사용 하고 있는지
	bool isEquipped_; //장착 슬롯인지
	bool isEquippedUsing_; //장착 슬롯 사용중인지
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

	
	Charm* Charm_;
	CharmState CharmState_;

public:

	void CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState, CHARM_SLOT _slot);
	void CreateEquippedCharmSlot(CharmState _CharmState);
	void CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath);


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

	bool GetisEquipped()
	{
		return CharmState_.isEquipped_;
	}
	bool GetisEquippedUsing()
	{
		return  CharmState_.isEquippedUsing_;
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

	void SetisEquippedUsing(bool _b)
	{
		CharmState_.isEquippedUsing_ = _b;
	}
	

	void SetisUsing(bool _b)
	{
		CharmState_.isUsing_ = _b;
	}
	

};

