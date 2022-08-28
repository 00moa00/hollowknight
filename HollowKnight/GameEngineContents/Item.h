#pragma once
#include "MasterUI.h"
#include"GlobalContentsValue.h"





// 설명 : 아이템 슬롯번호 0~9 스펠 아이템. 10~ 29 일반 아이템. 30~ 33 판매 아이템
// 스펠 아이템과, 판매 아이템은 위치 고정
// 일반 아이템을 얻으면 레벨의 ItemSlot을 돌아서 비어있으면 그자리에 넣는다 
// 일반 아이템 중에는 소비가 가능한 아이템이 있는데
// 갯수가 0이 되면 해당 아이템의 뒤에 있는 포인터 액터의 key값을 댕긴다.
// 댕기기 전에는 해당 아이템의 맵을 삭제먼저 한다.

class Item : public MasterUI
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void CreateItem(std::string _Name, ITEM_LIST _Item);



};

