#pragma once
#include "GlobalContentsValue.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>
// 관리해야하는 데이터 :		HUD 관련(가면, 영혼), 부적, 맵 해금, 아이템
//							플레이어 - 현재 상태, 비네팅 상태?

// 현재는 레벨마다 생성되는 클래스의 변수에 넣어주고 있지만
// 애초에 변수를 선언하지 않고 데이터 클래스에서 빼오는게 효율적일거같다.

enum class LevelList
{
	KingsPassLevel1,
	KingsPassLevel2,
	KingsPassLevel3,
	KingsPassLevel4,

	CrossroadsLevel1,
	CrossroadsLevel2,
	CrossroadsLevel3,
	CrossroadsLevel4,
	CrossroadsLevel5,
	CrossroadsLevel6,
	CrossroadsLevel7,

	DirtmouthLevel1,
	DirtmouthLevel2,
	DirtmouthLevel3,

	GrimmDirtmouthLevel1,
	GrimmDirtmouthLevel2,
	GrimmDirtmouthLevel3,

	GrimmmLevel,


	SlyShopLevel,
	MapShopLevel,

	DirtmouthStationLevel,

	KingsPassGrimmOpenLevel

};

struct KnightItemData
{
	bool isHas_;
	int ItemCount_;
	ITEM_LIST Item_;
};

struct KnightCharmData
{
	//bool isHas_;
	CHARM_SLOT Charm_;
};


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
	int AllMask_;							//내가 가질 수 있는 최대 가면
	int CurMask_;							//나의 현재 가면
	int CurSoul_;							//현재 영혼
	int CharmNotches_;						//가능한 부적 칸 수
	int UsingCharmNotches_;					// 현재 사용중인 부적 칸 수

	int HitDamage_;							// 공격 데미지

	int MaskPieceCount_;					// 가면 조각 갯수

	std::vector<KnightCharmData> CharmList_;
	std::vector<KnightItemData> ItemList_;

	bool isKnihgt_;							// 플레이어가 있다. : 필요없는거같음 후에 삭제
	bool isHUD_;							// 허드가 있다. 게임 첫 시작에만 애니메이션이 나오기 위함

	float MaxSkew;							// unit is degrees angle.
	float MaxSway;							// unit is pixels in screen space.
	float SeedShiftingFactor;

	bool isOverlayflag_;					//오버레이 플러그
	bool SavedPaletteInit_;					//팔레트...인데 사용 고민중

	float4 OverlayColor_;					//오버레이 컬러

	float4 MainLightMulColor_;				//메인 라이트 컬러
	float4 MainLightPlusColor_;				//메인 라이트 플러스 컬러

	float4 SlibingLightMulColor_;
	float4 SlibingLightPlusColor_;

	float4 DounutLightMulColor_;
	float4 DounutLightPlusColor_;

	BlendMode MainLighBlend_;
	BlendMode SlibingLighBlend_;
	BlendMode DounutLighBlend_;

	std::string PrevLevel_;
	std::string CurrentLevel_;
	std::vector<std::string> AllLevelNameList_;

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
	bool isCameraGUI_;	//카메라 GUi가 있다
	bool isEffectGUI_;
	bool isRevive_;		//플레이어가 다시 태어난당		: 비네팅에 사용중
	bool isBossBattle_;
	bool isIntroFallEvent_;
	bool isUseSoul_;
	bool isDeathLevelChange_;

	bool isGrimmOpen_;

	bool isAddNewMask_;	// 가면 해금됐다.

	float4 KnightPosition_;
	//float4 CurDir_;


	//std::map<int, std::string> KnihgtItemList_;

public:

	//================================
	//    아이템, 부적
	//================================

	bool FindKnightItemList(ITEM_LIST _Item)
	{
		for (std::vector<KnightItemData>::iterator It = ItemList_.begin(); It != ItemList_.end(); ++It)
		{
			if (It->Item_ == _Item)
			{
				return true;
			}
		}

		return false;
	}

	bool FindKnightCharmList(CHARM_SLOT _Charm)
	{
		for (std::vector<KnightCharmData>::iterator It = CharmList_.begin(); It != CharmList_.end(); ++It)
		{
			if (It->Charm_ == _Charm)
			{
				return true;
			}
		}

		return false;
	}

	void PushKnihgtItemList(ITEM_LIST _Item)
	{
		KnightItemData ItemData;
		ItemData.Item_ = _Item;
		//ItemData.ItemCount_ ;

		ItemList_.push_back(ItemData);
	}

	void PushKnihgtCharList(CHARM_SLOT _Charm)
	{
		KnightCharmData CharmData;
		CharmData.Charm_ = _Charm;

		CharmList_.push_back(CharmData);
	}


	//================================
	//    Getter
	//================================

	std::vector<KnightItemData> GetKnightItemData()
	{
		return ItemList_;
	}
	bool GetisAddNewMask() const
	{
		return isAddNewMask_;
	}

	int GetMaskPieceCount() const
	{
		return MaskPieceCount_;
	}

	bool GetisGrimmOpen() const
	{
		return isGrimmOpen_;
	}

	bool GetisDeathLevelChange() const
	{
		return isDeathLevelChange_;
	}

	bool GetisisUseSoul() const
	{
		return isUseSoul_;
	}

	bool GetisIntroFallEvent()
	{
		return isIntroFallEvent_;
	}

	bool GetisBossBattle() const
	{
		return isBossBattle_;
	}

	int GetHitDamage() const
	{
		return HitDamage_;
	}

	std::string& GetPreLevel()
	{
		return PrevLevel_;
	}

	std::string& GetCurrentLevel()
	{
		return CurrentLevel_;
	}

	BlendMode GetMainLightBlend()
	{
		return MainLighBlend_;
	}

	BlendMode GetSlibingLightBlend()
	{
		return SlibingLighBlend_;
	}

	BlendMode GetDounutLightBlend()
	{
		return DounutLighBlend_;
	}


	float4 GetKnihgtMainLightMulColor()
	{
		return MainLightMulColor_;
	}

	float4 GetKnihgtMainLightPlusColor()
	{
		return MainLightPlusColor_;
	}

	float4 GetKnihgtSlibingLightMulColor()
	{
		return SlibingLightMulColor_;
	}

	float4 GetKnihgtSlibingLightPlusColor()
	{
		return SlibingLightPlusColor_;
	}

	float4 GetKnihgtDounutLightMulColor()
	{
		return DounutLightMulColor_;
	}

	float4 GetKnihgtDounutLightPlusColor()
	{
		return DounutLightPlusColor_;
	}

	bool GetSavedPaletteInit()
	{
		return SavedPaletteInit_;
	}

	bool GetOverlayFlag()const
	{
		return isOverlayflag_;
	}

	float4 GetOverlayColor()
	{
		return OverlayColor_;
	}

	float GetMaxSkew() const
	{
		return MaxSkew;
	}


	float GetMaxSway() const
	{
		return MaxSway;
	}


	float GetSeedshiftingFactor() const
	{
		return SeedShiftingFactor;
	}


	bool GetisEffectGUI()
	{
		return isEffectGUI_;
	}

	bool GetisRevive()
	{
		return isRevive_;
	}


	bool GetisCameraGUI()
	{
		return isCameraGUI_;
	}

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
	void AddMaskPieceCount()
	{
		++MaskPieceCount_;
		if (MaskPieceCount_ > 4)
		{
			MaskPieceCount_ = 0;
		}
	}

	void SetisAddNewMask(bool _b)
	{
		isAddNewMask_ = _b;
	}

	void SetMaskPieceCount(int _i)
	{
		MaskPieceCount_ = _i;
	}

	void SetisGrimmOpen(bool _b)
	{
		isGrimmOpen_ = _b;
	}

	void SetisDeathLevelChange(bool _b)
	{
		isDeathLevelChange_ = _b;
	}

	void SetisUseSoul(bool _b)
	{
		isUseSoul_ = _b;
	}

	void SetisIntroFallEvent(bool _b)
	{
		isIntroFallEvent_ = _b;
	}

	void SetisBossBattle(bool _b)
	{
		isBossBattle_ = _b;
	}

	void SetHitDamage(int _i)
	{
		HitDamage_ = _i;
	}


	void PushLevelNameList(std::string _Name)
	{
		AllLevelNameList_.push_back(_Name);
	}


	void SetCurrentLevel(std::string _Level)
	{
		PrevLevel_ = CurrentLevel_;

		std::string UpperName = GameEngineString::ToUpperReturn(_Level);

		CurrentLevel_ = UpperName;
	}

	void SetMainLightBlend(BlendMode _Mode)
	{
		MainLighBlend_ = _Mode;
	}

	void SetSlibingLightBlend(BlendMode _Mode)
	{
		SlibingLighBlend_ = _Mode;
	}

	void SetDounutLightBlend(BlendMode _Mode)
	{
		DounutLighBlend_ = _Mode;
	}

	void SetKnihgtMainLightMulColor(float4 _f4)
	{
		MainLightMulColor_ = _f4;
	}

	void SetKnihgtMainLightPlusColor(float4 _f4)
	{
		MainLightPlusColor_ = _f4;
	}

	void SetKnihgtSlibingLightMulColor(float4 _f4)
	{
		SlibingLightMulColor_ = _f4;
	}

	void SetKnihgtSlibingLightPlusColor(float4 _f4)
	{
		SlibingLightPlusColor_ = _f4;
	}

	void SetKnihgtDounutLightMulColor(float4 _f4)
	{
		DounutLightMulColor_ = _f4;
	}

	void SetKnihgtDounutLightPlusColor(float4 _f4)
	{
		DounutLightPlusColor_ = _f4;
	}


	void SetSavedPaletteInit(bool _b)
	{
		SlibingLightMulColor_ = _b;
	}

	void SetOverlayflag(bool _b)
	{
		isOverlayflag_ = _b;
	}

	void SetOverlayColor(float4 _f)
	{
		OverlayColor_ = _f;
	}


	void SetMaxSkew(float _f)
	{
		MaxSkew = _f;
	}


	void SetMaxSway(float _f)
	{
		MaxSway = _f;
	}


	void SetSeedshiftingFactor(float _f) 
	{
		SeedShiftingFactor = _f;
	}



	void SetisRevive(bool _b)
	{
		isRevive_ = _b;
	}

	void SetisEffectGUI(bool _b)
	{
		isEffectGUI_ = _b;
	}

	void SetisCameraGUI(bool _b)
	{
		isCameraGUI_ = _b;
	}

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

	void SetAddAllMask()
	{
		++AllMask_;
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

