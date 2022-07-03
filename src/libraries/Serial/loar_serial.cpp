#include <Arduino.h>
#include "lua/lua.hpp"

static int begin(lua_State *L)
{
    unsigned long baud = luaL_checkinteger(L, 1);
    Serial.begin(baud);
    return 0;
}

static int print(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    Serial.print(msg);
    return 0;
}

static int println(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    Serial.println(msg);
    return 0;
}

static int available(lua_State *L)
{
    lua_pushinteger(L, Serial.available());
    return 1;
}

static int end(lua_State *L)
{
    Serial.end();
    return 0;
}

static int flush(lua_State *L)
{
    Serial.flush();
    return 0;
}

static int peek(lua_State *L)
{
    lua_pushinteger(L, Serial.peek());
    return 1;
}

static int read(lua_State *L)
{
    lua_pushinteger(L, Serial.read());
    return 1;
}

static int readString(lua_State *L)
{
    lua_pushstring(L, Serial.readString().c_str());
    return 1;
}

static int setTimeout(lua_State *L)
{
    unsigned long timeout = luaL_checkinteger(L, 1);
    Serial.setTimeout(timeout);
    return 0;
}

static int write(lua_State *L)
{
    const char *s = luaL_checkstring(L, 1);
    lua_pushinteger(L, Serial.write(s));
    return 1;
}

static const struct luaL_Reg serial_lib[] = {
    {"begin", begin},
    {"print", print},
    {"println", println},
    {"available", available},
    {"end", end},
    {"flush", flush},
    {"peek", peek},
    {"read", read},
    {"readString", readString},
    {"setTimeout", setTimeout},
    {"write", write},
    {NULL, NULL}
};

int luaopen_serial(lua_State *L)
{
    luaL_newlib(L, serial_lib);
    return 1;
}