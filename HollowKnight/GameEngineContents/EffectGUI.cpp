#include "PreCompile.h"
#include "EffectGUI.h"

//ImVec4 EffectGUI::Overlaycolor = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
//ImVec4 EffectGUI::saved_palette[32] = {};

EffectGUI::EffectGUI() 
	:
    isBlendClick_(false),

    overlay_flag(true),
    isMainLightOnOff_(true),
    isSiblingLightOnOff_(true),
    isDonutLightOnOff_(true),

    MainLightitemsCurrent(0),
    SiblingLightitemsCurrent(0),
    DonutLightitemsCurrent(0),

    Overlaycolor({ 0.499f, 0.592f, 0.726f, 1.0f }),

    MainLightMulColor_(),
    MainLightPlusColor_(),

    SlibingLightMulColor_(),
    SlibingLightPlusColor_(),

    DounutLightMulColor_(),
    DounutLightPlusColor_()


{



}

EffectGUI::~EffectGUI() 
{
}

void EffectGUI::Initialize(GameEngineLevel* _Level)
{
	//Overlaycolor = KnightData::GetInst()->GetOverlayColor();

    Overlaycolor.x = KnightData::GetInst()->GetOverlayColor().x;
    Overlaycolor.y = KnightData::GetInst()->GetOverlayColor().y;
    Overlaycolor.z = KnightData::GetInst()->GetOverlayColor().z;
    Overlaycolor.w = KnightData::GetInst()->GetOverlayColor().w;

    overlay_flag = KnightData::GetInst()->GetOverlayFlag();

    //Overlaycolor = KnightData::GetInst()->GetOverlayColor();
    Overlaycolor = ConvertFromFloat4(Overlaycolor, KnightData::GetInst()->GetOverlayColor());

    MainLightMulColor_= ConvertFromFloat4(MainLightMulColor_, KnightData::GetInst()->GetKnihgtMainLightMulColor());
    MainLightPlusColor_ = ConvertFromFloat4(MainLightPlusColor_, KnightData::GetInst()->GetKnihgtMainLightPlusColor());

    SlibingLightMulColor_ = ConvertFromFloat4(SlibingLightMulColor_, KnightData::GetInst()->GetKnihgtSlibingLightMulColor());
    SlibingLightPlusColor_ = ConvertFromFloat4(SlibingLightPlusColor_, KnightData::GetInst()->GetKnihgtSlibingLightPlusColor());


    DounutLightMulColor_ = ConvertFromFloat4(DounutLightMulColor_, KnightData::GetInst()->GetKnihgtDounutLightMulColor());
    DounutLightPlusColor_ = ConvertFromFloat4(DounutLightPlusColor_, KnightData::GetInst()->GetKnihgtDounutLightPlusColor());

    //MainLightitemsCurrent = static_cast<int>(KnightData::GetInst()->GetMainLightBlend());
    //SiblingLightitemsCurrent = static_cast<int>(KnightData::GetInst()->GetSlibingLightBlend());
    //DonutLightitemsCurrent = static_cast<int>(KnightData::GetInst()->GetDounutLightBlend());



  //saved_palette_init = KnightData::GetInst()->GetSavedPaletteInit();

}

void EffectGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	//Overlaycolor = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
    ImGui::Text("PostEffect");
	ImGuiColorEditFlags misc_flags = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);

	ImGui::Text("Overlay Color");
	ImGui::ColorEdit4("Overlay Color##2f", (float*)&Overlaycolor, ImGuiColorEditFlags_Float | misc_flags);

    if (ImGui::Button("overlay Reset"))
    {
        Overlaycolor = { 0.499, 0.592, 0.726, 1.0f };
    }


    ImGui::Checkbox("OverlayFlag", &overlay_flag);

    ImGui::Separator();

    ImGui::Text("KihgtMainLight");

    //const char* items[] = { "Alpha", "Overlay", "Lighten", "Multply", "Add", "Darken" };
    
      
    //ImGui::Combo("MainLight_Blend", &MainLightitemsCurrent, items, IM_ARRAYSIZE(items));

    //ImGui::SliderFloat4("MainLightMulColor", (float*)&MainLightMulColor_, 0.0f, 1.0f);

    ImGuiColorEditFlags MainLightMulColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("MainLightMulColor##2f", (float*)&MainLightMulColor_, ImGuiColorEditFlags_Float | MainLightMulColor);

    ImGuiColorEditFlags MainLightPlusColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("MainLightPlusColor##2f", (float*)&MainLightPlusColor_, ImGuiColorEditFlags_Float | MainLightPlusColor);
    if (ImGui::Button("Reset MainLight"))
    {
        MainLightMulColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
        MainLightPlusColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    if (ImGui::Button("OnOff MainLight"))
    {
        isMainLightOnOff_ = !isMainLightOnOff_;
    }


    ImGui::Separator();
    ImGui::Text("SiblingLight");

    ImGuiColorEditFlags SiblingLightMulColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("SiblingLightMulColor##2f", (float*)&SlibingLightMulColor_, ImGuiColorEditFlags_Float | SiblingLightMulColor);

    ImGuiColorEditFlags SiblingLightPlusColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("SlibingLightPlusColor##2f", (float*)&SlibingLightPlusColor_, ImGuiColorEditFlags_Float | SiblingLightPlusColor);
   
    if (ImGui::Button("Reset SlibingLight"))
    {
        SlibingLightMulColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
        SlibingLightPlusColor_ = { 0.348f, 0.564f, 0.653f, 0.0f };
    }

    if (ImGui::Button("OnOff SlibingLight"))
    {
        isSiblingLightOnOff_ = !isSiblingLightOnOff_;
    }

    ImGui::Separator();  
    ImGui::Text("DonutLight");

    ImGuiColorEditFlags DonutLightMulColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("DonutLightMulColor##2f", (float*)&DounutLightMulColor_, ImGuiColorEditFlags_Float | DonutLightMulColor);

    ImGuiColorEditFlags DounutLightPlusColor = (true ? ImGuiColorEditFlags_HDR : 0) | (true ? 0 : ImGuiColorEditFlags_NoDragDrop) | (true ? ImGuiColorEditFlags_AlphaPreviewHalf : (false ? ImGuiColorEditFlags_AlphaPreview : 0)) | (true ? 0 : ImGuiColorEditFlags_NoOptions);
    ImGui::ColorEdit4("DounutLightPlusColor##2f", (float*)&DounutLightPlusColor_, ImGuiColorEditFlags_Float | DounutLightPlusColor);
   
    if (ImGui::Button("Reset DonutLight"))
    {
        DounutLightMulColor_ = { 1.0f, 1.0f, 1.0f, 0.3f };
        DounutLightPlusColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    if (ImGui::Button("OnOff DonutLight"))
    {
        isDonutLightOnOff_ = !isDonutLightOnOff_;
    }

    ImGui::Separator();

    if (ImGui::Button("Recommend Setting"))
    {
        MainLightMulColor_ = { 0.354f, 0.446f, 0.474f, 1.053f };
        MainLightPlusColor_ = { 0.0f, 0.0f, 0.078f, 0.0f };

        SlibingLightMulColor_ = { 1.0f, 1.0f, 1.0f, 0.384f };
        SlibingLightPlusColor_ = { 0.348f, 0.564f, 0.653f, 0.0f };

        DounutLightMulColor_ = { 1.0f, 1.0f, 1.0f, 0.102f };
        DounutLightPlusColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };

        Overlaycolor = { 0.499, 0.592, 0.726, 1.0f };
    }

    if (ImGui::Button("Recommend Setting2"))
    {
        MainLightMulColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
        MainLightPlusColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };

        SlibingLightMulColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
        SlibingLightPlusColor_ = { 0.348f, 0.564f, 0.653f, 0.0f };

        DounutLightMulColor_ = { 1.0f, 1.0f, 1.0f, 0.4f };
        DounutLightPlusColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };

        Overlaycolor = {0.406, 0.539, 0.730, 1.0f };
    }
}

