
namespace xlioned::project {

    xeditor::panel::details::type_harness<panel> s_Type{ panel::class_name_v, xeditor::panel::type::flags{ .m_bDisplayOnEmptyProject = true, .m_bDisableChildDocking = true } };

    //-------------------------------------------------------------------------

    panel::panel( construct& Construct )
        : xeditor::panel::parent(Construct)
        , m_LogDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
    {
    }

    //-------------------------------------------------------------------------

    void panel::onCreateChildrenPanels(void)
    {
    }

    //-------------------------------------------------------------------------
    void panel::SettingsDependencies( void )
    {
        ImGui::Button("Import"); ImGui::SameLine();
        ImGui::Button("Create");
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
        ImGui::Button("Remove");
        // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        char Buffer[] = "Some path bla bla ";
        ImGui::Text("Path:");
        ImGui::InputText("##Project Path", Buffer, sizeof(Buffer), ImGuiInputTextFlags_ReadOnly);
        ImGui::NewLine();


        ImGui::TextWrapped("Project Path: something something ");

        ImGui::EndGroup();
    }

    void panel::SettingsGeneral()
    {
        ImGui::Text("Project Path:");
        char Buffer[] = "Some path bla bla ";
        ImGui::InputText("##2Project Path", Buffer, sizeof(Buffer), ImGuiInputTextFlags_ReadOnly);
    }

    void panel::SettingsEnviroment()
    {
        ImGui::Text("Project Path:");
        char Buffer[] = "Some path bla bla ";
        ImGui::InputText("##2Project Path", Buffer, sizeof(Buffer), ImGuiInputTextFlags_ReadOnly);
    }

    void panel::SettingsAI()
    {
        ImGui::Text("Project Path:");
        char Buffer[] = "Some path bla bla ";
        ImGui::InputText("##2Project Path", Buffer, sizeof(Buffer), ImGuiInputTextFlags_ReadOnly);
    }

    void panel::SettingsPlugins()
    {
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
                static int selected = 0;

                ImGui::BeginChild("setting options", ImVec2(300, -1), true);
                if (ImGui::BeginTable("setting options table", 1, ImGuiTableFlags_RowBg))
                {
                    for (int i = 0; i < SettingOptions.size(); i++)
                    {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 1; column++)
                        {
                            ImGui::TableSetColumnIndex(column);

                            if( ImGui::Selectable( SettingOptions[i].first, selected == i ) )
                                selected = i;
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndChild();
                ImGui::SameLine();

                // Call the right option to display
                ImGui::BeginGroup();
                std::invoke(SettingOptions[selected].second, this);
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