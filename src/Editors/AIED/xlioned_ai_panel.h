namespace xlioned::ai
{
    class panel : public xeditor::panel::parent
    {
        xcore_rtti(panel, xeditor::panel::parent);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " AI");

    public:

        panel( construct& Construct );
        int     TextEditCallback( ImGuiInputTextCallbackData* pData );
    protected:

        virtual         void                        onRender                ( void ) override;
        virtual         void                        onCreateChildrenPanels  ( void ) override;

    protected:

        document&                           m_AIDoc;
        std::array<char,256>                m_InputBuf{};
        bool                                m_bScrollToBottom{ false };
        bool                                m_bAutoScroll    { true };

    };
}