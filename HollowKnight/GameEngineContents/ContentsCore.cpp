#include "PreCompile.h"

#include "ContentsCore.h"

#include "TitleLevel.h"
#include "KingsPassLevel1.h"
#include "KingsPassLevel2.h"
#include "KingsPassLevel3.h"
#include "KingsPassLevel4.h"

#include "CrossroadsLevel1.h"
#include "CrossroadsLevel2.h"

#include "DirtmouthLevel1.h"
#include "DirtmouthLevel2.h"

#include "GrimmDirtmouthLevel1.h"
#include "GrimmDirtmouthLevel2.h"

#include "KingsPassGrimmOpenLevel.h"

#include "GrimmLevel.h"

#include "MapShopLevel.h"
#include "SlyShopLevel.h"

#include "KnightData.h"
#include "KnightShadowData.h"

#include "FireballPromptLevel.h"
#include "ScreamPromptLevel.h"

#include <GameEngineCore/GameEngineBlend.h>
#include "CameraGUI.h"

//#include <GameEngineCore/GameEngineLevel.h>

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
	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("TextureAtlasMask");
		NewPipe->SetVertexShader("Mask.hlsl");
		NewPipe->SetPixelShader("Mask.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Noise");
		NewPipe->SetInputAssembler1VertexBuffer("FullRect");
		NewPipe->SetInputAssembler2IndexBuffer("FullRect");
		NewPipe->SetVertexShader("Noise.hlsl");
		NewPipe->SetPixelShader("Noise.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("LightCut");
		NewPipe->SetVertexShader("LightCut.hlsl");
		NewPipe->SetPixelShader("LightCut.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Overlay");
		NewPipe->SetInputAssembler1VertexBuffer("FullRect");
		NewPipe->SetInputAssembler2IndexBuffer("FullRect");
		NewPipe->SetVertexShader("Overlay.hlsl");
		NewPipe->SetPixelShader("Overlay.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Vignette");
		NewPipe->SetInputAssembler1VertexBuffer("FullRect");
		NewPipe->SetInputAssembler2IndexBuffer("FullRect");
		NewPipe->SetVertexShader("Vignette.hlsl");
		NewPipe->SetPixelShader("Vignette.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("WhiteCutPostEffect");
		NewPipe->SetInputAssembler1VertexBuffer("FullRect");
		NewPipe->SetInputAssembler2IndexBuffer("FullRect");
		NewPipe->SetVertexShader("WhiteCutPostEffect.hlsl");
		NewPipe->SetPixelShader("WhiteCutPostEffect.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Bloom");
		NewPipe->SetInputAssembler1VertexBuffer("FullRect");
		NewPipe->SetInputAssembler2IndexBuffer("FullRect");
		NewPipe->SetVertexShader("Bloom.hlsl");
		NewPipe->SetPixelShader("Bloom.hlsl");
	}


	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		// 알파쪽만 따로 처리하는 옵션
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		GameEngineBlend::Create("AlphaBlend2", Desc);
	}

	{
		// 1, 1, 1, 1 * 뭔가 + 0, 0ㅏ, * 뭔가
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		// Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlend::Create("Overlay", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("LightenBlend", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = TRUE;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_DEST_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("MultplyBlend", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = TRUE;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("AddBlend", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = TRUE;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Addition", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = TRUE;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_MIN;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_MIN;

		GameEngineBlend::Create("DarkenBlend", Desc);
	}
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

		GameEngineTexture::Cut("wispy_smoke_particle_abyss.png", 1, 5);

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("TitleUI");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Area Title Cln_fleur_top0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Area Title Cln_fleur_top0011-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Area Title Cln_fleur_bottom0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("Area Title Cln_fleur_bottom0011-Sheet.png", 11, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Heart Piece UI Cln");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Heart Piece UI Cln_moving_health0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_010000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_020000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_030000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_040000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Heart Piece UI Cln_HP_UI_fuse0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("white_servant_death_flash0000-Sheet.png", 4, 1);

	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Key");


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
		Dir.Move("UI");
		Dir.Move("Prompts");

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
		Dir.Move("UI");
		Dir.Move("Prompts");
		Dir.Move("PromptUI");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Prompts Cln_prompt_appear0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Prompts Cln_prompt_appear0009-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Prompts Cln_prompt_idle0000-Sheet.png", 5, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Prompts");
		Dir.Move("PromptTitle");

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
		Dir.Move("UI");
		Dir.Move("Prompts");
		Dir.Move("Spell Prompt");

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
		Dir.Move("UI");
		Dir.Move("Dialogue");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Dialogue Cln_dialogue_fleur_bottom0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Dialogue Cln_dialogue_fleur_top0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Dialogue Cln_arrow_down0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Dialogue Cln_fullstop0000-Sheet.png", 4, 1);


	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Shop");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("UI_shops_animated_Shop_Menu_top0000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png",12, 1);
		GameEngineTexture::Cut("UI_shops_animated_Shop_Menu_figurehead_sly0000-Sheet.png", 7, 1);

	}

	//================================
	//    텍스처 / NPC
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Npc");
		Dir.Move("Elderbug");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
		
		GameEngineTexture::Cut("Elderbug_idle_01-Sheet.png", 6, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Npc");
		Dir.Move("Brumm");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Brum Cln_grimmkin_accordian0000-Sheet.png", 11, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Npc");
		Dir.Move("Iselda");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Iselda Cln_idle_to_Shop0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Iselda Cln_idle0013-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Iselda Cln_Shop_0006-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Iselda Cln_Shop_to_idle0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Iselda Cln_talk_right0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Iselda Cln_turn0001-Sheet.png", 5, 1);


	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Npc");
		Dir.Move("Sycophant");

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
		Dir.Move("Npc");
		Dir.Move("Sly");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Sly_town_idle0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Sly_turn_left_to_right0000-Sheet.png", 3, 1);

	}

	//================================
	//    텍스처 / Setting
	//================================

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Setting");

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
		Dir.Move("Setting");
		Dir.Move("Item");

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
		Dir.Move("Setting");
		Dir.Move("SpellIcon");

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
		Dir.Move("Setting");
		Dir.Move("Charm");

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
		Dir.Move("Setting");
		Dir.Move("CharmSlot");
		Dir.Move("UI");

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
		Dir.Move("Setting");
		Dir.Move("MiniMap");
		Dir.Move("Forgotten Crossroads");


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
		Dir.Move("Setting");
		Dir.Move("MiniMap");
		Dir.Move("Dirtmouth");


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
		Dir.Move("Setting");
		Dir.Move("MiniMap");
		Dir.Move("Crystal Peak");


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
		Dir.Move("Setting");
		Dir.Move("MiniMap");
		Dir.Move("Fungal Wastes");


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
		Dir.Move("Setting");
		Dir.Move("MiniMap");
		Dir.Move("Stag Station");


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
		Dir.Move("Setting");
		Dir.Move("UI Inventroy animated");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("UI_inventory_animated_Border_Fleur_arrow0000-Sheet.png", 11, 1);
		GameEngineTexture::Cut("UI_inventory_animated_Border_Fleur_bottom0000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("UI_inventory_animated_Border_Fleur_corner0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("UI_inventory_animated_Border_Fleur_top0000-Sheet.png", 11, 1);


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
		Dir.Move("Crawler");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

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
		Dir.Move("Monster");
		Dir.Move("Buzzer");


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

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Grimm");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Grimm Cln_Grimm_air_dash0000-Sheet.png", 18, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_anims_v050000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_arm0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_boss_balloon_attack0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Grimm Cln_grimm_boss_flame_pillar_talk_loop0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_Boss_ground_spike_attack0003-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_bow0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_cast0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_death_stun0000-Sheet.png", 2, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_evade0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_flame_pillar0000-Sheet.png", 15, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_idle_right0000-Sheet.png", 13, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_idle0000-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_roar0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_slash_antic0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_slash0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_slash0000-Sheet-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_stun_bat0000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_stun_explode0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_teleport0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_arm0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Grimm NPC_grimm_boss_flame_pillar_talk_loop0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_bow0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_flame_pillar0000-Sheet.png", 15, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_idle_right0000-Sheet.png", 13, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_idle0000-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Grimm NPC_Grimm_teleport0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Grimm_crowd0000-Sheet.png", 8, 1);
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("GrimmEffect");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Grimm Cln_Flame_bat0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Grimm Cln_Flame_Pillar_flash0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Grimm Cln_Flame_Pillar_flash0000-Sheet2.png", 6, 1);

		GameEngineTexture::Cut("Grimm Cln_ground_dash_effect0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Grimmkin Cln_grimm_fireball0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Grimmkin Cln_grimm_fireball0000-Sheet2.png", 8, 1);
		GameEngineTexture::Cut("Grimmkin Cln_grimm_fireball_explode0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Grimm Cln_Grimm_ground_spike0000-Sheet.png", 14, 1);
		GameEngineTexture::Cut("Grimm Cln_air_dash_effects0000-Sheet.png", 1, 5);
		GameEngineTexture::Cut("Grimm Cln_ground_dash_effect0000-Sheet.png", 6, 1);

		GameEngineTexture::Cut("grimm_smoke.png", 1, 5);
		GameEngineTexture::Cut("grimm_smoke2.png", 1, 5);

		GameEngineTexture::Cut("Grimm_flame_ball_particle.png", 3, 1);

		GameEngineTexture::Cut("grimm_particle_flame.png", 9, 1);
		GameEngineTexture::Cut("grimm_particle_flame2.png", 9, 1);


		GameEngineTexture::Cut("white_hit_particle_Pink.png", 1, 3);

		GameEngineTexture::Cut("Grimmflame0000-Sheet.png", 14, 1);

	}

	//================================
	//    텍스처 / 맵 / KingsPass
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("KingsPass");
		Dir.Move("Grimm");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}

	//================================
	//    텍스처 / 맵 / KingsPass
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("Forgotten Crossroads");
		Dir.Move("Level1");

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
		Dir.Move("Forgotten Crossroads");
		Dir.Move("Level2");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}


	//================================
	//    텍스처 / 맵 / DirtmouthMap
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("Dirtmouth");
		Dir.Move("Level1");

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
		Dir.Move("Dirtmouth");
		Dir.Move("Level2");

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
		Dir.Move("Dirtmouth");
		Dir.Move("Level3");

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
		Dir.Move("Dirtmouth");
		Dir.Move("MapShop");

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
		Dir.Move("Dirtmouth");
		Dir.Move("SlyShop");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}



	//================================
	//    텍스처 / 맵 / Grimm
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("Dirtmouth");
		Dir.Move("Grimm");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}
	}



	//================================
	//    텍스처 / 오브젝트
	//================================
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");


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
		Dir.Move("Object");
		Dir.Move("Spike");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("spikes0000-Sheet.png", 4, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");
		Dir.Move("HealthBug");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Health Bugs_health_cocoon_top0000-Sheet.png", 23, 1);
		GameEngineTexture::Cut("Health Bugs_health_plant_010013-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Health Bugs_health_plant_020007-Sheet.png", 16, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");
		Dir.Move("door");
		Dir.Move("tu");


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
		Dir.Move("Object");
		Dir.Move("door");
		Dir.Move("Gate");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Switches and gates_gate_resize0000-Sheet.png", 6, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");
		Dir.Move("door");
		Dir.Move("Boss Door Cln");


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
		Dir.Move("Object");
		Dir.Move("lamp_bug");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}


		GameEngineTexture::Cut("shop_lamp_bug0000-Sheet.png", 8, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");
		Dir.Move("Grimm");


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
		Dir.Move("Object");
		Dir.Move("door");
		Dir.Move("Tute Great Door");


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
		Dir.Move("Object");
		Dir.Move("Amblent Life");


		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Ambient Life_cave_glow_bug0000-Sheet.png", 4, 1);

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Object");
		Dir.Move("Tablet");


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
		
		GameEngineTexture::Cut("Knight_idle_low_health000-Sheet.png", 10, 1);

		// 벽타기
		GameEngineTexture::Cut("Knight_wall_slide0000-Sheet.png", 4, 1);
		GameEngineTexture::Cut("Knight_wall_jump0000-Sheet.png", 3, 1);

		// 스턴
		GameEngineTexture::Cut("Knight_stun0000-Sheet.png", 5, 1);

		// 사망
		GameEngineTexture::Cut("Knight_death_anim0000-Sheet.png", 14, 1);
		GameEngineTexture::Cut("Knight_spike_death000-Sheet.png", 8, 1);

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
		GameEngineTexture::Cut("Knight_cast_v030002-Sheet.png", 12, 1);
		GameEngineTexture::Cut("Knight_scream_cast_lvl_020000-Sheet.png", 9, 1);

		// 땅에서 기상
		GameEngineTexture::Cut("Knight_wake_up_ground0000-Sheet.png", 5, 1);

		// 기상
		GameEngineTexture::Cut("Knight_wake_up_ground0000-Sheet.png", 21, 1);
		GameEngineTexture::Cut("Knight_wake0000-Sheet.png", 5, 1);
		GameEngineTexture::Cut("Knight Hatchling Cln_burst0000-Sheet.png", 6, 1);

		//의자
		GameEngineTexture::Cut("Knight_sit0000-Sheet.png", 5, 1);

		GameEngineTexture::Cut("Knight_into_door0000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Knight_cast0003-Sheet.png", 10, 1);
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");
		Dir.Move("Effect");
		Dir.Move("Spell");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("Spell Effects_focus_effect0000-Sheet.png", 9, 1);
		GameEngineTexture::Cut("Spell Effects_focus_appear0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Spell Effects_burst_effect0000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Spell Effects_burst0000-Sheet.png", 7, 1);

		GameEngineTexture::Cut("Spell Effects 2_double_jump_wings0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Spell Effects_blast_effect_v020000-Sheet.png", 8, 1);
		GameEngineTexture::Cut("Spell Effects_fireball_v020000-Sheet.png", 10, 1);
		GameEngineTexture::Cut("Spell Effects_fireball_wall_impact_effect0000-Sheet.png", 7, 1);
		GameEngineTexture::Cut("Spell Effects_sharp_flash0000-Sheet.png", 4, 1);

		GameEngineTexture::Cut("moth_feather_particle.png", 1, 3);

		GameEngineTexture::Cut("Spell Effects 2_scream_effect0000-Sheet.png", 13, 1);
		GameEngineTexture::Cut("Spell Effects Neutral_scream_blast_level_020000-Sheet.png", 13, 1);


	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");
		Dir.Move("Effect");
		Dir.Move("Particle");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("final_boss_glow_particle.png", 1, 3);
		//GameEngineTexture::Cut("Spell Effects_focus_appear0000-Sheet.png", 7, 1);
		//GameEngineTexture::Cut("Spell Effects_burst_effect0000-Sheet.png", 8, 1);


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


		GameEngineTexture::Cut("hit_crack_simple0000-Sheet.png", 3, 1);

		GameEngineTexture::Cut("Switches and gates_gate_effect0000-Sheet.png", 4, 1);

		//먼지
		GameEngineTexture::Cut("Dust Effects_jump_puff0001-Sheet.png", 4, 1);

		GameEngineTexture::Cut("Knight_dash_effect0000-Sheet.png", 8, 1);

		GameEngineTexture::Cut("Ambient Life_bug_glow0000-Sheet.png", 6, 1);
		GameEngineTexture::Cut("Ambient Life_bug_glow0000-Sheet2.png", 6, 1);
		GameEngineTexture::Cut("shop_lamp_bug0001-Sheet.png", 7, 1);

		GameEngineTexture::Cut("stun_impact_effect0000-Sheet.png", 7, 1);


	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("Kinght");
		Dir.Move("Effect");
		Dir.Move("Hit");

		std::vector<GameEngineFile> Texture = Dir.GetAllFile();

		for (size_t i = 0; i < Texture.size(); i++)
		{
			GameEngineTexture::Load(Texture[i].GetFullPath());
		}

		GameEngineTexture::Cut("white_hit_particle_Orange.png", 1, 3);
		GameEngineTexture::Cut("white_hit_particle.png", 1, 3);

		GameEngineTexture::Cut("Projectiles_shot_impact0001-Sheet.png", 7, 1);
		GameEngineTexture::Cut("orange_puff_animated.png", 10, 1);
	}


	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	//================================
	//    레벨 생성
	//================================
	CreateLevel<TitleLevel>("TitleLevel");

	CreateLevel<KingsPassLevel1>("KingsPassLevel1");
	CreateLevel<KingsPassLevel2>("KingsPassLevel2");
	CreateLevel<KingsPassLevel3>("KingsPassLevel3");
	CreateLevel<KingsPassLevel4>("KingsPassLevel4");

	CreateLevel<CrossroadsLevel1>("CrossroadsLevel1");

	CreateLevel<GrimmLevel>("GrimmmLevel");

	CreateLevel<FireballPromptLevel>("FireballPromptLevel");
	//CreateLevel<CrossroadsLevel2>("CrossroadsLevel2");
	CreateLevel<ScreamPromptLevel>("ScreamPromptLevel");


	CreateLevel<DirtmouthLevel1>("DirtmouthLevel1");
	CreateLevel<DirtmouthLevel2>("DirtmouthLevel2");

	CreateLevel<GrimmDirtmouthLevel1>("GrimmDirtmouthLevel1");
	CreateLevel<GrimmDirtmouthLevel2>("GrimmDirtmouthLevel2");

	CreateLevel<MapShopLevel>("MapShopLevel");
	CreateLevel<SlyShopLevel>("SlyShopLevel");

	CreateLevel<KingsPassGrimmOpenLevel>("KingsPassGrimmOpenLevel");

	

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