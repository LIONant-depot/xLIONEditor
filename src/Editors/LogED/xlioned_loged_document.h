namespace xlioned::loged
{
    class document : public xeditor::document::base
    {
        xcore_rtti(document, xeditor::document::base);

        constexpr static auto class_name_v = xcore::string::constant("xLion/Documents/Log");

    public:

        using base::base;

        struct keydata
        {
            ImGuiTextBuffer                     m_Buf;
            ImVector<int>                       m_LineOffsets;        // Index to lines offset
        };

        using keydata_locked = xcore::lock::object< keydata, xcore::lock::semaphore_reentrant >;

    public:

                                                        document            ( xcore::string::constant<char> Str, xeditor::document::main& MainDoc ) noexcept;
                                void                    Clear               ( void )                                                                noexcept;
                                auto&                   getLockedKeyData    ( void )                                                        const   noexcept        { return m_LockedKeyData; }
        virtual       const xeditor::document::type&    getType             ( void )                                                        const   noexcept override;

    protected:

        virtual                 xcore::err              onSave              ( void )                                                                override;
        virtual                 xcore::err              onLoad              ( void )                                                                override;
        virtual                 xcore::err              onNew               ( void )                                                                override { return {}; }
        virtual                 xcore::err              onClose             ( void )                                                                override;
                                void                    msgNewLogMessage    ( const xcore::cstring& Str )                                           noexcept;

    protected:

        keydata_locked                                      m_LockedKeyData             {};
        xeditor::document::main::events::log_msg::delegate  m_deletegateNewLogMessage   { this, &document::msgNewLogMessage };
    };
}
