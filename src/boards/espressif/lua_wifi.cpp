#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>
#include <WiFi.h>
#include "lua/lua.hpp"
#include "loar.h"

static int mode(lua_State *L)
{
    const int m = luaL_checkinteger(L, 1);
    if(m >= WIFI_MODE_MAX)
        return luaL_error(L, "Invalid WiFi mode (%d)", m);
    WiFi.mode((wifi_mode_t)m);
    return 0;
}

static int begin(lua_State *L)
{
    const char *ssid = luaL_checkstring(L, 1);
    const char *passwd = luaL_checkstring(L, 2);
    WiFi.begin(ssid, passwd);
    return 0;
}

static int softAP(lua_State *L)
{
    const char *ssid = luaL_checkstring(L, 1);
    const char *passwd = luaL_checkstring(L, 2);
    WiFi.softAP(ssid, passwd);
    return 0;
}

static int scan(lua_State *L)
{
    int n = WiFi.scanNetworks();
    lua_createtable(L, 0, n);
    for(int i = 0; i < n; i++) {
        lua_createtable(L, 0, 2);
        lua_pushinteger(L, WiFi.RSSI(i));
        lua_setfield(L, -2, "RSSI");
        lua_pushinteger(L, WiFi.encryptionType(i));
        lua_setfield(L, -2, "encryptionType");
        lua_pushinteger(L, WiFi.channel(i));
        lua_setfield(L, -2, "channel");

        lua_setfield(L, -2, WiFi.SSID(i).c_str());
    }
    return 1;
}

static int status(lua_State *L)
{
    lua_pushinteger(L, WiFi.status());
    return 1;
}

static int localIP(lua_State *L)
{
    lua_pushstring(L, WiFi.localIP().toString().c_str());
    return 1;
}

static int RSSI(lua_State *L)
{
    lua_pushinteger(L, WiFi.RSSI());
    return 1;
}

static const struct luaL_Reg wifi_lib[] = {
    {"mode", mode},
    {"begin", begin},
    {"softAP", softAP},
    {"scan", scan},
    {"status", status},
    {"localIP", localIP},
    {"RSSI", RSSI},
    {NULL, NULL}
};

int luaopen_wifi(lua_State *L)
{
    luaL_newlib(L, wifi_lib);

    /* WiFi.mode() */
    LUA_REGISTER_CONSTANT(WIFI_MODE_NULL);
    LUA_REGISTER_CONSTANT(WIFI_MODE_STA);
    LUA_REGISTER_CONSTANT(WIFI_MODE_AP);
    LUA_REGISTER_CONSTANT(WIFI_MODE_APSTA);
    LUA_REGISTER_CONSTANT(WIFI_MODE_MAX);

    /* WiFi.status() */
    LUA_REGISTER_CONSTANT(WL_NO_SHIELD);
    LUA_REGISTER_CONSTANT(WL_IDLE_STATUS);
    LUA_REGISTER_CONSTANT(WL_NO_SSID_AVAIL);
    LUA_REGISTER_CONSTANT(WL_SCAN_COMPLETED);
    LUA_REGISTER_CONSTANT(WL_CONNECTED);
    LUA_REGISTER_CONSTANT(WL_CONNECT_FAILED);
    LUA_REGISTER_CONSTANT(WL_CONNECTION_LOST);
    LUA_REGISTER_CONSTANT(WL_DISCONNECTED);

    /* WiFi.encryptionType() */
    LUA_REGISTER_CONSTANT(WIFI_AUTH_OPEN);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WEP);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA2_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA_WPA2_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA2_ENTERPRISE);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA3_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WPA2_WPA3_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_WAPI_PSK);
    LUA_REGISTER_CONSTANT(WIFI_AUTH_MAX);

    return 1;
}

#endif