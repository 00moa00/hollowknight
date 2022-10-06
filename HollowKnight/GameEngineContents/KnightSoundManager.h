#pragma once
#include<GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class KnightSoundManager
{
private:
	static KnightSoundManager* Inst_;

public:
	static KnightSoundManager* GetInst()
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
	KnightSoundManager();
	~KnightSoundManager();

	// delete Function
	KnightSoundManager(const KnightSoundManager& _Other) = delete;
	KnightSoundManager(KnightSoundManager&& _Other) noexcept = delete;
	KnightSoundManager& operator=(const KnightSoundManager& _Other) = delete;
	KnightSoundManager& operator=(KnightSoundManager&& _Other) noexcept = delete;

protected:

private:
	GameEngineSoundPlayer BgmPlayer;
	GameEngineSoundPlayer KnightFallBgmPlayer;
	GameEngineSoundPlayer KnightFootStepBgmPlayer;
public:
	void BgmOn(std::string _file, int _LoopCount);
	void BgmOff();
	void BgmSound(float _Power);

	void KnightFallBgmOn(std::string _file, int _LoopCount);
	void KnightFallBgmOff();
	void KnightFallBgmSound(float _Power);

	void KnightFootStepBgmOn(std::string _file, int _LoopCount);
	void KnightFootStepBgmOff();
	void KnightFootStepBgmSound(float _Power);

};

