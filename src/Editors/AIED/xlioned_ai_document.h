namespace xlioned::ai
{
    class document : public xeditor::document::base
    {
        xcore_rtti(document, xeditor::document::base);

        constexpr static auto class_name_v = xcore::string::constant("xLion/Documents/AI");

    public:

                                                        document            ( xcore::string::constant<char> Str, xeditor::document::main& MainDoc ) noexcept;
        virtual       const xeditor::document::type&    getType             ( void )                                                        const   noexcept override;
                                auto&                   getLockedKeyData    ( void )                                                        const   noexcept        { return m_LockedKeyData; }

    protected:

        struct keydata
        {
            struct info
            {
                int                         m_LineOffsets;        // Index to lines offset
                std::uint16_t               m_FullLength;
                std::uint16_t               m_Length;
                std::uint8_t                m_MessageOffset;
                std::uint8_t                m_MsgOffset;
                std::uint8_t                m_FromSystemOffset;
                std::uint8_t                m_FromSystemLength;
                xcore::log::msg_type        m_MsgType;
            };

            ImGuiTextBuffer                     m_Buf;
            ImVector<info>                      m_Info;         // Index to lines offset
        };

        using keydata_locked = xcore::lock::object< keydata, xcore::lock::semaphore_reentrant >;

    protected:

        virtual                 xcore::err              onSave              ( void )                                                                override;
        virtual                 xcore::err              onLoad              ( void )                                                                override;
        virtual                 xcore::err              onNew               ( void )                                                                override;
        virtual                 xcore::err              onClose             ( void )                                                                override;
                                void                    msgNewLogMessage    ( const xcore::cstring& Str )                                           noexcept;

    protected:

        keydata_locked                                      m_LockedKeyData{};
        xeditor::document::main::events::log_msg::delegate  m_deletegateNewLogMessage{ this, &document::msgNewLogMessage };
    };
}
