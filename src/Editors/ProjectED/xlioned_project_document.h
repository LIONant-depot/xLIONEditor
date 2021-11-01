namespace xlioned::project
{
    struct general_settings
    {
        xcore::cstring m_ProjectPath;
        xcore::cstring m_WebAddressPath;
        xcore::cstring m_ResourcePath;
        xcore::cstring m_AssetPath;

        // Project GUID
    };

    struct source_control
    {
        xcore::cstring m_WebAddressPath;
    };

    struct user_settings
    {
        xcore::cstring m_UserName;
        xcore::cstring m_GitUser;
    };

    struct enviroment_folders
    {
        xcore::cstring m_ResourcePath;
        xcore::cstring m_AssetPath;
    };

    class document : public xeditor::document::base
    {
        xcore_rtti(document, xeditor::document::base);

        constexpr static auto class_name_v = xcore::string::constant("xLion/Documents/Project");

    public:

                                                        document            ( xcore::string::constant<char> Str, xeditor::document::main& MainDoc ) noexcept;
        virtual       const xeditor::document::type&    getType             ( void )                                                        const   noexcept override;

    protected:

        virtual                 xcore::err              onSave              ( void )                                                                override;
        virtual                 xcore::err              onLoad              ( void )                                                                override;
        virtual                 xcore::err              onNew               ( void )                                                                override;
        virtual                 xcore::err              onClose             ( void )                                                                override;
 //                               void                    msgNewLogMessage    ( const xcore::cstring& Str )                                           noexcept;

    protected:

 //       xeditor::document::main::events::log_msg::delegate  m_deletegateNewLogMessage   { this, &document::msgNewLogMessage };


        general_settings    m_GeneralSettings{};
        source_control      m_SourceControl{};
        user_settings       m_UserSettings{};
        enviroment_folders  m_EnviromentFolders{};

        friend class panel;
    };
}

property_begin_name(xlioned::project::general_settings, "General Settings")
{
    property_var(m_ProjectPath)
        .Flags( property::flags::SHOW_READONLY )
,   property_var(m_WebAddressPath)
}
property_end();

property_begin_name(xlioned::project::source_control, "Source Control")
{
    property_var(m_WebAddressPath)
}
property_end();

property_begin_name(xlioned::project::user_settings, "User Settings")
{
    property_var(m_UserName)
,   property_var(m_GitUser)
}
property_end();

property_begin_name(xlioned::project::enviroment_folders, "Enviroment Folders")
{
    property_var(m_ResourcePath)
,   property_var(m_AssetPath)
}
property_end();
