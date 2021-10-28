
#include "Explorer/xlioned_sceneed_explorer.h"

namespace xlioned::sceneed {

    xeditor::panel::details::type_harness<panel, explorer::panel> s_Type{ panel::class_name_v };

    //-------------------------------------------------------------------------

    panel::panel( construct& Construct )
        : xeditor::panel::parent(Construct)
        , m_LogDoc{ Construct.m_EditorFrame.getMainDoc().getSubDocument<document>() }
    {
    }

    //-------------------------------------------------------------------------

    void panel::onCreateChildrenPanels(void)
    {
        (void)parent::CreateTab( "Explorer" );
    }

    //-------------------------------------------------------------------------

    void panel::onRender(void)
    {
    
    }
}