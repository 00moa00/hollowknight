#include "PreCompile.h"
#include "SettingUIMaster.h"

SettingUIMaster::SettingUIMaster() 
{
}

SettingUIMaster::~SettingUIMaster() 
{
}

void SettingUIMaster::SelectSettingPointer()
{
}

void SettingUIMaster::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture(_FileName, _Index);
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
	//Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
}

void SettingUIMaster::CreateRendererComponent(float4 _LocalScale, std::string _FileName)
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture(_FileName);
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
}


void SettingUIMaster::PixLocalNegativeY()
{
	Renderer_->GetTransform().SetLocalScale({ GetTransform().GetLocalScale().x, abs(GetTransform().GetLocalScale().y), 1 });
	if (0.0f > Renderer_->GetTransform().GetLocalScale().y)
	{
		return;
	}

	Renderer_->GetTransform().SetLocalScale({ GetTransform().GetLocalScale().x, -(GetTransform().GetLocalScale().y), 1 });

}

void SettingUIMaster::PixLocalPositiveY()
{

	if (0.0f < Renderer_->GetTransform().GetLocalScale().y)
	{
		return;
	}

	// abs 어떤 숫자를 넣으면 무조건 양수(절대값)으로 변경해주는 함수.



}

void SettingUIMaster::ChangeAnimation(std::string _Name)
{
	Renderer_->ChangeFrameAnimation(_Name);

}
