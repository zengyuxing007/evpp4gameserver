#pragma once

#include "platform_config.h"

#ifdef H_OS_WINDOWS
#ifdef H_DEBUG_MODE
H_LINK_LIB("evpp_static_d")
H_LINK_LIB("libglog_static_d")
#else
H_LINK_LIB("evpp_static")
H_LINK_LIB("libglog_static")
#endif

H_LINK_LIB("Ws2_32")
H_LINK_LIB("libevent")
H_LINK_LIB("libevent_core") // libevent2.0
H_LINK_LIB("libevent_extras") // libevent2.0
#endif




