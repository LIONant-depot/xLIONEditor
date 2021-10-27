namespace xlioned::loged
{
    class panel : public xeditor::panel::base
    {
        xcore_rtti(panel, xeditor::panel::base);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " Log");
    
    public:

                                                        panel           ( xcore::string::constant<char> Str, xeditor::panel::instance_guid Guid, xeditor::frame& EditorFrame );

    protected:

        enum class open_popup : std::uint8_t
        { NONE
        , MAIN_MENU
        , COPY_LOG_TO_CLIPBOARD
        };


    protected:

                        void                            msgHandleLog    ( xcore::cstring& Str );
        virtual         const xeditor::panel::type&     getType         ( void ) override;
        virtual         void                            onRender        ( void ) override;

    protected:

        document&                           m_LogDoc;
        ImGuiTextFilter                     m_Filter        {};
        int                                 m_LastLineCount { 0 };
    };
}
