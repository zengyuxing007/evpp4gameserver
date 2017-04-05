#pragma once

namespace
{
struct OnApp
{
    OnApp()
    {
#ifdef WIN32
        // Initialize Winsock 2.2
        WSADATA wsaData;
        int err = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if(err)
        {
            std::cout << "WSAStartup() failed with error: %d" << err;
        }
#endif
    }
    ~OnApp()
    {
#ifdef WIN32
        system("pause");
        WSACleanup();
#endif
    }
} __s_onexit_pause;
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

