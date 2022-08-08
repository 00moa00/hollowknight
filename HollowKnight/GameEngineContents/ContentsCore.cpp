#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/KingsPassLevel.h"

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
	//GameEngineWindow::GetInst()->SetWindowScaleAndPosition(float4{1920,1080}, float4{0,0});

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Title");


		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");


		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}

		GameEngineTexture::Cut("main_menu_pointer_anim0000-Sheet.png", 11, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Monster");


		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("level1");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
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

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
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

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
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

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}

		//기본
		GameEngineTexture::Cut("Knight_idle_still_020000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("Knight_shadow_dash0000-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Knight_jump_01-Sheet.png", 6, 1);
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


		// 지도보기
		GameEngineTexture::Cut("Knight_sit_map_look0026-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_walk_map0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Knight_walk_map_turn0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Knight_sit_map_write0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_idle_map0000-Sheet.png", 9, 1);


		// 살펴보기
		GameEngineTexture::Cut("Knight_look_down0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Knight_look_up0000-Sheet.png", 6, 1);

		//공격
		GameEngineTexture::Cut("Knight_slash_left_longer0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Knight_up_slash0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Knight_down_slash_v02000-Sheet.png", 5, 1);

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




	//Dir.Move("BlackSet");
	//GameEngineFolderTexture::Load(Dir.GetFullPath());

	// Knight


	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}


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

}