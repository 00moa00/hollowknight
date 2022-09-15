#include "PreCompile.h"
#include "MasterEffect.h"

MasterEffect::MasterEffect() 
	:
	MainRenderer_(nullptr),
	MainCollision_(nullptr),

	LightMulColor_(),
	LightPlusColor_(),

	BlendMode_(BlendMode::MAX),

	Direction_(),
	CollisionSize_()
{
}

MasterEffect::~MasterEffect() 
{
}

void MasterEffect::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
	MainRenderer_->GetTransform().SetWorldPosition({ 0, _LocalScale.y / 2 });
}

void MasterEffect::CreateRendererComponent(float4 _LocalScale, std::string _FileName)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
	MainRenderer_->GetTransform().SetWorldPosition({ 0, _LocalScale.y / 2 });
}

void MasterEffect::CreateRendererComponent(std::string _FileName)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName);
	MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
	MainRenderer_->GetTransform().SetWorldPosition({ 0, MainRenderer_->GetCurTexture()->GetScale().y / 2 });
}

void MasterEffect::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	MainCollision_ = CreateComponent<GameEngineCollision>();
	//MainCollision_ ->Push
	MainCollision_->GetTransform().SetLocalScale(_LocalScale);
	MainCollision_->ChangeOrder(_Order);
}


void MasterEffect::SetBlendMode(BlendMode _Mode)
{
	switch (_Mode)
	{
	case BlendMode::Alpha:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend");

		break;
	case BlendMode::Overlay:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");

		break;
	case BlendMode::Lighten:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("LightenBlend");

		break;
	case BlendMode::Multply:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("MultplyBlend");

		break;
	case BlendMode::Add:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");

		break;

	case BlendMode::Addition:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("Addition");

		break;
	case BlendMode::Darken:
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("DarkenBlend");

		break;
	default:
		break;
	}

	BlendMode_ = _Mode;
}


void MasterEffect::SetMulColor(float4 _MulColor)
{
	LightMulColor_ = _MulColor;
	MainRenderer_->GetPixelData().MulColor = _MulColor;
}

void MasterEffect::SetPlusColor(float4 _PlusColor)
{
	LightPlusColor_ = _PlusColor;
	MainRenderer_->GetPixelData().PlusColor.x = _PlusColor.x;
	MainRenderer_->GetPixelData().PlusColor.y = _PlusColor.y;
	MainRenderer_->GetPixelData().PlusColor.z = _PlusColor.z;




}

