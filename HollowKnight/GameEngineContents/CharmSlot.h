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
	int SlotCount_;		//슬롯 몇개를 사용하고 있는지
	bool KnihgistHas_;	//나이트가 가지고 있는지
	bool isUsing_;		//사용 하고 있는지
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

	CharmState& GetCharmState()
	{
		return CharmState_;
	}
	

};

