
namespace xlioned::project {

    xeditor::panel::details::type_harness<panel> s_Type{ panel::class_name_v, xeditor::panel::type::flags{ .m_bDisplayOnEmptyProject = true, .m_bDisableChildDocking = true } };

    //-------------------------------------------------------------------------

    panel::panel( construct& Construct )
        : xeditor::panel::parent(Construct)
        , m_ProjectDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
        , m_Inspector("Properties", false)
    {
    }

    //-------------------------------------------------------------------------

    void panel::onCreateChildrenPanels(void)
    {
    }

    //-------------------------------------------------------------------------
    void panel::SettingsDependencies(bool bFirstTime)
    {
        if (bFirstTime)
        {
            m_Inspector.clear();
            m_Inspector.AppendEntity();
            m_Inspector.AppendEntityComponent(m_Inspector.getPropertyVTable(), &m_Inspector);
        }

        ImGui::Button("Import"); ImGui::SameLine();
        ImGui::Button("Create"); ImGui::SameLine();
        ImGui::Button("Remove");
        static int selected = 0;
        {
            ImGui::BeginChild("left pane", ImVec2(350, 0), true);

            if (ImGui::BeginTable("table1", 1, ImGuiTableFlags_RowBg))
            {
                for (int i = 0; i < 10; i++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 1; column++)
                    {
                        ImGui::TableSetColumnIndex(column);

                        char label[128];
                        sprintf_s(label, 128, "MyObject %d \n12/4/32", i);
                        if (ImGui::Selectable(label, selected == i))
                            selected = i;
                    }
                }
                ImGui::EndTable();
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        ImGui::BeginGroup();
        
        ImGui::BeginChild("SettingsDependenciesProperties", ImVec2(-1, -1), false);
        m_Inspector.ShowNoWindow();
        ImGui::EndChild();

        ImGui::EndGroup();
    }

    void panel::SettingsGeneral(bool bFirstTime)
    {
        if( bFirstTime )
        {
            m_Inspector.clear();
            m_Inspector.AppendEntity();
            m_Inspector.AppendEntityComponent( xcore::property::getTable(m_ProjectDoc.m_GeneralSettings), &m_ProjectDoc.m_GeneralSettings );
            m_Inspector.AppendEntityComponent(xcore::property::getTable(m_ProjectDoc.m_SourceControl), &m_ProjectDoc.m_SourceControl);
        }

        ImGui::BeginChild("SettingsGeneralProperties", ImVec2(-1, -1), false);
        m_Inspector.ShowNoWindow();
        ImGui::EndChild();
    }

    void panel::SettingsEnviroment(bool bFirstTime)
    {
        if (bFirstTime)
        {
            m_Inspector.clear();
            m_Inspector.AppendEntity();
            m_Inspector.AppendEntityComponent(xcore::property::getTable(m_ProjectDoc.m_SourceControl), &m_ProjectDoc.m_SourceControl);
            m_Inspector.AppendEntityComponent(xcore::property::getTable(m_ProjectDoc.m_UserSettings), &m_ProjectDoc.m_UserSettings);
            m_Inspector.AppendEntityComponent(xcore::property::getTable(m_ProjectDoc.m_EnviromentFolders), &m_ProjectDoc.m_EnviromentFolders);
        }

        ImGui::BeginChild("SettingsEnviromentProperties", ImVec2(-1, -1), false);
        m_Inspector.ShowNoWindow();
        ImGui::EndChild();
    }

    void panel::SettingsAI(bool bFirstTime)
    {
        if (bFirstTime)
        {
            m_Inspector.clear();
            m_Inspector.AppendEntity();
            m_Inspector.AppendEntityComponent(m_Inspector.getPropertyVTable(), &m_Inspector);
        }

        ImGui::BeginChild("SettingsAIProperties", ImVec2(-1, -1), false);
        m_Inspector.ShowNoWindow();
        ImGui::EndChild();
    }

    void panel::SettingsPlugins(bool bFirstTime)
    {
        if (bFirstTime)
        {
            m_Inspector.clear();
            m_Inspector.AppendEntity();
            m_Inspector.AppendEntityComponent(m_Inspector.getPropertyVTable(), &m_Inspector);
        }

        ImGui::Text("Plugins:");
        ImGui::BeginChild("left pane", ImVec2(-1, -1), true);
        if (ImGui::BeginTable("table1", 1, ImGuiTableFlags_RowBg))
        {
            static int selected = 0;
            for (int i = 0; i < 10; i++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 1; column++)
                {
                    ImGui::TableSetColumnIndex(column);

                    char label[128];
                    sprintf_s(label, 128, "MyObject %d \n12/4/32", i);
                    if (ImGui::Selectable(label))
                        selected = i;
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndChild();
    }

    //-------------------------------------------------------------------------

    void panel::onRender(void)
    {
        ImGui::BeginChild("item222", ImVec2(-1, 50)); // Leave room for 1 line below us
        ImGui::Button("Save"); ImGui::SameLine();
        ImGui::Button("Close"); ImGui::SameLine();
        ImGui::Text("Project Name Here");
        ImGui::Separator();
        ImGui::EndChild();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Settings"))
            {
                constexpr static auto SettingOptions = std::array
                { std::pair{ "General",      &panel::SettingsGeneral        }
                , std::pair{ "AI",           &panel::SettingsAI             }
                , std::pair{ "Enviroment",   &panel::SettingsEnviroment     }
                , std::pair{ "Dependencies", &panel::SettingsDependencies   }
                , std::pair{ "Plugins",      &panel::SettingsPlugins        }
                };

                const auto PreviousSelected = m_SelectedMenu;
                ImGui::BeginChild("setting options", ImVec2(300, -1), true);
                if (ImGui::BeginTable("setting options table", 1, ImGuiTableFlags_RowBg))
                {
                    for (int i = 0; i < SettingOptions.size(); i++)
                    {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 1; column++)
                        {
                            ImGui::TableSetColumnIndex(column);

                            if( ImGui::Selectable( SettingOptions[i].first, m_SelectedMenu == i ) )
                                m_SelectedMenu = i;
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndChild();
                ImGui::SameLine();

                 

                // Call the right option to display
                ImGui::BeginGroup();
                if( m_SelectedMenu == -1 ) m_SelectedMenu = 0;
                std::invoke(SettingOptions[m_SelectedMenu].second, this, PreviousSelected != m_SelectedMenu );
                ImGui::EndGroup();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("New Project"))
            {
                ImGui::Button("Load"); ImGui::SameLine();
                ImGui::Button("Create"); 

                ImGui::Text("Recent Projects:");
                ImGui::BeginChild("left pane", ImVec2(-1, -1), true);
                if (ImGui::BeginTable("table1", 1, ImGuiTableFlags_RowBg))
                {
                    static int selected = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 1; column++)
                        {
                            ImGui::TableSetColumnIndex(column);

                            char label[128];
                            sprintf_s(label, 128, "MyObject %d \n12/4/32", i);
                            if (ImGui::Selectable(label))
                                selected = i;
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndChild();

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
}