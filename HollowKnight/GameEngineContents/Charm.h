#pragma once
#include "MasterUI.h"
struct RendererMove
{
	float4 StartDir_;
	float4 EndDir_;
};


// 설명 :
class Charm : public MasterUI
{
public:
	// constrcuter destructer
	Charm();
	~Charm();

	// delete Function
	Charm(const Charm& _Other) = delete;
	Charm(Charm&& _Other) noexcept = delete;
	Charm& operator=(const Charm& _Other) = delete;
	Charm& operator=(Charm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool isCharmSlotWait_;			// 카피용 플러그

	bool isRendererDeathFlag_;
	bool isDeathFlag_;

	bool isMoveEnd_;


	std::string CharmName_;
	RendererMove RendererMove_;

	GameEngineStateManager CharmManager_;

	Charm* CharmPointer_;

public:
	
	bool GetMoveEnd()
	{
		return isMoveEnd_;
	}


	void SetRenderMove(float4 _StartDir, float4 _EndDir, bool _isRenderDeathFlag = false, bool _isDeathFlag = false)
	{

		RendererMove_.StartDir_ = _StartDir;
		RendererMove_.EndDir_ = _EndDir;
		isRendererDeathFlag_ = _isRenderDeathFlag;
		isDeathFlag_ = _isDeathFlag;

		CharmManager_.ChangeState("MOVE");
	}

	void SetCharmPointer(Charm* _OtherCharm)
	{
		CharmPointer_ = _OtherCharm;
	}
	
	
	
	void CreateCharm(std::string _Name, std::string _FilePath, float4 Scale);


	//=========================================
	//    SettingPointerCharmPageManager
	//=========================================
	void PointerCharmIdleStart(const StateInfo& _Info);
	void PointerCharmIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmIdleEnd(const StateInfo& _Info);

	void PointerCharmMoveStart(const StateInfo& _Info);
	void PointerCharmMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmMoveEnd(const StateInfo& _Info);

};

