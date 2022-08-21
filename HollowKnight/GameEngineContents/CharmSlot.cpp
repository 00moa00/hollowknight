#include "PreCompile.h"
#include "CharmSlot.h"

CharmSlot::CharmSlot() 
{
}

CharmSlot::~CharmSlot() 
{
}

void CharmSlot::Start()
{
}

void CharmSlot::Update(float _Deltatime)
{
}

void CharmSlot::CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState)
{
	// 何利 浇吩
	CreateRendererComponent({68,68,1}, "charm_backboard.png");

	//何利 惑怕
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.SlotCount_ = _CharmState.SlotCount_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;

	//何利
	Charm_ = GetLevel()->CreateActor<Charm>();
	Charm_->CreateCharm(_SlotName, _CharmFilePath, {142, 134, 1});
	Charm_->SetParent(this);
	//GetRenderer()->SetParent(this);

}
