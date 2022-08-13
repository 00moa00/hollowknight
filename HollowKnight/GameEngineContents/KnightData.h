#pragma once

// Ό³Έν :
class KnightData
{
private:
	static KnightData* Inst_;

public:
	static KnightData* GetInst()
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
	KnightData();
	~KnightData();

	// delete Function
	KnightData(const KnightData& _Other) = delete;
	KnightData(KnightData&& _Other) noexcept = delete;
	KnightData& operator=(const KnightData& _Other) = delete;
	KnightData& operator=(KnightData&& _Other) noexcept = delete;

private:
	bool isRefill_;

public:
	bool GetisRefill()
	{
		return isRefill_;
	}

	void SetisRefill(bool _b)
	{
		isRefill_ = _b;
	}

};

