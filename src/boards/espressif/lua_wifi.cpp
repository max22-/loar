#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>
#include <WiFi.h>
#include "lua/lua.hpp"

static int begin(lua_State *L)
{
    const char *ssid = luaL_checkstring(L, 1);
    const char *passwd = luaL_checkstring(L, 2);
    WiFi.begin(ssid, passwd);
    return 0;
}

static int localIP(lua_State *L)
{
    lua_pushstring(L, WiFi.localIP().toString().c_str());
    return 1;
}

static const struct luaL_Reg wifi_lib[] = {
    {"begin", begin},
    {"localIP", localIP},
    {NULL, NULL}
};

int luaopen_wifi(lua_State *L)
{
    luaL_newlib(L, wifi_lib);
    return 1;
}

#endif