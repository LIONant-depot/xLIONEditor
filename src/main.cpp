
#include "../../src/xlioned_main_document.h"
#include "../../dependencies/xEditor/dependencies/xgpu/src/xGPU.h"
#include "../../dependencies/xEditor/dependencies/xgpu/tools/xgpu_imgui_breach.h"
#include "../dependencies/properties/src/Examples/ImGuiExample/ImGuiPropertyInspector.cpp"

//------------------------------------------------------------------------------------------------

struct editor
{
    xcore::log::channel                         m_GraphicsLog{ std::string("Graphics") };
    xgpu::instance                              m_Instance;
    xgpu::device                                m_Device;
    xgpu::window                                m_MainWindow;
    std::unique_ptr<xeditor::frame::base>       m_MainFrame;
    std::unique_ptr<xlioned::document::main>    m_MainDocument;
    inline static xcore::log::channel*          s_pGlobalAccessLogChannel;

    int Init( void )
    {
        //
        // Init Graphics Instance
        //
        {
            s_pGlobalAccessLogChannel = &m_GraphicsLog;
            xgpu::instance::setup Setup
            { .m_pAppName           = "xLionEditor"
            , .m_bDebugMode         = true
            , .m_bEnableRenderDoc   = true
            , .m_Driver             = xgpu::instance::setup::driver::VULKAN
            , .m_pLogErrorFunc      = [](std::string_view View){ XLOG_CHANNEL_ERROR( *s_pGlobalAccessLogChannel, "%s", View.data() ); }
            , .m_pLogWarning        = [](std::string_view View){ XLOG_CHANNEL_WARNING( *s_pGlobalAccessLogChannel, "%s", View.data()); }
            };
            
            if (auto Err = xgpu::CreateInstance(m_Instance, Setup ); Err)
                return xgpu::getErrorInt(Err);
        }

        if (auto Err = m_Instance.Create(m_Device); Err)
            return xgpu::getErrorInt(Err);

        if (auto Err = m_Device.Create(m_MainWindow, {}); Err)
            return xgpu::getErrorInt(Err);
    
        //
        // Create main doc
        //
        m_MainFrame    = std::make_unique<xeditor::frame::base>(m_MainWindow);
        m_MainDocument = std::make_unique<xlioned::document::main>(*m_MainFrame);

        return 0;
    }
};

//------------------------------------------------------------------------------------------------

int main()
{
    xcore::Init("LIONEditor");

    //
    // Create an instance of the editor
    //
    auto Editor = std::make_unique<editor>();
    if( auto Err = Editor->Init(); Err ) return Err;

    //
    // Main loop
    //
    while( Editor->m_MainFrame->AdvanceLogic() )
    {
        // Working...
    }

    return 0;
}

