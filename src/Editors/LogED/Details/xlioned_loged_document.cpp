namespace xlioned::loged {

//-------------------------------------------------------------------------------------------
static const xeditor::document::details::type_harness<xlioned::loged::document> s_TypeDoc{ xlioned::loged::document::class_name_v };
    
//-------------------------------------------------------------------------------------------

const xeditor::document::type& document::getType( void ) const noexcept
{ 
    return s_TypeDoc;  
}

//-------------------------------------------------------------------------------------------

document::document( const xcore::string::constant<char> Str, xeditor::document::main& MainDoc ) noexcept
    : xeditor::document::base{ Str, MainDoc }
{
    m_deletegateNewLogMessage.Connect( MainDoc.m_Events.m_LogMsg );
}

//-------------------------------------------------------------------------------------------

void document::Clear( void ) noexcept   
{
    xcore::lock::scope Lk(m_LockedKeyData);
    auto& KeyData = m_LockedKeyData.get();
    KeyData.m_Buf.clear();
    KeyData.m_LineOffsets.clear(); 
}

//-------------------------------------------------------------------------------------------

xcore::err document::onSave( void )
{
    return {};
}

//-------------------------------------------------------------------------------------------

xcore::err document::onLoad( void )
{
    return {};
}

//-------------------------------------------------------------------------------------------

xcore::err document::onClose( void )
{
    return {};
}

//-------------------------------------------------------------------------------------------

void document::msgNewLogMessage( const xcore::cstring& Str ) noexcept
{
    xcore::lock::scope Lk( m_LockedKeyData );

    auto& KeyData = m_LockedKeyData.get();
    auto old_size = KeyData.m_Buf.size();
    
    KeyData.m_Buf.append( Str );

    for( int new_size = KeyData.m_Buf.size(); old_size < new_size; old_size++ )
    {
        if( KeyData.m_Buf[old_size] == '\n' )
            KeyData.m_LineOffsets.push_back(old_size);
    }
}

} // namespace xeditor::document