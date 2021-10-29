
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
        ImGui::BeginChild( "Menu", {25*4, 35}, true, ImGuiWindowFlags_NoScrollbar );
     //   ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (float)5);
     //   ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (float)3);
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