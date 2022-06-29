#include "boards.h"
#include "lua/lua.hpp"

#include "espressif/esp.h"
#include "espressif/lua_wifi.h"

int luaopen_board(lua_State *L)
{
    #ifdef ARDUINO_ARCH_ESP32
    luaL_requiref(L, "ESP", luaopen_esp, 1);
    lua_pop(L, 1);
    luaL_requiref(L, "WiFi", luaopen_wifi, 1);
    lua_pop(L, 1);
    #endif

    return 1;
}