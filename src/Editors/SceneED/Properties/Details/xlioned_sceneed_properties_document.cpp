namespace xlioned::sceneed::properties {

//-------------------------------------------------------------------------------------------
static const xeditor::document::details::type_harness<xlioned::sceneed::properties::document> s_TypeDoc{ xlioned::sceneed::properties::document::class_name_v };

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

} // end of namespace xlioned::sceneed::explorer 