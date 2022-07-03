#include "loar_spi.h"
#ifdef LOAR_USE_SPI
#include "loar.h"
#include "lua/lua.hpp"
#include <SPI.h>

static int begin(lua_State *L)
{
    SPI.begin();
    return 0;
}

static int beginTransaction(lua_State *L)
{
    uint32_t clock = luaL_checkinteger(L, 1);
    uint8_t bitOrder = luaL_checkinteger(L, 2);
    uint8_t dataMode = luaL_checkinteger(L, 3);
    SPI.beginTransaction(SPISettings(clock, bitOrder, dataMode));
    return 0;
}

static int endTransaction(lua_State *L)
{
    SPI.endTransaction();
    return 0;
}

static int end(lua_State *L)
{
    SPI.end();
    return 0;
}

static int transfer(lua_State *L)
{
    uint8_t val = luaL_checkinteger(L, 1);
    lua_pushinteger(L, SPI.transfer(val));
    return 1;
}

static int transfer16(lua_State *L)
{
    uint16_t val = luaL_checkinteger(L, 1);
    lua_pushinteger(L, SPI.transfer16(val));
    return 1;
}

static const struct luaL_Reg spi_lib[] = {
    {"begin", begin},
    {"beginTransaction", beginTransaction},
    {"endTransaction", endTransaction},
    {"end", end},
    {"transfer", transfer},
    {"transfer16", transfer16},
    {NULL, NULL}
};

int luaopen_spi(lua_State *L)
{
    luaL_newlib(L, spi_lib);

    LUA_REGISTER_CONSTANT(LSBFIRST);
    LUA_REGISTER_CONSTANT(MSBFIRST);

    LUA_REGISTER_CONSTANT(SPI_MODE0);
    LUA_REGISTER_CONSTANT(SPI_MODE1);
    LUA_REGISTER_CONSTANT(SPI_MODE2);
    LUA_REGISTER_CONSTANT(SPI_MODE3);
    
    return 1;
}

#endif