namespace xlioned::loged {

static const xeditor::panel::details::type_harness<panel> s_Type
{ panel::class_name_v
, xeditor::panel::type::flags{ .m_bDisplayOnEmptyProject = true, .m_bDisableChildDocking = true }
};    

//-------------------------------------------------------------------------------------------

panel::panel( construct& Construct )
    : xeditor::panel::parent{ Construct }
    , m_LogDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
{
}

//-------------------------------------------------------------------------------------------

void panel::onRender( void )
{
    open_popup WhichPopupToOpen = open_popup::NONE;

    //
    // Main menu
    //
    if( ImGui::Button( ICON_FA_ARROW_CIRCLE_DOWN ) ) // "Menu"
    {
    }

    //
    // Clear the log
    // This needs to be done before the lock
    ImGui::SameLine(); if( ImGui::Button( "Reset Log" ) )
    {
        m_LogDoc.Clear();
    }
    
    //
    // Lock data here
    //
    xcore::lock::scope Lk( std::as_const(m_LogDoc.getLockedKeyData()) );

    auto& KeyData = m_LogDoc.getLockedKeyData().get();

    ImGui::SameLine(); if( ImGui::Button( ICON_FA_CLIPBOARD ) )
    {
        WhichPopupToOpen = open_popup::COPY_LOG_TO_CLIPBOARD;
    }

    ImGui::SameLine(); if( ImGui::Button( ICON_FA_TIMES ) )
    {
        m_Filter.Clear();
    }

    ImGui::SameLine(); m_Filter.Draw(ICON_FA_SEARCH, -24.0f);
    ImGui::Separator();


    ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if( WhichPopupToOpen == open_popup::COPY_LOG_TO_CLIPBOARD )
    {
        ImGui::LogToClipboard();
    }

    if( m_Filter.IsActive() )
    {
        const char* buf_begin   = KeyData.m_Buf.begin();
        const char* line        = buf_begin;

        for( int line_no = 0; line != nullptr; line_no++ )
        {
            const char* line_end = (line_no < KeyData.m_LineOffsets.Size) ? buf_begin + KeyData.m_LineOffsets[line_no] : nullptr;

            if( m_Filter.PassFilter(line, line_end) )
            {
                ImGui::TextUnformatted(line, line_end);
            }

            line = line_end && line_end[1] ? line_end + 1 : nullptr;
        }
    }
    else
    {
        ImGui::TextUnformatted( KeyData.m_Buf.begin() );
    }

    //
    // Scroll down to the last line when new data comes in
    //
    if( m_LastLineCount != KeyData.m_LineOffsets.Size )
    {
        ImGui::SetScrollHereY(1.0f);
        m_LastLineCount = KeyData.m_LineOffsets.Size;
    }

    ImGui::EndChild();
}

} // namespace xlioned::loged

