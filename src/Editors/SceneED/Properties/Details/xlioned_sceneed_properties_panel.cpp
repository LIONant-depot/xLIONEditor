
#include "../dependencies/properties/src/Examples/ImGuiExample/ImGuiPropertyExample.h"

namespace xlioned::sceneed::properties {

//-------------------------------------------------------------------------

panel::panel(construct& Construct )
    : xeditor::panel::child(Construct)
    , m_LogDoc{ Construct.m_Parent.getMainDoc().getSubDocument<document>() }
    , m_Inspector( "Properties", false )
{
    m_Inspector.clear();
    m_Inspector.AppendEntity();
    m_Inspector.AppendEntityComponent(Examples.m_Tables[10].first, Examples.m_Tables[10].second);
}

//-------------------------------------------------------------------------

void panel::onRender(void)
{
   // m_Inspector.PopAllStyles();
    m_Inspector.ShowNoWindow();
  //  m_Inspector.PopAllStyles();
}

} // end of namespace xlioned::sceneed::explorer