#include "PreCompile.h"
#include "Knight.h"
#include "KnightData.h"
#include "KnightShadow.h"
#include "KnightShadowData.h"
#include "HollowKnightLevel.h"

#include "KnightDoubleJumpEffect.h"

#include "KnightFocusEffect.h"
#include "KnightBurstEffect.h"

#include "FadeIn.h"
#include "FadeOut.h"




void Knight::KnightStillStart(const StateInfo& _Info)
{
	isPossibleDoubleJump_ = true;

	if (_Info.PrevState == "RUN")
	{
		GetRenderer()->ChangeFrameAnimation("RUN_TO_IDLE_ANIMATION");
	}
	else
	{
		if (isLowHealth_ == true)
		{
			GetRenderer()->ChangeFrameAnimation("LOW_HEALTH_ANIMATION");
		}

		else
		{
			GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
		}
	}
}

void Knight::KnightStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	//this->isPixelCheck(_DeltaTime, GetMoveDirection());

	//if (GetisWall() == true)
	//{
 //		isKnihgtStillWall_ = true;
	//}

	//else
	//{
	//	isKnihgtStillWall_ = false;
	//}

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	// ======== Knight VS Tablet ========

	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Tablet, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnihgtVSTabletCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{

		if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
		{
			KnightManager_.ChangeState("SEE");
			return;

		}

	}
	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}


	// ======== Knight VS Monster ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

	// ======== Knight VS Bench ========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Bench, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnihgtVSBenchCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
		&& (GameEngineInput::GetInst()->IsDown("KnightUp") == true))
	{

		KnightManager_.ChangeState("SIT");
		return;
	}


	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	// ======== Knight VS NPC ========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::NPC, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnihgtVSNPCCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}

	// ======== Knight VS POTAL ========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Potal, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSPotalCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}

	// ================================
	// ============ UPDATE ============
	// ================================

	DoubleSlashTimer(_DeltaTime);
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

	if (GameEngineInput::GetInst()->IsFree("KnightJump") == true && isPressJumppingKey_ == true)
	{
		isPressJumppingKey_ = false;
	}

	if (GameEngineInput::GetInst()->IsFree("KnightUp") == true)
	{
		KnightLookUpTimer_ = 0.f; // 타이머 초기화
	}

	if (GameEngineInput::GetInst()->IsFree("KnightDown") == true)
	{
		KnightLookDownTimer_ = 0.f; // 타이머 초기화
	}

	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}


	// ==================================
	// ========== Change State ==========
	// ==================================

	if (true == GameEngineInput::GetInst()->IsDown("KnightFocus"))
	{

	}

	 if (GetisKnightMove() == true && isRunMode_ == false)
	{
		KnightManager_.ChangeState("WALK");
	}

	if (GetisKnightMove() == true && isRunMode_ == true)
	{
		KnightManager_.ChangeState("RUN");
	}

	// 점프
	if (GameEngineInput::GetInst()->IsDown("KnightJump") == true && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
		return;

	}

	// 위 공격
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		KnightManager_.ChangeState("UP_SLASH");
		return;
	}

	// 기본 공격
	if  (GameEngineInput::GetInst()->IsDown("KnightSlash") == true 
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true

		&& isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
		return;

	}

	 //콤보 공격
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true 
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
		return;

	}

	// 아래 바라보기
	if (GameEngineInput::GetInst()->IsPress("KnightDown") == true )
	{
		LookDownTimerAndChangeState(_DeltaTime);
		return;

	}

	// 위 바라보기
	if (GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		LookUpTimerAndChangeState(_DeltaTime);
		return;

	}

	// 맵 보기
	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		//GetRenderer()->ChangeFrameAnimation("MAP_OPEN_ANIMATION");
		KnightManager_.ChangeState("MAP_STILL");
		return;


	}

	// 대쉬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
		return;

	}

	// 집중
	if (GameEngineInput::GetInst()->IsDown("KnightFocus") == true)
	{
		KnightManager_.ChangeState("FOCUS");
		return;

	}

	if (GetisOnGround() == false && isKnightPotal_ == false)
	{
		KnightManager_.ChangeState("FALL");
		return;
	}
}

void Knight::KnightWalkStart(const StateInfo& _Info)
{
	isPossibleDoubleJump_ = true;

	GetRenderer()->ChangeFrameAnimation("WALK_ANIMATION");
}

void Knight::KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}


	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	//SideDarkEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Side_Dark) });
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

	DoubleSlashTimer(_DeltaTime);

	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//isWallCheck(_DeltaTime, GetMoveDirection());

	if (GetisWall() == true || GetisCollWall() == true)
	{
		isKnihgtStillWall_ = true;
	}

	else
	{
		isKnihgtStillWall_ = false;
	}
	if (GetisWall() == true || GetisCollWall() == true)
	{
		//GetTransform().SetWorldMove(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);

		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			if (GetPrevDirection().CompareInt2D(float4::LEFT) == false)
			{
				SetPrevDirection(float4::LEFT);
				//PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("WALK_TURN");
				return;

			}

			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
			SetPrevDirection(float4::LEFT);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			if (GetPrevDirection().CompareInt2D(float4::RIGHT) == false)
			{
				SetPrevDirection(float4::RIGHT);
				KnightManager_.ChangeState("WALK_TURN");
				return;

			}

			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
			SetPrevDirection(float4::RIGHT);
		}
	}

	else if(GetisOnGround() == false && isKnightPotal_ == false)
	{
		KnightManager_.ChangeState("FALL");
		return;
	}


	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}
	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	// ========== 스테이트 변경 ==========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Potal, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSPotalCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}


	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
		return;

	}



	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
		return;
	}

	if (GetisKnightMove() == false)
	{
		//isKnihgtStillWall_ = false;

		KnightManager_.ChangeState("STILL");
		return;
	}

	// 대쉬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
		return;
	}

	if (isRunMode_ == true)
	{
		KnightManager_.ChangeState("RUN");
		return;
	}

}

void Knight::KnightWalkTurnStart(const StateInfo& _Info)
{
	if (GetPrevDirection().CompareInt2D(float4::LEFT) == true)
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();

		if (isRunMode_ == true)
		{
			GetRenderer()->ChangeFrameAnimation("RUN_TURN_ANIMATION");
		}
		else
		{
			GetRenderer()->ChangeFrameAnimation("WALK_TURN_LEFT_ANIMATION");

		}



	}

	else if (GetPrevDirection().CompareInt2D(float4::RIGHT) == true)
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();

		if (isRunMode_ == true)
		{
			GetRenderer()->ChangeFrameAnimation("RUN_TURN_ANIMATION");
		}
		else
		{
			GetRenderer()->ChangeFrameAnimation("WALK_TURN_RIGHT_ANIMATION");

		}

	}

	isWalkTurnEnd_ = false;
	isRunTurnEnd_ = false;
}

void Knight::KnightWalkTurnUpdate(float _DeltaTime, const StateInfo& _Info)
{

	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (isWalkTurnEnd_ == true || isRunTurnEnd_ == true) //애니메이션 end bool 값
	{
		isWalkTurnEnd_ = false;
		isRunTurnEnd_ = false;
		if (isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
			return;

		}

		else if (isRunMode_ == false)
		{
			KnightManager_.ChangeState("WALK");
			return;
		}
	}

	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	//SideDarkEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Side_Dark) });
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

	DoubleSlashTimer(_DeltaTime);

	//KnightDirectionCheck();


	if (GetisWall() == true || GetisCollWall() == true)
	{
		GetTransform().SetWorldMove(float4::ZERO * KnightRunSpeed_ * _DeltaTime);

	}
	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{

			GetTransform().SetWorldMove(float4::LEFT * KnightRunSpeed_ * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{

			GetTransform().SetWorldMove(float4::RIGHT * KnightRunSpeed_ * _DeltaTime);
		}
	}



	else if (GetisOnGround() == false && isKnightPotal_ == false)
	{
		KnightManager_.ChangeState("FALL");
		return;
	}


	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}
	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}
	// ========== 스테이트 변경 ==========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Potal, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSPotalCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}


	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
		return;

	}



	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
		return;
	}

	if (GetisKnightMove() == false)
	{
		//isKnihgtStillWall_ = false;

		KnightManager_.ChangeState("STILL");
		return;
	}

	// 대쉬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
		return;
	}

}

void Knight::KnightLookDownStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LOOK_DOWN_ANIMATION");
}

void Knight::KnightLookDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}


	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}
	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

	if (GameEngineInput::GetInst()->IsFree("KnightDown") == true)
	{
		KnightManager_.ChangeState("STILL");
		//KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}
}

void Knight::KnightLookDownEnd(const StateInfo& _Info)
{
}

void Knight::KnightLookUpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LOOK_UP_ANIMATION");

}

void Knight::KnightLookUpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}
	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (GameEngineInput::GetInst()->IsFree("KnightUp") == true)
	{
		KnightManager_.ChangeState("STILL");
		return;
	}

}

void Knight::KnightLookUpEnd(const StateInfo& _Info)
{
}

void Knight::KnightUpSlashJumpStart(const StateInfo& _Info)
{
	isDoubleJumpEnd_ = false;
	SetJumpPower({ 0, KnightDoubleJumpPower_ , 0 });
}

void Knight::KnightUpSlashJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	isKnihgtActtingMoveChack();
	KnightActtingDirectionCheck();
	KnightIsActtingCheck();
	isPixelCheckUp(_DeltaTime);

	ActtingMoveDirection_.Normalize();


	if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
	{
		isKnihgtStillWall_ = false;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);
	}


	if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
	{
		float4 Move = (float4::UP) * (GetGravity() * 1.7f) * _DeltaTime;
		SubJumpPower(Move);


		float JumpLenth = GetJumpPower().Length();
		if (JumpLenth <= Move.Length() || GetisUpBlock() == true /*|| GetisWall() == true*/)
		{
			KnightManager_.ChangeState("FALL");
			return;

		}
		GetTransform().SetWorldMove(GetJumpPower() * (GetJumpSpeed()) * _DeltaTime);

	}

	else
	{
		float4 Move = (float4::UP)*GetGravity() * _DeltaTime;
		Move.x += (-ActtingMoveDirection_.x * KnightActtingMoveDirPower_);
		Move.y += abs(Move.x);
		//Move.Length

		SubJumpPower(Move);
		float JumpLenth = GetJumpPower().y /*+ abs(GetJumpPower().x*/;
		float MoveLenth = Move.Length();

		this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);


		if (JumpLenth <= 0.0f || GetisWall() == true || GetisUpBlock() == true || GetisCollWall() == true)
		{
			KnightManager_.ChangeState("FALL");
			return;
		}

		//float4 Resulut = GetJumpPower()* GetJumpSpeed()* _DeltaTime;


		GetTransform().SetWorldMove({ (GetJumpPower() + JumpAccel_) * GetJumpSpeed() * _DeltaTime });
	}


	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

}

void Knight::KnightUpSlashJumpEnd(const StateInfo& _Info)
{
	JumpAccel_ = 0.f;
	//GetRenderer()->GetTransform().SetLocalScale({ 349, 186, 1 });
	//GetRenderer()->SetPivot(PIVOTMODE::BOT);

	this->SetisGround(false);
}

void Knight::KnightJumpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("JUMP_ANIMATION");

	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;
	isPressJumppingKey_ = true;

	//SetisGround(false);

	SetJumpPower({ 0, KnightJumpPower_, 0 });
}

void Knight::KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

	DoubleSlashTimer(_DeltaTime);

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}


	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		isPixelCheckUp(_DeltaTime);
		//isDoubleCheckAreaCheck(_DeltaTime);
		ActtingMoveDirection_.Normalize();
		JumpAccel_ -= 20.f *_DeltaTime;


		this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);
		//isWallRedCheck(ActtingMoveDirection_);

		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}


		if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
		{
			float4 Move = (float4::UP) ;
			SubJumpPower(Move * _DeltaTime * GetGravity());


			float JumpLenth = GetJumpPower().Length();
			if (JumpLenth <= Move.Length() || GetisUpBlock() == true /*|| GetisWall() == true*/)
			{
				KnightManager_.ChangeState("FALL");
				return;

			}
			GetTransform().SetWorldMove(GetJumpPower() * (GetJumpSpeed()) * _DeltaTime);

		}

		else
		{
			float4 Move = (float4::UP );
			Move.x += (-ActtingMoveDirection_.x/2 );
			//Move.y += abs(Move.x) * 2;
			//Move.Length

			SubJumpPower(Move * _DeltaTime * GetGravity());
			float JumpLenth = GetJumpPower().y /*+ abs(GetJumpPower().x*/;
			float MoveLenth = Move.Length();

			this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);


			if (JumpLenth <= 0.0f || GetisWall() == true || GetisUpBlock() == true || GetisCollWall() == true)
			{
				KnightManager_.ChangeState("FALL");
				return;
			}

			//float4 Resulut = GetJumpPower()* GetJumpSpeed()* _DeltaTime;


			GetTransform().SetWorldMove({ (GetJumpPower() ) * GetJumpSpeed() * _DeltaTime });
		}
		



		if (GetisWall() == true && isKnihgtStillWall_ == false && GetisUpBlock() == true && GetisCollWall() == true)
		{
			KnightManager_.ChangeState("FALL");
			return;
		}


	}


	// ========== 스테이트 변경 ==========


	// 위 공격
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		KnightManager_.ChangeState("UP_SLASH");
		return;
	}

	// 아래 공격
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightDown") == true)
	{
		KnightManager_.ChangeState("DOWN_SLASH");
		return;
	}

	// 기본 공격
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& GameEngineInput::GetInst()->IsFree("KnightDown") == true

		&& isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");		
		return;
	}

	//콤보 공격
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& isPossibleDoubleSlash_ == true)
	{

		KnightManager_.ChangeState("DOUBLE_SLASH");		
		return;
	}


	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		KnightManager_.ChangeState("FALL");
		return;
	}
}

void Knight::KnightJumpEnd(const StateInfo& _Info)
{
	JumpAccel_ = 0.f;
	//ActtingMoveDirection_ = float4::ZERO;

	//SetJumpPower({ 0, KnightJumpPower_, 0 });
	//isPressJumppingKey_ = false;

	this->SetisGround(false);
}

void Knight::KnightDoubleJumpStart(const StateInfo& _Info)
{
	//isPossibleDoubleJump_ = false;
	isDoubleJumpEnd_ = false;

	GetRenderer()->ChangeFrameAnimation("DOUBLE_JUMP_ANIMATION");

	SetJumpPower({ 0, KnightDoubleJumpPower_ , 0 });
	KnightDoubleJumpEffect_->SetEffectOn();
}

void Knight::KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();
		isPixelCheckUp(_DeltaTime);

		ActtingMoveDirection_.Normalize();


		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}

		// ======== Knight VS WallColl ========
		if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
			std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
			)
		{
			SetisCollWall(true);
		}
		else
		{
			SetisCollWall(false);

		}


		if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
		{
			float4 Move = (float4::UP) ;
			SubJumpPower(Move * _DeltaTime * GetGravity());


			float JumpLenth = GetJumpPower().Length();
			if (JumpLenth <= Move.Length() || GetisUpBlock() == true /*|| GetisWall() == true*/)
			{
				KnightManager_.ChangeState("FALL");
				return;

			}
			GetTransform().SetWorldMove(GetJumpPower() * (GetJumpSpeed()) * _DeltaTime);

		}

		else
		{
			this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);

			float4 Move = (float4::UP);
			Move.x += (-ActtingMoveDirection_.x /2);
		//	Move.y += abs(Move.x) * 2;

			SubJumpPower(Move * _DeltaTime * GetGravity());
			float JumpLenth = GetJumpPower().y /*+ abs(GetJumpPower().x*/;
			float MoveLenth = Move.Length();


			if (JumpLenth <= 0.0f || GetisWall() == true || GetisUpBlock() == true || GetisCollWall() == true)
			{
				KnightManager_.ChangeState("FALL");
				return;
			}

			//float4 Resulut = GetJumpPower()* GetJumpSpeed()* _DeltaTime;


			GetTransform().SetWorldMove({ (GetJumpPower()) * GetJumpSpeed() * _DeltaTime });
		}
	}

	// ========== 스테이트 변경 ==========

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") )
	{
		KnightManager_.ChangeState("FALL");
	}
	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}
	//// 위 공격
	//if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
	//	&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	//{
	//	KnightManager_.ChangeState("UP_SLASH");
	//}

}

void Knight::KnightDoubleJumpEnd(const StateInfo& _Info)
{
	JumpAccel_ = 0.f;
	SetisGround(false);
}

void Knight::KnightLandStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LAND_ANIMATION");
}

void Knight::KnightLandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 점프
	if (GameEngineInput::GetInst()->IsDown("KnightJump") == true)
	{
		KnightManager_.ChangeState("JUMP");
	}


	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	if (isLandEnd_ == true)
	{
		isLandEnd_ = false;
		KnightManager_.ChangeState("STILL");
		return;
	}


}

void Knight::KnightLandEnd(const StateInfo& _Info)
{
}

void Knight::KnightFallStart(const StateInfo& _Info)
{
	KnightFallAccel_ = 0.0f;

	isKnightActtingMove_ = false;
	//ActtingMoveDirection_ = float4::ZERO;

	//SetMoveDirection(float4::DOWN);

	GetRenderer()->ChangeFrameAnimation("FAll_ANIMATION");
}

void Knight::KnightFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());


	isKnihgtActtingMoveChack();
	KnightActtingDirectionCheck();
	KnightIsActtingCheck();

	//ActtingMoveDirection_.Normalize();
	isDoubleCheckAreaCheck(_DeltaTime);

	isPixelCheck(_DeltaTime, ActtingMoveDirection_);

	if (GetisOnGround() == true)
	{
		if (GetisKnightMove() == true && isRunMode_ == false)
		{
			KnightManager_.ChangeState("WALK");
			return;
		}

		if (GetisKnightMove() == true && isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
			return;
		}

		else
		{
			KnightManager_.ChangeState("LAND");
			return;
		}

	}

		// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
	{
		isKnihgtStillWall_ = false;
	}

	if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
	{

		float4 Move = (float4::DOWN /** GetGravity()  * 0.004f*/);

		float4 CurrentPos = {GetTransform().GetWorldPosition().x
							,GetTransform().GetWorldPosition().y };

		float4 DestPos = { GetTransform().GetWorldPosition().x 
							,GetTransform().GetWorldPosition().y + Move .y - KnightFallAccel_ };

		float4 MoveLerp = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * ((GetFallSpeed() )));


		GetTransform().SetWorldPosition(MoveLerp);
	}

	else
	{
   		float4 Move = float4::DOWN /** GetGravity() * 0.004f*/;
		Move.x = (ActtingMoveDirection_.x * KnightActtingMoveDirPower_);
		//Move.y += Move.x;
		//Move.Length
		this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);

		float4 CurrentPos = { GetTransform().GetWorldPosition().x
									,GetTransform().GetWorldPosition().y };

		float4 DestPos = { GetTransform().GetWorldPosition().x + ((Move.x * KnightActtingMoveDirPower_ ))
							,GetTransform().GetWorldPosition().y + Move.y - KnightFallAccel_ };

		float4 MoveLerp = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * GetFallSpeed());

		GetTransform().SetWorldPosition(MoveLerp);



	}

	//if(GetLevel()->GetNameConstRef() == "")
	KnightFallAccel_ += (17.f * _DeltaTime);


	//if (GetisWall() == true /*&& isKnihgtStillWall_ == false*/)
	//{
	//	KnightManager_.ChangeState("FALL");
	//	return;
	//}

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	// ======== Knight VS Monster ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	// ========== 스테이트 변경 ==========


	// 위 공격
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		KnightManager_.ChangeState("UP_SLASH");		
		return;

	}

	// 아래 공격
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightDown") == true)
	{
		KnightManager_.ChangeState("DOWN_SLASH");
		return;
	}

	// 기본 공격
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& GameEngineInput::GetInst()->IsFree("KnightDown") == true
		&& isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
		return;

	}

	// 콤보 공격
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
		return;
	}

	// 더블 점프
	if (true == GameEngineInput::GetInst()->IsDown("KnightJump") && isPossibleDoubleJump_ == true /*&& GetisDoubleJumpPossible() == true*/)
	{
		isPossibleDoubleJump_ = false;
		KnightManager_.ChangeState("DOUBLE_JUMP");		
		return;

	}
}

void Knight::KnightFallEnd(const StateInfo& _Info)
{

	KnightFallAccel_ = 0.0f;

	if (isKnightActtingMove_ == true)
	{
		SetMoveDirection(ActtingMoveDirection_);
	}
}

void Knight::KnightIntroFallStart(const StateInfo& _Info)
{
	isKnightActtingMove_ = false;


	GetRenderer()->ChangeFrameAnimation("FAll_ANIMATION");
}

void Knight::KnightIntroFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	isDoubleCheckAreaCheck(_DeltaTime);
	isPixelCheck(_DeltaTime, ActtingMoveDirection_);

	if (GetisOnGround() == true)
	{
		KnightManager_.ChangeState("INTRO_LAND");
		return;

	}

	float4 Move = (float4::DOWN /** GetGravity()  * 0.004f*/);

	float4 CurrentPos = { GetTransform().GetWorldPosition().x
						,GetTransform().GetWorldPosition().y };

	float4 DestPos = { GetTransform().GetWorldPosition().x
						,GetTransform().GetWorldPosition().y + Move.y};

	float4 MoveLerp = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() *1300.f);


	GetTransform().SetWorldPosition(MoveLerp);

}

void Knight::KnightIntroFallEnd(const StateInfo& _Info)
{
}

void Knight::KnightIntroLandStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("INTRO_LAND_ANIMATION");
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);

}

void Knight::KnightIntroLandUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GetRenderer()->GetCurFrameAnimation()->GetFrameAnimationDesc().CurFrame == 4)
	{
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);

	}

	if (isIntroLandEnd_ == true)
	{
		isIntroLandEnd_ = false;
		KnightManager_.ChangeState("STILL");
		return;
	}
}

void Knight::KnightIntroLandEnd(const StateInfo& _Info)
{
}

void Knight::KnightDashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DASH_ANIMATION");
	KnightDashTimer_ = 0.f;
	SetSpeed(1200.f);

}

void Knight::KnightDashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightDashTimer_ += _DeltaTime;
	//DoubleSlashTimer(_DeltaTime);

	this->KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());


	if (GetisWall() == true || GetisCollWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else
	{
		GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);
	}

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS Monster ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}


	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}


	// ========== 스테이트 변경 ==========

	//if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	//{
	//	KnightManager_.ChangeState("JUMP");
	//}

	//if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	//{
	//	isPressJumppingKey_ = false;
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	//{
	//	KnightManager_.ChangeState("SLASH");
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	//{
	//	KnightManager_.ChangeState("DOUBLE_SLASH");
	//}

	if (KnightDashTimer_ > 0.4f)
	{
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightDashEnd(const StateInfo& _Info)
{
	SetSpeed(300.f);
}

void Knight::KnightFocusStart(const StateInfo& _Info)
{
	isLowHealth_ = false;
	GetRenderer()->ChangeFrameAnimation("FOCUS_ANIMATION");
	KnightFocusEffect_ = GetLevel()->CreateActor<KnightFocusEffect>();
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::Focus);

	KnightFocusEffect_->GetTransform().SetWorldPosition(
		{this->GetTransform().GetWorldPosition().x
		, this->GetTransform().GetWorldPosition().y 
		, static_cast<float>(Z_ORDER::Effect)});
}

void Knight::KnightFocusUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnihgtFocusTimer_ += _DeltaTime;
	if (GameEngineInput::GetInst()->IsFree("KnightFocus") == true && GetRenderer()->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() < 5)
	{
		KnightFocusEffect_->Death();
		KnightFocusEffect_ = nullptr;
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::CancleFocus);
		KnightManager_.ChangeState("STILL");
		return;
	}



	if (GetRenderer()->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() == 8)
	{
		KnightBurstEffect* KnightBurstEffect_= 	GetLevel()->CreateActor<KnightBurstEffect>();

		KnightBurstEffect_->GetTransform().SetWorldPosition(
			{ this->GetTransform().GetWorldPosition().x
			, this->GetTransform().GetWorldPosition().y 
			, static_cast<float>(Z_ORDER::Effect) });

		KnightManager_.ChangeState("FOCUS_BURST");

		return;


	}

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}


	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}
}

void Knight::KnightFocusEnd(const StateInfo& _Info)
{
	KnihgtFocusTimer_ = 0.f;

	KnightFocusEffect_ = nullptr;
}

void Knight::KnightFocusBurstStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::ReturnFocus);

}

void Knight::KnightFocusBurstUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}


	if (isFocusEnd_ == true)
	{
		isFocusEnd_ = false;
		KnightData::GetInst()->SetisRefill(true);
		KnightManager_.ChangeState("STILL"); 
		return;
	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}
}

void Knight::KnightFocusBurstEnd(const StateInfo& _Info)
{
	//GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);

}

void Knight::KnightRunStart(const StateInfo& _Info)
{
	isPossibleDoubleJump_ = true;

	if (_Info.PrevState == "STILL" || _Info.PrevState == "WALK")
	{
		GetRenderer()->ChangeFrameAnimation("IDLE_TO_RUN_ANIMATION");
	}
	else
	{
		GetRenderer()->ChangeFrameAnimation("RUN_ANIMATION");
	}

}

void Knight::KnightRunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	//SideDarkEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Side_Dark) });
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

	DoubleSlashTimer(_DeltaTime);

	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());


	if (GetisWall() == true || GetisCollWall() == true)
	{
		isKnihgtStillWall_ = true;
	}

	else
	{
		isKnihgtStillWall_ = false;
	}
	if (GetisWall() == true || GetisCollWall() == true)
	{
		//GetTransform().SetWorldMove(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * KnightRunSpeed_ * _DeltaTime);

		//KnightManager_.ChangeState("FALL");
	}



	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			if (GetPrevDirection().CompareInt2D(float4::LEFT) == false)
			{
				SetPrevDirection(float4::LEFT);
				//PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("WALK_TURN");
				return;
			}

			GetTransform().SetWorldMove(float4::LEFT * KnightRunSpeed_ * _DeltaTime);
			SetPrevDirection(float4::LEFT);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			if (GetPrevDirection().CompareInt2D(float4::RIGHT) == false)
			{
				SetPrevDirection(float4::RIGHT);
				KnightManager_.ChangeState("WALK_TURN");
				return;

			}

			GetTransform().SetWorldMove(float4::RIGHT * KnightRunSpeed_ * _DeltaTime);
			SetPrevDirection(float4::RIGHT);
		}
	}



	else if (GetisOnGround() == false && isKnightPotal_ == false)
	{
		KnightManager_.ChangeState("FALL");
		return;
	}


	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}
	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}
	// ========== 스테이트 변경 ==========

	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Potal, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSPotalCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}


	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
		return;

	}



	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
		return;
	}

	if (GetisKnightMove() == false)
	{
		//isKnihgtStillWall_ = false;

		KnightManager_.ChangeState("STILL");
		return;
	}

	// 대쉬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
		return;
	}

	if (isRunMode_ == true)
	{
		KnightManager_.ChangeState("RUN");
		return;
	}
}

void Knight::KnightRunEnd(const StateInfo& _Info)
{
}

void Knight::KnightStunStart(const StateInfo& _Info)
{
	//KnightKnockbackTimer_ = 1.0f;
	KnightStunEffect_->StunEffectOn();
	GetRenderer()->ChangeFrameAnimation("STUN_ANIMATION");
	if (KnightData::GetInst()->GetisBossBattle() == true)
	{
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::Battle_Shaking);

	}
	else
	{
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::Shaking);

	}

	if (isKnightSpikeHit_ == true)
	{
		FadeOut* FadeOut_= GetLevel()->CreateActor<FadeOut>();
		FadeOut_->SetNoCountDeath(true);
		FadeOut_->SetFadeSpeed(1.5f);
	}


}

void Knight::KnightStunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (KnightKnockbackTimer_ > 0.04f)
	{
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	}

	else
	{
		GameEngineTime::GetInst()->SetTimeScale(0, 0.1f);

	}



	KnightKnockbackTimer_ += _DeltaTime;



	if (isKnightSpikeHit_ == true)
	{
		if (KnightKnockbackTimer_ > 0.2f)
		{
			KnightKnockbackTimer_ = 0.f;
			if (KnightData::GetInst()->GetCurMask() == -1)
			{
				isLowHealth_ = false;

				KnightData::GetInst()->SetisDeath(true);
				KnightData::GetInst()->SetisRevive(true);

				KnightManager_.ChangeState("DEATH");
			}

			else
			{
				KnightManager_.ChangeState("STILL");

			}
		}

		GetTransform().SetWorldMove(float4::UP * GetSpeed() * _DeltaTime);


	}
	else
	{
		if (KnightKnockbackTimer_ > 0.2f)
		{
			KnightKnockbackTimer_ = 0.f;
			if (KnightData::GetInst()->GetCurMask() == -1)
			{
				isLowHealth_ = false;

				KnightData::GetInst()->SetisDeath(true);
				KnightData::GetInst()->SetisRevive(true);

				KnightManager_.ChangeState("DEATH");
			}

			else
			{
				KnightManager_.ChangeState("STILL");

			}
		}

		GetTransform().SetWorldMove(-GetMoveDirection() * GetSpeed() * _DeltaTime);

	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}
}

void Knight::KnightStunEnd(const StateInfo& _Info)
{
	if (isKnightSpikeHit_ == true)
	{
		GetLevel()->CreateActor<FadeIn>();

		GetTransform().SetWorldPosition({ 2167, -2438, static_cast<float>(Z_ORDER::Knight) });
		isKnightSpikeHit_ = false;


	}


	if (KnightData::GetInst()->GetCurMask() == 0)
	{
		isLowHealth_ = true;
		LowHealth* LowHealth_ = GetLevel()->CreateActor<LowHealth>();
	}
	if (KnightData::GetInst()->GetisBossBattle() == true)
	{
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetInRoomMove);

	}

	else
	{
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);

	}

	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	KnightStunEffect_->StunEffectOff();

	isInvincibility_ = true;
}

void Knight::KnightDeathStart(const StateInfo& _Info)
{
	isInvincibility_ = false;

	GetRenderer()->ChangeFrameAnimation("DEATH_ANIMATION");
}

void Knight::KnightDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	if (KnightData::GetInst()->GetisShadow() == true)
	{
		KnightData::GetInst()->SetisShadow(false);
		KnightShadowData::GetInst()->SetisShadowDepart(true);
	}

	if (isDeathEnd_ == true)
	{
		isDeathEnd_ = false;
		KnightShadow* Shadow = GetLevel()->CreateActor<KnightShadow>();
		Shadow->GetTransform().SetWorldPosition({this->GetTransform().GetWorldPosition().x + 400.f, this->GetTransform().GetWorldPosition().y, 0});
		
		KnightData::GetInst()->SetisShadow(true);
		KnightData::GetInst()->SetisRevive(false);

		KnightShadowData::GetInst()->SetShadowPosition({ this->GetTransform().GetWorldPosition().x + 400.f, this->GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Knight_Shadow) });
		KnightManager_.ChangeState("GROUND_WAKE_UP");
		return;
	}
}

void Knight::KnightDeathEnd(const StateInfo& _Info)
{
}

void Knight::KnightWakeUpGroundStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WAKEUP_GROUND_ANIMATION");
}

void Knight::KnightWakeUpGroundUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isGroundWakeUpEnd_ == true)
	{
		isGroundWakeUpEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightWakeUpGroundEnd(const StateInfo& _Info)
{
}

void Knight::KnightWakeUpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WAKEUP_ANIMATION");
}

void Knight::KnightWakeUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isWakeUpEnd_ == true)
	{
		isWakeUpEnd_ = false;
	}
}

void Knight::KnightWakeUpEnd(const StateInfo& _Info)
{
}

void Knight::KnightSlashStart(const StateInfo& _Info)
{
	//isPossibleDoubleSlash_ = false;
	//KnightSlashTimer_ = 0.f;
	GetRenderer()->ChangeFrameAnimation("SLASH_ANIMATION");
	KnightSlashEffect_->GetCollision()->On();
	KnightSlashEffect_->SetAnimationSlash();

	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ 80, 50, 0 });

	}

	else if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ -80, 50, 0 });
	}
}

void Knight::KnightSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//isWallCheck(_DeltaTime);

	KnightSlashCollisionTimer_ += _DeltaTime;
	if (KnightSlashCollisionTimer_ > 0.1f)
	{
		KnightSlashCollisionTimer_ = 0.f;
		KnightSlashEffect_->GetCollision()->Off();

	}

	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		 )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}

	if (GetisWall() == true || GetisCollWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}

	// 낙하중에 공격한다면 애니메이션이 끝날 떄까지 낙하 스테이트로 이동하면 안된다. => 이유 : 애니메이션 처리
	// 그렇기 때문에 여기서 중력처리를 따로 하는중
	else if (GetisOnGround() == false || GetisWall() == false || GetisCollWall() == false)
	{
		KnightFallAccel_ += 10.f * _DeltaTime;

		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		isDoubleCheckAreaCheck(_DeltaTime);

		isPixelCheck(_DeltaTime, ActtingMoveDirection_);


		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}

	if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
	{

		this->isPixelCheck(_DeltaTime, float4::DOWN);
		float4 Move = (float4::DOWN * GetGravity()  * _DeltaTime);

		Move.y -= KnightFallAccel_;

		GetTransform().SetWorldMove(Move );
	}

	else
	{
		this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);
   		float4 Move = float4::DOWN * GetGravity() * _DeltaTime;

		Move.x += KnightActtingMoveDirPower_ * ActtingMoveDirection_.x;
		Move.y -= KnightFallAccel_;

		GetTransform().SetWorldMove(Move);


	}

		if (isSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");

		}

	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);
	}

	// ========== 스테이트 변경 ==========
	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}

	//애니메이션이 끝나면 
	if (isSlashEnd_ == true)
	{
		KnightFallAccel_ = 0.0f;

		isSlashEnd_ = false;

		if (_Info.PrevState == "RUN" || isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
		}

		if (_Info.PrevState == "STILL")
		{
			KnightManager_.ChangeState("STILL");
		}

		if (_Info.PrevState == "WALK")
		{
			KnightManager_.ChangeState("WALK");
		}
	}
}

void Knight::KnightSlashEnd(const StateInfo& _Info)
{
	KnightSlashCollisionTimer_ = 0.f;
	KnightSlashEffect_->GetCollision()->Off();
	isPossibleDoubleSlash_ = true;

}

void Knight::KnightDoubleSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DOUBLE_SLASH_ANIMATION");

	KnightSlashEffect_->GetCollision()->On();
	KnightSlashEffect_->SetAnimationDoubleSlash();

	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ 80, 50, 0 });

	}

	else if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ -80, 50, 0 });

	}


}

void Knight::KnightDoubleSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{


	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());


	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);

	}
	// ======== Knight VS Monster ========

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS MonsterAttack ========
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster_Attack, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterAttackCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		KnightManager_.ChangeState("STUN");
		KnightData::GetInst()->SetisBreak(true);
		return;

	}



	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (GetisWall() == true || GetisCollWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}



	// 낙하중에 공격한다면 애니메이션이 끝날 떄까지 낙하 스테이트로 이동하면 안된다. => 이유 : 애니메이션 처리
	// 그렇기 때문에 여기서 중력처리를 따로 하는중
	else if (GetisOnGround() == false || GetisWall() == false || GetisCollWall() == false)
	{
		KnightFallAccel_ += 10.f * _DeltaTime;
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		isDoubleCheckAreaCheck(_DeltaTime);

		isPixelCheck(_DeltaTime, ActtingMoveDirection_);


		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}

		if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
		{

			this->isPixelCheck(_DeltaTime, float4::DOWN);
			float4 Move = (float4::DOWN * GetGravity() * _DeltaTime);

			Move.y -= KnightFallAccel_;

			GetTransform().SetWorldMove(Move);
		}

		else
		{
			this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);
			float4 Move = float4::DOWN * GetGravity() * _DeltaTime;

			Move.x += KnightActtingMoveDirPower_ * ActtingMoveDirection_.x;
			Move.y -= KnightFallAccel_;

			GetTransform().SetWorldMove(Move);


		}




		if (isSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");

		}
	}

	// ========== 스테이트 변경 ==========

	//if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	//{
	//	KnightManager_.ChangeState("JUMP");
	//}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}

	KnightSlashCollisionTimer_ += _DeltaTime;
	if (KnightSlashCollisionTimer_ > 0.1f)
	{
		KnightSlashCollisionTimer_ = 0.f;
		KnightSlashEffect_->GetCollision()->Off();

	}

	if (isDoubleSlashEnd_ == true)
	{
		KnightFallAccel_ = 0.0f;

		isDoubleSlashEnd_ = false;

		if (_Info.PrevState == "RUN" || isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
		}

		if (_Info.PrevState == "STILL")
		{
			KnightManager_.ChangeState("STILL");
		}

		if (_Info.PrevState == "WALK")
		{
			KnightManager_.ChangeState("WALK");
		}




		//KnightSlashEffect_->Off();

	}

}

void Knight::KnightDoubleSlashEnd(const StateInfo& _Info)
{
	KnightSlashEffect_->GetCollision()->Off();
	KnightSlashCollisionTimer_ = 0.f;
	isPossibleDoubleSlash_ = false;
}

void Knight::KnightUpSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("UP_SLASH_ANIMATION");

	KnightSlashEffect_->GetCollision()->On();
	KnightSlashEffect_->SetAnimationUpSlash();

	KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ 0, 100, 0 });


}

void Knight::KnightUpSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//isWallCheck(_DeltaTime);
	KnightSlashCollisionTimer_ += _DeltaTime;
	if (KnightSlashCollisionTimer_ > 0.1f)
	{
		KnightSlashCollisionTimer_ = 0.f;
		KnightSlashEffect_->GetCollision()->Off();

	}
	// 내가 만약 무적이면 깜빡거린다
	if (isInvincibility_ == true)
	{
		KnightInvincibiliting(_DeltaTime);
	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true )
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);
	}

	if (GetisWall() == true || GetisCollWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}

	// 낙하중에 공격한다면 애니메이션이 끝날 떄까지 낙하 스테이트로 이동하면 안된다. => 이유 : 애니메이션 처리
	// 그렇기 때문에 여기서 중력처리를 따로 하는중
	else if (GetisOnGround() == false && GetisWall() == false && GetisCollWall() == false)
	{
		KnightFallAccel_ += 10.f * _DeltaTime;
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		isDoubleCheckAreaCheck(_DeltaTime);

		isPixelCheck(_DeltaTime, ActtingMoveDirection_);


		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}

		//if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
		//{
			this->isPixelCheck(_DeltaTime, float4::DOWN);
			float4 Move = (float4::DOWN * GetGravity() * _DeltaTime);

		//	Move.y -= KnightFallAccel_;

			GetTransform().SetWorldMove(Move);
		//}

		//else
		//{
		//	this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);
		//	float4 Move = float4::DOWN * GetGravity() * _DeltaTime;

		//	Move.x += KnightActtingMoveDirPower_ * ActtingMoveDirection_.x;
		//	//Move.y -= KnightFallAccel_;

		//	GetTransform().SetWorldMove(Move);
		//}

		if (isSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");
		}
	}

	// ========== 스테이트 변경 ==========
	//if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	//{
	//	KnightManager_.ChangeState("JUMP");
	//}

	//if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	//{
	//	isPressJumppingKey_ = false;
	//}

	//애니메이션이 끝나면 
	if (isUpSlashEnd_ == true)
	{
		KnightFallAccel_ = 0.0f;

		isUpSlashEnd_ = false;

		if (_Info.PrevState == "RUN" || isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
		}

		if (_Info.PrevState == "STILL")
		{
			KnightManager_.ChangeState("STILL");
		}

		if (_Info.PrevState == "WALK")
		{
			KnightManager_.ChangeState("WALK");
		}
	}
}

void Knight::KnightUpSlashEnd(const StateInfo& _Info)
{
	KnightSlashCollisionTimer_ = 0.f;
	KnightSlashEffect_->GetCollision()->Off();
	isPossibleDoubleSlash_ = true;
}

void Knight::KnightDownSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DOWN_SLASH_ANIMATION");
	KnightSlashEffect_->GetCollision()->On();
	KnightSlashEffect_->SetAnimationDownSlash();
	KnightSlashEffect_->GetCollision()->GetTransform().SetLocalPosition({ 0, -10, 0 });

}

void Knight::KnightDownSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (KnightSlashEffect_->GetisColl() == true)
	{
		KnightManager_.ChangeState("SLASH_JUMP");
		return;
	}

	KnightSlashCollisionTimer_ += _DeltaTime;
	if (KnightSlashCollisionTimer_ > 0.1f)
	{
		KnightSlashCollisionTimer_ = 0.f;
		KnightSlashEffect_->GetCollision()->Off();
	}

	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//isWallCheck(_DeltaTime);

	if (GetisWall() == true || GetisCollWall() == true)
	{
		//SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}

	// 낙하중에 공격한다면 애니메이션이 끝날 떄까지 낙하 스테이트로 이동하면 안된다. => 이유 : 애니메이션 처리
	// 그렇기 때문에 여기서 중력처리를 따로 하는중
	else if (GetisOnGround() == false && GetisWall() == false && GetisCollWall() == false)
	{
		KnightFallAccel_ += 10.f * _DeltaTime;

		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		isDoubleCheckAreaCheck(_DeltaTime);

		isPixelCheck(_DeltaTime, ActtingMoveDirection_);


		if (isKnightActtingMove_ == true && float4::ZERO.CompareInt2D(ActtingMoveDirection_) == false)
		{
			isKnihgtStillWall_ = false;
		}

		if (ActtingMoveDirection_.CompareInt2D(float4::ZERO) || isKnihgtStillWall_ == true || GetisWall() == true || GetisCollWall() == true)
		{

			this->isPixelCheck(_DeltaTime, float4::DOWN);
			float4 Move = (float4::DOWN * GetGravity() * _DeltaTime);

			Move.y -= KnightFallAccel_;

			GetTransform().SetWorldMove(Move);
		}

		else
		{
			this->isPixelCheck(_DeltaTime, ActtingMoveDirection_);
			float4 Move = float4::DOWN * GetGravity() * _DeltaTime;

			Move.x += KnightActtingMoveDirPower_ * ActtingMoveDirection_.x;
			Move.y -= KnightFallAccel_;

			GetTransform().SetWorldMove(Move);
		}

		if (isSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");
		}
	}

	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnightVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		KnightData::GetInst()->SetisBreak(true);
		KnightManager_.ChangeState("STUN");
		return;
	}

	// ========== 스테이트 변경 ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}


	//애니메이션이 끝나면 
	if (isDownSlashEnd_ == true)
	{
		isDownSlashEnd_ = false;
		KnightFallAccel_ = 0.0f;

		if (_Info.PrevState == "RUN" || isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
		}

		if (_Info.PrevState == "STILL")
		{
			KnightManager_.ChangeState("STILL");
		}

		if (_Info.PrevState == "WALK")
		{
			KnightManager_.ChangeState("WALK");
		}

	}
}

void Knight::KnightDownSlashEnd(const StateInfo& _Info)
{
	KnightSlashCollisionTimer_ = 0.f;
	KnightSlashEffect_->GetCollision()->Off();
	isPossibleDoubleSlash_ = true;
}

void Knight::KnightMapStillStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "STILL")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_ANIMATION");

	}

	if (_Info.PrevState == "MAP_WALKING")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_STILL_ANIMATION");
	}
}

void Knight::KnightMapStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("STILL");
	}

	if (GetisKnightMove() == true)
	{
		//GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
	}
}

void Knight::KnightMapStillEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapWalkinglStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "MAP_STILL")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
	}

	if (_Info.PrevState == "MAP_WALKING_TURN")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
	}
}

void Knight::KnightMapWalkinglUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//this->isWallCheck(_DeltaTime);

	if (GetisWall() == true || GetisCollWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			if (GetPrevDirection().CompareInt2D(float4::LEFT) == false)
			{
				SetPrevDirection(float4::LEFT);
				//PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("WALK_TURN");
				return;

			}

			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
			SetPrevDirection(float4::LEFT);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			if (GetPrevDirection().CompareInt2D(float4::RIGHT) == false)
			{
				SetPrevDirection(float4::RIGHT);
				KnightManager_.ChangeState("WALK_TURN");
				return;

			}

			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
			SetPrevDirection(float4::RIGHT);
		}
	}


	else
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("FALL");
	}


	// ========== 스테이트 변경 ==========


	if (GetisKnightMove() == false)
	{
		KnightManager_.ChangeState("MAP_STILL");
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("WALK");
	}
}

void Knight::KnightMapWalkinglEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapWalkingTurnlStart(const StateInfo& _Info)
{
	if (GetPrevDirection().CompareInt2D(float4::LEFT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_TURN_RIGHT_ANIMATION");
	}

	if (GetPrevDirection().CompareInt2D(float4::RIGHT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_TURN_LEFT_ANIMATION");
	}
}

void Knight::KnightMapWalkingTurnlUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isMapWalkTurnEnd_ == true)
	{
		isMapWalkTurnEnd_ = false;
		KnightManager_.ChangeState("MAP_WALKING");
	}
}

void Knight::KnightMapWalkingTurnlEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklStart(const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelStart(const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelEnd(const StateInfo& _Info)
{
}

void Knight::KnightSlideStart(const StateInfo& _Info)
{


	GetRenderer()->ChangeFrameAnimation("SLIDE_ANIMATION");
}

void Knight::KnightSlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(float4::DOWN * GetGravity() * GetFallSpeed() * _DeltaTime);

	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//	isWallCheck(_DeltaTime, GetMoveDirection());


	if (GetisOnGround() == true)
	{
		if (GetisKnightMove() == true && isRunMode_ == false)
		{
			KnightManager_.ChangeState("WALK");
			return;
		}

		if (GetisKnightMove() == true && isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
			return;
		}

		else
		{
			KnightManager_.ChangeState("LAND");
			return;
		}

	}
	else if (GetisWall() == false || GetisCollWall() == false)
	{
		KnightManager_.ChangeState("FALL");
	}
	else if (true == GameEngineInput::GetInst()->IsDown("KnightJump"))
	{
		KnightManager_.ChangeState("WALL_JUMP");
	}


	//else 
	//{
	//	KnightManager_.ChangeState("FALL");
	//	return;
	//}
}

void Knight::KnightSlideEnd(const StateInfo& _Info)
{
}

void Knight::KnightWallJumpStart(const StateInfo& _Info)
{
	KnihgtSlideNegativeRenderer();
	GetRenderer()->ChangeFrameAnimation("WALL_JUMP_ANIMATION");

	SetJumpPower({ 0, 100.f, 0 });
}

void Knight::KnightWallJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SubJumpPower(((float4::UP * 1.3f) + ( GetMoveDirection())) * GetGravity() * _DeltaTime);
	GetTransform().SetWorldMove(GetJumpPower() * 12 * _DeltaTime);


	if (GetJumpPower().y <= 0.f )
	{
		KnightManager_.ChangeState("WALL_JUMP_LAND");
	}
}

void Knight::KnightWallJumpEnd(const StateInfo& _Info)
{
	KnihgtSlidePositiveRenderer();
}

void Knight::KnightWallJumpLandStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WALL_JUMP_ANIMATION");

	SetJumpPower({ 0, 100.f, 0 });
}

void Knight::KnightWallJumpLandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SubJumpPower(((float4::UP * 1.3f) + (-GetMoveDirection())) * GetGravity() * _DeltaTime);
	GetTransform().SetWorldMove(GetJumpPower() * 12 * _DeltaTime);

	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	if (GetisWall() == true || GetisCollWall() == true)
	{
		KnightManager_.ChangeState("SLIDE");
	}
	if (GetJumpPower().y <= 0.f && GetisWall() == false && GetisCollWall() == false)
	{
		KnightManager_.ChangeState("FALL");
	}
}

void Knight::KnightWallJumpLandEnd(const StateInfo& _Info)
{
}

void Knight::KnightSitStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SIT_ANIMATION");
	GetTransform().SetLocalMove({0, 10.f});
	KnightData::GetInst()->SetisSitting(true);

}

void Knight::KnightSitUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsDown("OnOffSettingPage"))
	{
		KnightData::GetInst()->SetisSetting(!KnightData::GetInst()->GetisSetting());
	}


	if (true == GameEngineInput::GetInst()->IsDown("KnightUp") && KnightData::GetInst()->GetisSetting() == false)
	{
		KnightManager_.ChangeState("STILL");

	}
}

void Knight::KnightSitEnd(const StateInfo& _Info)
{
	KnightData::GetInst()->SetisSitting(false);
	GetTransform().SetLocalMove({ 0, -10.f });

}

void Knight::KnightTalkingStart(const StateInfo& _Info)
{
}

void Knight::KnightTalkingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::NPC, CollisionType::CT_OBB2D,
		std::bind(&Knight::NPCNextDialogueCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

		
	}

}

void Knight::KnightTalkingEnd(const StateInfo& _Info)
{
}

void Knight::KnightShoppingStart(const StateInfo& _Info)
{
}

void Knight::KnightShoppingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::NPC, CollisionType::CT_OBB2D,
		std::bind(&Knight::ShopCloseCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

	}

}

void Knight::KnightShoppingEnd(const StateInfo& _Info)
{
}

void Knight::KnightDoorStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DOOR_ANIMATION");

}

void Knight::KnightDoorUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isDoorEnd_ == true)
	{
		isDoorEnd_ = false;
		GEngine::ChangeLevel(ChangeLevel_);
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightDoorEnd(const StateInfo& _Info)
{
	ChangeLevel_ = "";
}

void Knight::KnightTabletStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SEE_ANIMATION");

}

void Knight::KnightTabletUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// ======== Knight VS Tablet ========

	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Tablet, CollisionType::CT_OBB2D,
		std::bind(&Knight::KnihgtVSTabletCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{

	}

}

void Knight::KnightTabletEnd(const StateInfo& _Info)
{
}

void Knight::KnightTabletReturnToIdleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SEE_RETURN_ANIMATION");

}

void Knight::KnightTabletReturnToIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isReturnToIdle_ == true)
	{
		isReturnToIdle_ = false;
		KnightManager_.ChangeState("STILL");

	}
}

void Knight::KnightTabletReturnToIdleEnd(const StateInfo& _Info)
{
}

