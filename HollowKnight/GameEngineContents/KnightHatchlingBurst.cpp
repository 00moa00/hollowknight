#include "PreCompile.h"
#include "KnightHatchlingBurst.h"

KnightHatchlingBurst::KnightHatchlingBurst() 
{
}

KnightHatchlingBurst::~KnightHatchlingBurst() 
{
}

void KnightHatchlingBurst::Start()
{
	CreateRendererComponent("Knight Hatchling Cln_burst0000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 247.f * 3.f, 234.f * 3.f });
	GetRenderer()->GetTransform().SetLocalPosition({-12.f, ((234.f * 3.f)/5) - 10.f});
	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Knight Hatchling Cln_burst0000-Sheet.png", 0, 5, 0.050f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 6; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		GetRenderer()->CreateFrameAnimationCutTexture("BACK_ANIMATION", FrameAnimation_DESC("stun_impact_effect0000-Sheet.png", BackAni, 0.060f, false));
	}


	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Knight Hatchling Cln_burst0000-Sheet.png", 5, 5, 0.010f, false));


	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			//GetRenderer()->ScaleToCutTexture(0);
			GetRenderer()->GetTransform().SetLocalScale({ 270.f * 3.f, 270.f * 3.f });

			GetRenderer()->ChangeFrameAnimation("BACK_ANIMATION");
		});

	GetRenderer()->AnimationBindEnd("BACK_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});


	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

	Off();
}

void KnightHatchlingBurst::Update(float _DeltaTime)
{
}

void KnightHatchlingBurst::EffectOn()
{
	On();
	GetRenderer()->GetTransform().SetLocalScale({ 247.f * 3.f, 234.f * 3.f });

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
}
