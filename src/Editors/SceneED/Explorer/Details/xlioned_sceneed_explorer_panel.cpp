
namespace xlioned::sceneed::explorer {

xeditor::panel::details::type_harness<xlioned::sceneed::explorer::panel> panel::s_Type
{ panel::class_name_v
};

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