
namespace xlioned::sceneed::explorer {

//-------------------------------------------------------------------------

panel::panel(construct& Construct )
    : xeditor::panel::child(Construct)
    , m_LogDoc{ Construct.m_Parent.getMainDoc().getSubDocument<document>() }
{
}

//-------------------------------------------------------------------------

void panel::onRender(void)
{

}

} // end of namespace xlioned::sceneed::explorer