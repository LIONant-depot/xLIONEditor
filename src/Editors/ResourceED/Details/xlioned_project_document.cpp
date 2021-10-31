
namespace xlioned::project {

//-------------------------------------------------------------------------------------------
static const xeditor::document::details::type_harness<document> s_TypeDoc{ document::class_name_v };

//--------------------------------------------------------------------------------

const xeditor::document::type& document::getType(void) const noexcept
{
    return s_TypeDoc;
}

//--------------------------------------------------------------------------------

document::document(xcore::string::constant<char> Str, xeditor::document::main& MainDoc) noexcept
    : xeditor::document::base(Str, MainDoc)
{
}

//--------------------------------------------------------------------------------

xcore::err document::onSave(void) { return {}; }
xcore::err document::onNew(void) { return {}; }
xcore::err document::onClose(void) { return {}; }
xcore::err document::onLoad(void) { return {}; }

} // namespace xlioned::sceneed
