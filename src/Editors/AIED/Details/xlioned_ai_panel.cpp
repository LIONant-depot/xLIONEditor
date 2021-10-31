
#include <imgui_internal.h>

namespace xlioned::ai {

    xeditor::panel::details::type_harness<panel> s_Type{ panel::class_name_v, xeditor::panel::type::flags{ .m_bDisplayOnEmptyProject = true, .m_bDisableChildDocking = true } };

    //-------------------------------------------------------------------------

    panel::panel( construct& Construct )
        : xeditor::panel::parent(Construct)
        , m_AIDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
    {
    }

    //-------------------------------------------------------------------------

    void panel::onCreateChildrenPanels(void)
    {
    }

    //-------------------------------------------------------------------------

    int panel::TextEditCallback(ImGuiInputTextCallbackData* pData)
    {
        switch (pData->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
        break;
        case ImGuiInputTextFlags_CallbackHistory:
        break;
        }

        return 0;
    }

    //-------------------------------------------------------------------------

    void panel::onRender(void)
    {
        //
        // Display the messages at the top
        //
        {
            xcore::lock::scope Lk(std::as_const(m_AIDoc.getLockedKeyData()));
            auto& KeyData = m_AIDoc.getLockedKeyData().get();

            const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
            ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_NoScrollbar);//ImGuiWindowFlags_HorizontalScrollbar);

            static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

            int Index = 0;
            int iType = -1;

            if (ImGui::BeginTable("3ways", 2, flags))
            {
                ImGui::TableSetupScrollFreeze(2, 1);
                ImGui::TableSetupColumn("Name",     ImGuiTableColumnFlags_NoHide );//ImGuiTableColumnFlags_NoHide);
                ImGui::TableSetupColumn("Message", ImGuiTableColumnFlags_WidthStretch);//ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
                ImGui::TableHeadersRow();

                int Open = 0;
                for( auto& E : KeyData.m_Info )
                {
                    DO_DETAILS:
                    ImGui::TableNextRow();
                    for( int c=0; c<2; c++ )
                    {
                        ImGui::TableNextColumn();

                        if(c==0 && Open == 0 )
                        {
                            if (iType != (int)E.m_MsgType)
                            {
                                if (iType != -1) ImGui::PopStyleColor();
                                iType = (int)E.m_MsgType;

                                switch (E.m_MsgType)
                                {
                                case xcore::log::msg_type::L_INFO:      ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]); break;
                                case xcore::log::msg_type::L_ERROR:     ImGui::PushStyleColor(ImGuiCol_Text, ImU32(0xff0000ffu)); break;
                                case xcore::log::msg_type::L_WARNING:   ImGui::PushStyleColor(ImGuiCol_Text, ImU32(0xff00ffffu)); break;
                                }
                            }
                            
                            Open = ImGui::TreeNodeBehavior
                            ( 1000 + Index++
                            , ImGuiTreeNodeFlags_SpanFullWidth
                            , KeyData.m_Buf.begin() + E.m_LineOffsets + E.m_FromSystemOffset
                            , KeyData.m_Buf.begin() + E.m_LineOffsets + E.m_FromSystemOffset + E.m_FromSystemLength
                            )?1:0;
                        }
                        else if(c==1 && Open <= 1 )
                        {
                            // Render text with wrap
                            ImGui::PushTextWrapPos(0.0f);
                            ImGui::TextEx
                            (KeyData.m_Buf.begin() + E.m_LineOffsets + E.m_MessageOffset
                                , KeyData.m_Buf.begin() + E.m_LineOffsets + E.m_Length
                                , ImGuiTextFlags_NoWidthForLargeClippedText
                            );
                            ImGui::PopTextWrapPos();
                        }
                        else if (c == 1 && Open > 1 )
                        {
                            ImGui::PushTextWrapPos(0.0f);
                            ImGui::TextEx
                            (KeyData.m_Buf.begin() + E.m_LineOffsets
                                , KeyData.m_Buf.begin() + E.m_LineOffsets + E.m_FullLength
                                , ImGuiTextFlags_NoWidthForLargeClippedText
                            );
                            ImGui::PopTextWrapPos();
                            Open = 0;
                            ImGui::TreePop();
                        }
                    }
                    if (Open)
                    {
                        Open++;
                        goto DO_DETAILS;
                    }
                }

                if (iType != -1) ImGui::PopStyleColor();

                if (m_bScrollToBottom || (m_bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                    ImGui::SetScrollHereY(1.0f);
                m_bScrollToBottom = false;
             }

            ImGui::EndTable();
            ImGui::EndChild();
        }
    //    ImGui::Separator();

        //
        // Handle the input
        //
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        if( ImGui::InputText
                ( "Input"
                , m_InputBuf.data()
                , m_InputBuf.size()
                , input_text_flags
                , [](ImGuiInputTextCallbackData* pData )
                {
                    panel* pThis = (panel*)pData->UserData;
                    return pThis->TextEditCallback(pData);
                }
                , (void*)this)
           )
        {
            // Remove trailing spaces
            [](char* s)
            {   char* str_end = s + std::strlen(s); 
                while (str_end > s && str_end[-1] == ' ') str_end--;
                *str_end = 0; 
            }(m_InputBuf.data());

            m_bScrollToBottom = true;

            // If we still have some content lets send the command
            if( m_InputBuf[0] )
            {
                m_AIDoc.ExecuteCommand( m_InputBuf.data() );
                m_InputBuf[0] = 0;
            }

            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
    }
}