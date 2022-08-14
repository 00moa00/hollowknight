#pragma once

// ���� :
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

	int Mask_;

	bool isRefill_;
	bool isNewMask_;
	bool isBreak_;

public:

	//================================
	//    Getter
	//================================

	int GetMask()
	{
		return Mask_;
	}

	bool GetisRefill()
	{
		return isRefill_;
	}

	bool GetisNewMask()
	{
		return isNewMask_;
	}

	bool GetisBreak()
	{
		return isBreak_;
	}

	//================================
	//    Setter
	//================================

	void SetMask(int _i)
	{
		Mask_ = _i;
	}

	void SetisRefill(bool _b)
	{
		isRefill_ = _b;
	}

	void SetisNewMask(bool _b)
	{
		isNewMask_ = _b;
	}

	void SetisBreak(bool _b)
	{
		isBreak_ = _b;
	}


};

