namespace xlioned::loged
{
    class frame : public xeditor::frame::base
    {
        xcore_rtti(frame, xeditor::frame::base);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " Log");
    
    public:

                                                        frame           ( xcore::string::constant<char> Str, xeditor::frame::instance_guid Guid, xeditor::frame::main& EditorFrame );

    protected:

        enum class open_popup : std::uint8_t
        { NONE
        , MAIN_MENU
        , COPY_LOG_TO_CLIPBOARD
        };


    protected:

                        void                            msgHandleLog    ( xcore::cstring& Str );
        virtual         const xeditor::frame::type&     getType         ( void ) override;
        virtual         void                            onRender        ( void ) override;

    protected:

        document&                           m_LogDoc;
        ImGuiTextFilter                     m_Filter        {};
        int                                 m_LastLineCount { 0 };
    };
}
