#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
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
	//레벨에서 생성해? 


private:
	float4 ShadowPosition_;
	float4 KnightPosition_;

	bool isShadowDepart_;

public:
	//================================
	//    Getter
	//================================
	float4 GetShadowPosition()
	{
		return ShadowPosition_;
	}

	float4 GetKnightPosition()
	{
		return KnightPosition_;
	}

	bool GetisShadowDepart()
	{
		return isShadowDepart_;
	}

	//================================
	//    Setter
	//================================

	void SetShadowPosition(float4 _Pos)
	{
		ShadowPosition_ = _Pos;
	}

	void SetKnightPosition(float4 _Pos)
	{
		KnightPosition_ = _Pos;
	}

	void SetisShadowDepart(bool _b)
	{
		isShadowDepart_ = _b;
	}

};

