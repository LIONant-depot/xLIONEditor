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

        void SettingsDependencies(void);
        void SettingsGeneral();
        void SettingsPlugins();
        void SettingsEnviroment();
        void SettingsAI();

    protected:

        document&                           m_LogDoc;
    };
}