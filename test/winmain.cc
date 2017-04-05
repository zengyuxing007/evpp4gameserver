#include "test_common.h"

#include "evpp/libevent_headers.h"

namespace
{
#ifdef WIN32
struct OnApp
{
    OnApp()
    {
        // Initialize net work.
        WSADATA wsaData;
        // Initialize Winsock 2.2
        int nError = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if(nError)
        {
            std::cout << "WSAStartup() failed with error: %d" << nError;
        }

    }
    ~OnApp()
    {
        system("pause");
    }
} __s_onexit_pause;
#endif
}

#ifdef _WIN32

#ifdef _DEBUG
#pragma comment(lib, "evpp_static_d.lib")
#pragma comment(lib, "libglog_static_d.lib")
#else
#pragma comment(lib, "evpp_static.lib")
#pragma comment(lib, "libglog_static.lib")
#endif // _DEBUG

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "libevent_core.lib") // libevent2.0
#pragma comment(lib, "libevent_extras.lib") // libevent2.0
#endif

// main function is defined on gtest_main.cc