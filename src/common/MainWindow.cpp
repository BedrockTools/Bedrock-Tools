#include "MainWindow.hpp"

static std::vector<char> loadShader(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    return {
        (std::istreambuf_iterator(file)),
        std::istreambuf_iterator<char>()
    };
};

inline const auto vs_shader = loadShader("assets/shaders/Test/Test.vertex.bin");
inline const auto fs_shader = loadShader("assets/shaders/Test/Test.fragment.bin");

bgfx::ProgramHandle program;

struct PosColorVertex {
    float x, y, z; // Position
};

PosColorVertex vertices[] = {
    {-0.5f,  0.5f, 0.0f},  // Top-left
    { 0.5f,  0.5f, 0.0f},  // Top-right
    {-0.5f, -0.5f, 0.0f},  // Bottom-left
    { 0.5f, -0.5f, 0.0f}   // Bottom-right
};

bgfx::VertexLayout layout;
bgfx::VertexBufferHandle vertexBuffer;

//Index buffer
uint16_t indices[] = { 0, 1, 2, 1, 3, 2 };
bgfx::IndexBufferHandle indexBuffer;

void MainWindow::initialize(const std::shared_ptr<webview::webview>& webview, int width, int height)
{
    this->m_Width = width;
    this->m_Height = height;
    this->m_Webview = webview;

    {
        webview->set_title("Bedrock Tools");
        webview->set_size(640, 480, WEBVIEW_HINT_MIN);
        webview->set_size(width, height, WEBVIEW_HINT_NONE);

        webview->navigate("http://127.0.0.1:56729/index.html");
    };

    bgfx::PlatformData platformData;
    platformData.nwh = webview->window().value();

    bgfx::Init bgfxInit;
#ifdef _WIN32 // Windows (x64 and x86)
    bgfxInit.type = bgfx::RendererType::Direct3D11;

#elif defined(__ANDROID__)
    bgfxInit.type = bgfx::RendererType::OpenGLES;

#elif defined(__APPLE__) // Apple platforms (macOS, iOS)
    bgfxInit.type = bgfx::RendererType::Metal;

#else // Linux or an unknown platform
    bgfxInit.type = bgfx::RendererType::OpenGL;

#endif

    bgfxInit.resolution.width = this->m_Width;
    bgfxInit.resolution.height = this->m_Height;
    bgfxInit.resolution.reset = this->m_Vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;
    bgfxInit.platformData = platformData;
    bgfx::init(bgfxInit);

    bgfx::ShaderHandle vertexShader = bgfx::createShader(bgfx::makeRef(vs_shader.data(), vs_shader.size()));
    bgfx::ShaderHandle fragmentShader = bgfx::createShader(bgfx::makeRef(fs_shader.data(), fs_shader.size()));

    std::cout << "Meow!" << std::endl;
    if (!bgfx::isValid(vertexShader)) {
        std::cout << "Vertex shader creation failed!" << std::endl;
    };
    if (!bgfx::isValid(fragmentShader)) {
        std::cout << "Fragment shader creation failed!" << std::endl;
    };

    program = bgfx::createProgram(vertexShader, fragmentShader, true);
    if (!bgfx::isValid(program)) {
        std::cout << "Shader program creation failed!" << std::endl;
    };

    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .end();
    vertexBuffer = bgfx::createVertexBuffer(
        bgfx::makeRef(vertices, sizeof(vertices)),
        layout
    );

    indexBuffer = bgfx::createIndexBuffer(
        bgfx::makeRef(indices, sizeof(indices))
    );

    bgfx::setDebug(BGFX_DEBUG_NONE);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
};

void MainWindow::update(int width, int height)
{
    this->m_Width = width;
    this->m_Height = height;
    bgfx::reset(this->m_Width, this->m_Height, this->m_Vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE);
    bgfx::setViewRect(0, 0, 0, this->m_Width, this->m_Height);

    bgfx::frame();
    //bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFFFFFFFF, 1.0f, 0);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0xAFAFC8FF, 1.0f, 0);
    bgfx::touch(0);

    // Set the vertex and index buffers
    bgfx::setVertexBuffer(0, vertexBuffer);
    bgfx::setIndexBuffer(indexBuffer);

    // Submit the draw call
    bgfx::submit(0, program);
};

void MainWindow::terminate() const
{
    this->m_Webview->terminate();
    bgfx::shutdown();
};

std::string MainWindow::getWindowTitle() const
{
    std::stringstream stream;
    stream << "Bedrock Tools";

    if (true)
    {
        stream
            << " "
            << "(" << this->m_Width << ", " << this->m_Height << ")";
    };

    return stream.str();
};