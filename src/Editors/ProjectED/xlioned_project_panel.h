namespace xlioned::project
{
    class panel : public xeditor::panel::parent
    {
        xcore_rtti(panel, xeditor::panel::parent);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " Project");

    public:

        panel( construct& Construct );
    
    protected:

        virtual         void                        onRender                ( void ) override;
        virtual         void                        onCreateChildrenPanels  ( void ) override;

        void SettingsDependencies( bool bFirstTime );
        void SettingsGeneral(bool bFirstTime);
        void SettingsPlugins(bool bFirstTime);
        void SettingsEnviroment(bool bFirstTime);
        void SettingsAI(bool bFirstTime);

    protected:

        document&                           m_ProjectDoc;
        property::inspector                 m_Inspector;
        int                                 m_SelectedMenu = -1;
    };
}