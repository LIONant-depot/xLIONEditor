namespace xlioned::loged
{
    class tab : public xeditor::tab::base
    {
        xcore_rtti(tab, xeditor::tab::base);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " Log");
    
    public:

                                            tab             ( xcore::string::constant<char> Str, xeditor::tab::instance_guid Guid, xeditor::frame::base& EditorFrame );

    protected:

        enum class open_popup : std::uint8_t
        { NONE
        , MAIN_MENU
        , COPY_LOG_TO_CLIPBOARD
        };


    protected:

                        void                        msgHandleLog    ( xcore::cstring& Str );
        virtual         const xeditor::tab::type&   getType         ( void ) override;
        virtual         void                        onRender        ( void ) override;

    protected:

        document&                           m_LogDoc;
        ImGuiTextFilter                     m_Filter        {};
        int                                 m_LastLineCount { 0 };
    };
}
