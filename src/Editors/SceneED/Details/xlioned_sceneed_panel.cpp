
#include "Explorer/xlioned_sceneed_explorer.h"
#include "Properties/xlioned_sceneed_properties.h"

namespace xlioned::sceneed {

    xeditor::panel::details::type_harness<panel, explorer::panel, properties::panel> s_Type{ panel::class_name_v, xeditor::panel::type::flags{ .m_bDisplayOnEmptyProject = true } };

    //-------------------------------------------------------------------------

    panel::panel( construct& Construct )
        : xeditor::panel::parent(Construct)
        , m_LogDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
    {
    }

    //-------------------------------------------------------------------------

    void panel::onCreateChildrenPanels(void)
    {
        (void)parent::CreateTab( "Explorer" );
        (void)parent::CreateTab("Properties");
    }

    //-------------------------------------------------------------------------

    void panel::onRender(void)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        SetNextWindowPosRelativeToCenterDock(position_type::TOP_MIDDLE, { 0,2 });

        float h =      ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f  + ImGui::GetStyle().WindowPadding.y * 2.0f;
        float x = 4 * (ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.x * 2.0f) + ImGui::GetStyle().WindowPadding.x * 2.0f;
        ImGui::BeginChild( "Menu", { x, h }, true, ImGuiWindowFlags_NoScrollbar );

        ImGui::Button("X");

        ImGui::SameLine();
        ImGui::Button("X");

        ImGui::SameLine();
        ImGui::Button("X");

        ImGui::SameLine();
        ImGui::Button("X");

        ImGui::PopStyleVar();
        ImGui::EndChild();
    }
}