
#define PROPERTY_EDITOR
#include "../dependencies/xEditor/Src/xeditor.h"

namespace xlioned::document
{
    class main : public xeditor::document::main
    {
        xcore_rtti(main, xeditor::document::main)
    
    public:

        constexpr static auto           class_name_v = xcore::string::constant("xLIONEditor/Documents/Main");

        main(xeditor::frame::base& Frame) noexcept : xeditor::document::main(class_name_v, Frame) {}

    public:

    };
}
