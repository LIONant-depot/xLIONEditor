
namespace xlioned::ai {

//-------------------------------------------------------------------------------------------
static const xeditor::document::details::type_harness<document> s_TypeDoc{ document::class_name_v };

//--------------------------------------------------------------------------------

const xeditor::document::type& document::getType(void) const noexcept
{
    return s_TypeDoc;
}

//--------------------------------------------------------------------------------

document::document(xcore::string::constant<char> Str, xeditor::document::main& MainDoc) noexcept
    : xeditor::document::base(Str, MainDoc)
{
    m_deletegateNewLogMessage.Connect(MainDoc.m_Events.m_LogMsg);
}

//--------------------------------------------------------------------------------

xcore::err document::onSave(void) { return {}; }
xcore::err document::onNew(void) { return {}; }
xcore::err document::onClose(void) { return {}; }
xcore::err document::onLoad(void) { return {}; }

//--------------------------------------------------------------------------------

void document::msgNewLogMessage( const xcore::cstring& Str ) noexcept
{
    xcore::lock::scope Lk( m_LockedKeyData );

    auto& KeyData = m_LockedKeyData.get();
    auto old_size = KeyData.m_Buf.size();
    
    KeyData.m_Buf.append( Str );

    keydata::info Info;

    Info.m_LineOffsets = old_size;
    Info.m_Length  = Info.m_FullLength = static_cast<std::uint16_t>(KeyData.m_Buf.size() - old_size);

    if (auto Index = xcore::string::FindStr(Str, "[WARNING]"); Index >= 0)
    {
        Info.m_MsgType = xcore::log::msg_type::L_WARNING;
    }
    else if (auto Index = xcore::string::FindStr(Str, "[INFO]"); Index >= 0)
    {
        Info.m_MsgType = xcore::log::msg_type::L_INFO;
    }
    else if (auto Index = xcore::string::FindStr(Str, "[ERROR]"); Index >= 0)
    {
        Info.m_MsgType = xcore::log::msg_type::L_ERROR;
    }
    else
    {
        Info.m_MsgType = xcore::log::msg_type::L_INFO;
    }
    
    // From system
    Info.m_FromSystemOffset = xcore::string::FindStr( Str, "][" );
    if(Info.m_FromSystemOffset != - 1 ) 
    {
        Info.m_FromSystemOffset += 2;
        Info.m_FromSystemLength = xcore::string::FindStr(&Str[Info.m_FromSystemOffset], "][");

        int offset = Info.m_FromSystemOffset + Info.m_FromSystemLength + 2;
        Info.m_MessageOffset    = 2 + offset + xcore::string::FindStr(&Str[offset], "]");
    }

    // Update the length
    if( auto end = xcore::string::FindStr(Str, "- ("); end != -1 )
    {
        Info.m_Length = end;
    }


    KeyData.m_Info.push_back(Info);

/*
    for( int new_size = KeyData.m_Buf.size(); old_size < new_size; old_size++ )
    {
        if( KeyData.m_Buf[old_size] == '\n' )
        {
            keydata::info Info;

            Info.m_LineOffsets = old_size;
            
            if( auto Index = xcore::string::FindStr( Str, "[WARNING]" ); Index >= 0 )
            {
                Info.m_MsgType = xcore::log::msg_type::L_WARNING;
            }
            else if (auto Index = xcore::string::FindStr(Str, "[INFO]"); Index >= 0)
            {
                Info.m_MsgType = xcore::log::msg_type::L_INFO;
            }
            else if (auto Index = xcore::string::FindStr(Str, "[ERROR]"); Index >= 0)
            {
                Info.m_MsgType = xcore::log::msg_type::L_ERROR;
            }

            KeyData.m_Info.push_back(Info);
        }
    }
*/
}

} // namespace xlioned::sceneed
