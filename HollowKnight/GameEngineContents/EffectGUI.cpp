#include "PreCompile.h"
#include "EffectGUI.h"

ImVec4 EffectGUI::Overlaycolor = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

EffectGUI::EffectGUI() 
	:
    OverlayFlag_(false),
	alpha_half_preview(true),
	drag_and_drop(true),
	options_menu(true),
	hdr(true)
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


}

void EffectGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	//Overlaycolor = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
	ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (OverlayFlag_ ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
	
	ImGui::Text("Overlay Color");
	ImGui::ColorEdit4("Overlay Color##2f", (float*)&Overlaycolor, ImGuiColorEditFlags_Float | misc_flags);

    // Generate a default palette. The palette will persist and can be edited.
    static bool saved_palette_init = true;
    static ImVec4 saved_palette[32] = {};
    if (saved_palette_init)
    {
        for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
        {
            ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
                saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
            saved_palette[n].w = 1.0f; // Alpha
        }
        saved_palette_init = false;
    }

    ImGui::Checkbox("OverlayFlag", &OverlayFlag_);

	 static ImVec4 backup_color;

     bool open_popup = ImGui::ColorButton("MyColor##3b", Overlaycolor, misc_flags);
     ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
     open_popup |= ImGui::Button("Palette");
     if (open_popup)
     {
         ImGui::OpenPopup("mypicker");
         backup_color = Overlaycolor;
     }
     if (ImGui::BeginPopup("mypicker"))
     {
         ImGui::Text("Save Overlay Color");
         ImGui::Separator();
         ImGui::ColorPicker4("##picker", (float*)&Overlaycolor, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
         ImGui::SameLine();

         ImGui::BeginGroup(); // Lock X position
         ImGui::Text("Current");
         ImGui::ColorButton("##current", Overlaycolor, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
         ImGui::Text("Previous");
         if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
             Overlaycolor = backup_color;
         ImGui::Separator();
         ImGui::Text("Palette");
         for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
         {
             ImGui::PushID(n);
             if ((n % 8) != 0)
                 ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

             ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
             if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
                 Overlaycolor = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, Overlaycolor.w); // Preserve alpha!

             // Allow user to drop colors into each palette entry. Note that ColorButton() is already a
             // drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
             if (ImGui::BeginDragDropTarget())
             {
                 if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                     memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                 if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                     memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                 ImGui::EndDragDropTarget();
             }

             ImGui::PopID();
         }
         ImGui::EndGroup();
         ImGui::EndPopup();
     }

}

