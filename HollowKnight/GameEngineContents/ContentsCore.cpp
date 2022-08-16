#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/KingsPassLevel.h"
#include "KnightData.h"
#include "KnightShadowData.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	//================================
	//    폰트
	//================================
	GameEngineFont::Load("Noto Serif KR");

	//================================
	//    텍스처 / 타이틀
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Title");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	//================================
	//    텍스처 / UI
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Point");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("main_menu_pointer_anim0000-Sheet.png", 11, 1);

	}



	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Vessel");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("HUD Cln_HUD_frame_v020000-Sheet.png", 6, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Mask");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("HUD Cln_appear_v020000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("HUD Cln_idle_v020000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("HUD Cln_add_health_appear0000-Sheet.png", 14, 1);
		GameEngineTexture::Cut("HUD Cln_break_backboard0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("HUD Cln_refill0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("MaskWait.png", 2, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Geo");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("HUD Cln_coin_get0001-Sheet.png", 3, 1);
		GameEngineTexture::Cut("HUD Cln_HUD_coin_break_short0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("HUD Cln_HUD_coin_v020000-Sheet.png", 5, 1);
	
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Soul");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("HUD_Soulorb_fills_soul_grow0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("HUD_Soulorb_fills_soul_idle0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("HUD_Soulorb_fills_soul_shrink0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("HUD Cln_soul_orb_glow0000.png", 1, 1);
	}

	//================================
	//    텍스처 / 맵 아이템
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("MapItem");
		Dir.Move("Geo");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Geo_coin_air000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("Geo_coin0000-Sheet.png", 8, 1);

	}

	//================================
	//    텍스처 / 몬스터
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Monster");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Buzzer_death0000-Sheet.png", 3, 1);
		GameEngineTexture::Cut("Buzzer_fly0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Buzzer_idle_01-Sheet.png", 3, 1);
		GameEngineTexture::Cut("Buzzer_startle_01-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Buzzer_turn001-Sheet.png", 2, 1);

		GameEngineTexture::Cut("Crawler_goomba_death0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Crawler_goomba_turn_r_0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Crawler_goomba_turn0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Crawler_goomba_walk0000-Sheet.png", 4, 1);
	}

	//================================
	//    텍스처 / 맵
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("level1");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("level2");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("level3");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("level4");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	//================================
	//    텍스처 / 플레이어
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		//기본
		GameEngineTexture::Cut("Knight_idle_still_020000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("Knight_jump_01-Sheet.png", 6, 1);

		GameEngineTexture::Cut("Knight_land0000-Sheet.png", 3, 1);
		GameEngineTexture::Cut("Knight_fall_01-Sheet.png", 6, 1);

		GameEngineTexture::Cut("Knight_walk0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Knight DJump Cutscene Cln_collect_double_jump0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Knight_double_jump_v020000-Sheet.png", 8, 1);

		GameEngineTexture::Cut("Knight_turn000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_dash_v020000-Sheet.png", 12, 1);

		GameEngineTexture::Cut("Knight_run0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Knight_idle_to_run0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Knight_run_to_idle000-Sheet.png", 6, 1);

		GameEngineTexture::Cut("Knight_focus_v020000-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Knight_idle_low_health000-Sheet.png", 10, 1);

		GameEngineTexture::Cut("Knight_wake_up_ground0000-Sheet.png", 21, 1);


		// 벽타기
		GameEngineTexture::Cut("Knight_wall_slide0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_wall_jump0000-Sheet.png", 3, 1);

		// 스턴
		GameEngineTexture::Cut("Knight_stun0000-Sheet.png", 5, 1);

		// 사망
		GameEngineTexture::Cut("Knight_death_anim0000-Sheet.png", 14, 1);

		// 지도보기
		GameEngineTexture::Cut("Knight_sit_map_look0026-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_walk_map0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Knight_walk_map_turn0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_sit_map_write0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_idle_map0000-Sheet.png", 9, 1);

		// 살펴보기
		GameEngineTexture::Cut("Knight_look_down0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Knight_look_up0000-Sheet.png", 6, 1);

		// 공격
		GameEngineTexture::Cut("Knight_slash_left_longer0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Knight_up_slash0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Knight_down_slash_v02000-Sheet.png", 5, 1);

		// 땅에서 기상
		GameEngineTexture::Cut("Knight_wake_up_ground0000-Sheet.png", 5, 1);

		// 기상
		GameEngineTexture::Cut("Knight_wake_up_ground0000-Sheet.png", 21, 1);
		GameEngineTexture::Cut("Knight_wake0000-Sheet.png", 5, 1);

	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");
		Dir.Move("Shadow");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Hollow Shade Cln_idle0000-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_appear0000-Sheet.png", 30, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_death000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_fly000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_slash000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_startle0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_turn000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_depart000-Sheet.png", 9, 1);

		GameEngineTexture::Cut("Hollow Shade Cln_death_explode0000-Sheet.png", 3, 1);
		GameEngineTexture::Cut("Hollow Shade Cln_slash_effect007-Sheet.png", 2, 1);

	}


	//================================
	//    텍스처 / 이펙트
	//================================

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");
		Dir.Move("Effect");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}


		// 스킬
		GameEngineTexture::Cut("Knight_cast_v030002-Sheet.png", 12, 1);

		//이펙트
		GameEngineTexture::Cut("Knight_double_slashes_effect-Sheet.png", 3, 1);
		GameEngineTexture::Cut("Knight_slashes_effect0001-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_up_slash_effect0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_down_slash_effect0001-Sheet.png", 2, 1);

		//사마귀 이펙트
		GameEngineTexture::Cut("Knight_mantis_slash_left0005-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_mantis_up_slash0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_mantis_down_slash0001-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_mantis_slash_left0001-Sheet.png", 2, 1);

	}

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	//================================
	//    레벨 생성
	//================================
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<KingsPassLevel>("KingsPassLevel");

	ChangeLevel("TitleLevel");
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
	
}

void ContentsCore::End()
{
	KnightData::Destroy();
	KnightShadowData::Destroy();

}