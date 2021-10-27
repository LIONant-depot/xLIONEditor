namespace xlioned::sceneed::explorer
{
    class document : public xeditor::document::base
    {
        xcore_rtti(document, xeditor::document::base);
        constexpr static auto class_name_v = xcore::string::constant("xLion/Documents/Scene");
    public:

                                                        document        ( xcore::string::constant<char> Str, xeditor::document::main& MainDoc )                         noexcept;
        xforceinline            bool                    isSceneValid    ( void )                                                                                const   noexcept { return m_SceneGuid.m_gRC.m_Value != 0; }
        virtual                 const type&             getType         ( void )                                                                                const   noexcept override;
        xforceinline            auto                    getSceneFullGuid( void )                                                                                const   noexcept { return m_SceneGuid; }

        x_incppfile             magic_folder&           appendZone      (magic_folder::guid            gParent
            , gb_cfactory::zone_guid      gZone)                                                                         noexcept;


        x_inline                void                    setActiveFZone(magic_folder::guid            gFolder)                                                                       noexcept { m_gActiveFolder = gFolder; }
        x_inline                auto                    getActiveFZone(void)                                                                                                const   noexcept { return m_gActiveFolder; }
        x_incppfile             void                    DestroyEntity(entity_guid                   gEntity)                                                                       noexcept;
        x_incppfile             magic_folder& CreateFolder(magic_folder::guid            gParent
            , magic_folder::guid          gNewFolder = xnot_null)                                                        noexcept;
        x_incppfile             entity_guid             CreateEntity(gb_cfactory::interface::guid  gEntityType
            , entity_guid                 InstanceGuid
            , magic_folder::guid          gFolder = nullptr)                                                             noexcept;
        x_incppfile             entity_guid             CreateEDEntity(gb_cfactory::interface::guid  gEntityType
            , entity_guid                 InstanceGuid
            , magic_folder::guid          gFolder = nullptr)                                                             noexcept;
        //    x_incppfile             entity_guid             RenameEDEntity      ( entity_guid                   gEntity
        //                                                                          , xbuffer_view<char>          NewName )                                                                       noexcept;
        x_incppfile             void                    RenameFolder(magic_folder::guid            gFolder
            , xbuffer_view<char>          NewName)                                                                       noexcept;
        x_inline                auto& getLayersDB(void)                                                                                                        noexcept { return m_lLayers; }
        x_inline                auto& get(entity_guid Guid)                                                                                            noexcept { return *m_lEditorEntities[Guid]; }
        x_inline                auto& get(magic_folder::guid Guid)                                                                                     noexcept { return *m_lMagicFolders[Guid]; }
        x_incppfile             auto& get(zone_guid Guid)                                                                                              noexcept;
        x_inline                edentity* findEDEntry(entity_guid Guid)                                                                                            noexcept { auto t = m_lEditorEntities.find(entity_guid{ Guid.m_Value }); return t == m_lEditorEntities.end() ? nullptr : t->second.getPtr(); }
        inline                  err                     New(void)                                                                                                        noexcept { if (auto Error = onClose(); Error.isError() == false) return onNew(); else return Error; }
        inline                  err                     Save(void)                                                                                                        noexcept { return onSave(); }
        inline                  err                     Load(void)                                                                                                        noexcept { if (auto Error = onClose(); Error.isError() == false) return onLoad(); else return Error; }
        inline                  err                     Close(void)                                                                                                        noexcept { return onClose(); }
        x_incppfile             err                     ImportLayer(xrcguid_full gLayer)                                                                                         noexcept;
        x_forceconst            auto                    getBlueprintFolderGuid(void)                                                                                              const   noexcept { return ms_gBlueprintEditingFolder; }

    protected:

        using edentity_db = std::map< entity_guid, xndptr_s<edentity> >;
        using magicf_db = std::map< magic_folder::guid, xndptr_s<magic_folder> >;

    protected:


        virtual                 err                     onSave(void)                                                                                                        xthrows override;
        virtual                 err                     onLoad(void)                                                                                                        xthrows override;
        virtual                 err                     onNew(void)                                                                                                        xthrows override { return err::state::OK; }
        virtual                 err                     onClose(void)                                                                                                        xthrows override;
        x_incppfile             void                    msgChangeHappen(xproperty_v2::base& Prop)                                                                                    noexcept;
        x_incppfile             bool                    msgAssetEdit(xrcguid_full gScene)                                                                                         noexcept;
        x_incppfile             err                     HandleSceneLoad(void)                                                                                                        noexcept;
        x_incppfile             err                     LoadLayer(xrcguid_full gLayer, std::mutex& Mutex)                                                                      noexcept;
        x_incppfile             err                     SaveLayer(xrcguid_full gLayer)                                                                                         noexcept;
        x_incppfile             void                    Init(void)                                                                                                        noexcept;

    protected:

        X_CMD_LOGGING(x_reporting::log_channel                 m_LogChannel{ t_class_string_v.m_pValue,   true });
        x_constexprvar magic_folder::guid                       ms_gBlueprintEditingFolder{ "Blueprint Folder for Editing" };
        gbed_scene_player::document& m_ScenePlayerDoc;
        gbed_game_refresh::document& m_GameRefreshDoc;
        xrcguid_full                                            m_SceneGuid{ {xnull}, {xnull} };
        magicf_db                                               m_lMagicFolders{};
        edentity_db                                             m_lEditorEntities{};
        xvector< layer >                                        m_lLayers{};
        magic_folder::guid                                      m_gActiveFolder{ xnull };
        xstring                                                 m_ScenePath{};
        x_message::event<xproperty_v2::base&>::delegate         m_deletegateChangeHappen { this, & document::msgChangeHappen };
        x_message::event_rtn<xrcguid_full>::delegate            m_deletegateAssetEdit{ this, &document::msgAssetEdit };
        bool                                                    m_bChanged{ false };
        */
    };
}