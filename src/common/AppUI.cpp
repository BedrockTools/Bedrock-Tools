#include "AppUI.hpp"

namespace AppUI
{
    inline HttpServer g_Server{};
    void serveHttp()
    {
        g_Server.use(R"(/.*)", HttpMethod::GET,
            HttpServer::useStatic("data/ui"));

        g_Server.listen(56729);
    };
};