#pragma once

// We must link against these libraries on windows platform for Visual Studio IDE.

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)

#ifdef _DEBUG
#pragma comment(lib, "evpp_static_d.lib")
#pragma comment(lib, "libglog_static_d.lib")
#else
#pragma comment(lib, "evpp_static.lib")
#pragma comment(lib, "libglog_static.lib")
#endif

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "libevent_core.lib") // libevent2.0
#pragma comment(lib, "libevent_extras.lib") // libevent2.0

#endif