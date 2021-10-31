namespace xlioned::project
{
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
    };
}
