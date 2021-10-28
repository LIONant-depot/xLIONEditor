namespace xlioned::sceneed::explorer
{
    class panel : public xeditor::panel::child
    {
        xcore_rtti(panel, xeditor::panel::child);
        constexpr static auto class_name_v = xcore::string::constant("" ICON_FA_TASKS " Explorer");

        static xeditor::panel::details::type_harness<xlioned::sceneed::explorer::panel> s_Type;
    public:

        panel( construct& Construct );

    protected:

        virtual         void                        onRender(void) override;


    protected:

        document& m_LogDoc;
    };
}