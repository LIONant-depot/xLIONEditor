namespace xlioned_sceneed::scenneed::explorer::magic_folders
{
    using magic_folder_path     = xcore::types::make_unique< std::filesystem::path, struct magic_folder_path_tag >;
    using edentity_path         = xcore::types::make_unique< std::filesystem::path, struct edentity_path_tag >;

    using zone_guid             = xcore::guid::unit<64, struct zone_guid_tag >;
    using layer_guid            = xcore::guid::rcfull<>;

    //----------------------------------------------------------------------------

    struct folder 
    {
        enum class type : std::uint8_t
        { NONE
        , LAYER
        , FOLDER_IN_LAYER
        , ZONE
        , FOLDER_IN_ZONE
        , DEFAULT_ZONE
        , BLUEPRINT_EDITING
        , COUNT
        };

        static constexpr std::array<const char*, static_cast<std::size_t>(type::COUNT)> g_TypeToString =
        { "ERROR"
        , "LAYER"           // Layer
        , "LFOLDER"         // Layer folder
        , "ZONE"            // zone
        , "ZFOLDER"         // Zone folder
        , "BLUEPRINTS"      // Blue prints been edited (System Layer)
        };

        using guid = xcore::guid::unit<64, struct folder_tag >;

                        guid        getGuid         ( void )                                                        const   noexcept { return m_Guid; }
                        void        Save            ( xcore::textfile::stream& File )                          ;
                        void        Load            ( xcore::textfile::stream& File )                          ;

        type                                        m_Type                  { type::NONE };
        guid                                        m_Guid                  {};             // Zone, Layer, or Folder Guid
        guid                                        m_gParent               {};             // could point to layer or magic_folder

        xcore::cstring                              m_Name                  {};             // Layer + Zone does not use this
        zone_guid                                   m_gZone                 {};             // Layer + folder_in_layer does not use this

        layer_guid                                  m_gLayer                {};             // No Need to save
        xcore::vector<std::uint64_t>                m_lgEntity              {};             // List of magic folder entities No Need to save
        xcore::vector<guid>                         m_lgChildren            {};             // No Need to save
        mutable bool                                m_bChanged              { false };      // No Need to save
        mutable bool                                m_bExpanded             { false };      // No Need to save
    };

    //----------------------------------------------------------------------------

    struct entity : xcore::property::base
    {
        xcore_rtti_start(entity);

                                                    entity                  ( gbed_scene_player::document& GameGraphDoc )       noexcept : m_ScenePlayerDoc{ GameGraphDoc } {}
        virtual                                    ~entity                  ( void )                                            noexcept {}
                        std::uint64_t               getGuid                 ( void )                                    const   noexcept { return m_Guid; }
                        void                        Save                    ( xcore::textfile::stream& File );
                        void                        Load                    ( xcore::textfile::stream& File );

        std::uint64_t                               m_Guid                  {};
        gb_cfactory::interface::guid                m_gEntityType           {};
        xcore::cstring                              m_Name                  {};
        folder::guid                                m_gFolder               { nullptr };

        mutable bool                                m_bChanged              { false };
        mutable bool                                m_bBlueprintInstance    { false };
    };

    //----------------------------------------------------------------------------

    struct layer
    {
        layer_guid                                  m_Guid                  {};
        bool                                        m_bLoad                 { true };
        mutable bool                                m_bExpanded             { true };
    };
}
