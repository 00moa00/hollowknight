#pragma once
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class KnightShadowData
{
private:
	static KnightShadowData* Inst_;

public:
	static KnightShadowData* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	// constrcuter destructer
	KnightShadowData();
	~KnightShadowData();

	// delete Function
	KnightShadowData(const KnightShadowData& _Other) = delete;
	KnightShadowData(KnightShadowData&& _Other) noexcept = delete;
	KnightShadowData& operator=(const KnightShadowData& _Other) = delete;
	KnightShadowData& operator=(KnightShadowData&& _Other) noexcept = delete;

protected:

private:
	float4 Position_;

};

