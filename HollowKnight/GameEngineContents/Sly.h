#pragma once
#include "MasterNPC.h"
#include "Shop.h"

// Ό³Έν :
class Sly : public MasterNPC
{
public:
	// constrcuter destructer
	Sly();
	~Sly();

	// delete Function
	Sly(const Sly& _Other) = delete;
	Sly(Sly&& _Other) noexcept = delete;
	Sly& operator=(const Sly& _Other) = delete;
	Sly& operator=(Sly&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CheckDirToKnight() override;

public:
	void SetisShop(bool b) override
	{
		if (b == true)
		{
			OpenShop_ = true;
			MapShop_->On();
			MapShop_->SetShopPopup();
			SlyManager_.ChangeState("SHOP_OPEN");
		}

		else if (b == false)
		{
			OpenShop_ = false;

			MapShop_->SetShopPopDown();

		}
	}

private:
	bool OpenShop_;

	int ShopIndexCount_;

	float4 PrevDir_;

	Shop* MapShop_;

	GameEngineStateManager SlyManager_;


private:

	//================================
	//    Bind State
	//================================

	void SlyIdleStart(const StateInfo& _Info);
	void SlyIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlyIdleEnd(const StateInfo& _Info);

	void SlyChangeDirStart(const StateInfo& _Info);
	void SlyChangeDirUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlyChangeDirEnd(const StateInfo& _Info);

	void SlyShopOpenStart(const StateInfo& _Info);
	void SlyShopOpenUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlyShopOpenEnd(const StateInfo& _Info);

	void SlyTalkingStart(const StateInfo& _Info);
	void SlyTalkingUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlyTalkingEnd(const StateInfo& _Info);

};

