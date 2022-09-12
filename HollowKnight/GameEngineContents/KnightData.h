#pragma once

// 관리해야하는 데이터 : 플레이어 체력, 영혼레벨, 부적, 맵 해금, 아이템
// 현재는 레벨마다 생성되는 클래스의 변수에 넣어주고 있지만
// 애초에 변수를 선언하지 않고 데이터 클래스에서 빼오는게 효율적일거같다

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
	//================================
	//    레벨이동 데이터
	//================================
	int AllMask_;			//내가 가질 수 있는 최대 가면
	int CurMask_;			//나의 현재 가면
	int CurSoul_;			//현재 영혼
	int CharmNotches_;		//가능한 부적 칸 수
	int UsingCharmNotches_; // 현재 사용중인 부적 칸 수

	bool isKnihgt_;			// 플레이어가 있다. : 필요없는거같음 후에 삭제
	bool isHUD_;			// 허드가 있다. 게임 첫 시작에만 애니메이션이 나오기 위함


	//================================
	//    플래그
	//================================
	bool isRefill_;		//가면 -> 회복됐다
	bool isNewMask_;	//가면 -> 새로 생겼땅
	bool isBreak_;		// 가면 -> 깨졌다
	bool isDeath_;		//죽었다
	bool isShadow_;		// 죽었고 이미 그림자가 있다
	bool isGrowSoul_;	// 몬스터를 쳤을때 영혼이 찬다
	bool isSitting_;	// 의자에 앉아있다.
	bool isSetting_;	//세팅 페이지 열었당

	float4 KnightPosition_;


	std::map<int, std::string> KnihgtItemList_;

public:

	//================================
	//    Getter
	//================================

	int GetCurSoul()
	{
		return CurSoul_;
	}

	bool GetisHUD()
	{
		return isHUD_;
	}

	bool GetisKnight()
	{
		return isKnihgt_;
	}

	int GetUsingCharmNotches()
	{
		return UsingCharmNotches_;
	}

	bool GetisSetting()
	{
		return isSetting_;
	}

	bool GetisShadow()
	{
		return isShadow_;
	}

	bool GetisSitting()
	{
		return isSitting_;
	}

	int GetAllMask()
	{
		return AllMask_;
	}

	int GetCurMask()
	{
		return CurMask_;
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

	bool GetisDeath()
	{
		return isDeath_;
	}

	bool GetisGrowSoul()
	{
		return isGrowSoul_;
	}

	int GetCharmNotches()
	{
		return CharmNotches_;
	}

	float4 GetKnightPosition()
	{
		return KnightPosition_;
	}


	//================================
	//    Setter
	//================================
	void SetisHUD(bool _b)
	{
		isHUD_ = _b;
	}

	void SetisKnight(bool _b)
	{
		isKnihgt_ = _b;
	}

	//부적을 장착한다.
	bool SubUsingCharmNotches(int _i)
	{
		if (CharmNotches_ - UsingCharmNotches_ >= _i)
		{
			UsingCharmNotches_ += _i;
			return true;
		}

		return false;
	}

	// 부적을 뺸다
	void AddUsingCharmNotches(int _i)
	{

		if (UsingCharmNotches_ >= 0)
		{
			UsingCharmNotches_ -= _i;

		}
	}

	void SetKnightPosition(float4 _Pos)
	{
		KnightPosition_ = _Pos;
	}


	void SetisSetting(bool _b)
	{
		isSetting_ = _b;
	}

	void SetisShadow(bool _b)
	{
		isShadow_ = _b;
	}

	void SetisSitting(bool _b)
	{
		isSitting_ = _b;
	}

	void SetAllMask(int _i)
	{
		AllMask_ = _i;
	}

	void SetCurMask(int _i)
	{
		CurMask_ = _i;
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

	void SetisDeath(bool _b)
	{
		isDeath_ = _b;
	}

	void SetisSoulGrow(bool _b)
	{
		isGrowSoul_ = _b;
	}

	void SetCurSoul(int _i)
	{
		CurSoul_ = _i;
	}

};

