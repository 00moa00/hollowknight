#include "PreCompile.h"
#include "GrimmCrowds.h"

GrimmCrowds::GrimmCrowds() 
{
}

GrimmCrowds::~GrimmCrowds() 
{
}

void GrimmCrowds::Start()
{
	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 5300,-350 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetParent(this);
	}
	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 5200,-470 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetParent(this);
	}




	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 5650,-320 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetParent(this);
	}
	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 5700,-420 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetParent(this);
	}

	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 4550,-320 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetScaleNegativeX();

		GrimmCrowd_->SetParent(this);
	}

	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 4100,-320 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetScaleNegativeX();

		GrimmCrowd_->SetParent(this);
	}

	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 4750,-450 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetScaleNegativeX();

		GrimmCrowd_->SetParent(this);
	}



	{
		GrimmCrowd* GrimmCrowd_ = GetLevel()->CreateActor<GrimmCrowd>();
		GrimmCrowd_->GetTransform().SetWorldPosition({ 4200,-450 , static_cast<float>(Z_ORDER::Back_Back_Object) });
		GrimmCrowd_->SetScaleNegativeX();
		GrimmCrowd_->SetParent(this);
	}
}

