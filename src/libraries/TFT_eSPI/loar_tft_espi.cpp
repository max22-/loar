#include "loar_tft_espi.h"
#ifdef LOAR_USE_TFT_ESPI
#include "loar.h"
#include "lua/lua.hpp"
#include <TFT_eSPI.h>

static TFT_eSPI tft = TFT_eSPI();

static int init(lua_State *L)
{
    tft.init();
    return 0;
}

static int setRotation(lua_State *L)
{
    int r = luaL_checkinteger(L, 1);
    if(r > 7)
        return luaL_error(L, "Invalid argument (0<=r<=7)");
    tft.setRotation(r);
    return 0;
}

static int fillScreen(lua_State *L)
{
    int c = luaL_checkinteger(L, 1);
    tft.fillScreen(c);
    return 0;
}

static int setTextSize(lua_State *L)
{
    uint8_t s = luaL_checkinteger(L, 1);
    tft.setTextSize(s);
    return 0;
}

static int setCursor(lua_State *L)
{
    int16_t x = luaL_checkinteger(L, 1);
    int16_t y = luaL_checkinteger(L, 2);
    if(lua_gettop(L) == 3) {
        uint8_t font = luaL_checkinteger(L, 3);
        tft.setCursor(x, y, font);
    } else tft.setCursor(x, y);
    return 0;
}

static int getCursor(lua_State *L)
{
    lua_pushinteger(L, tft.getCursorX());
    lua_pushinteger(L, tft.getCursorY());
    return 2;
}

static int print(lua_State *L)
{
  int nargs = lua_gettop(L);
  for(int i = 1; i <= nargs; i++) {
    if(lua_isstring(L, i))
      tft.print(lua_tostring(L, i));
    else {
      int type = lua_type(L, i);
      switch(type) {
        case LUA_TBOOLEAN:
          tft.print(lua_toboolean(L, i) ? "true": "false");
          break;
        case LUA_TNUMBER:
          if(lua_isinteger(L, i))
            tft.print(lua_tointeger(L, i));
          else
            tft.print(lua_tonumber(L, i));
          break;
        default:
          tft.print(lua_typename(L, lua_type(L, i)));
          break;
      }
    }
    if(i != nargs) tft.print('\t');
  }
  tft.println();
  return 0;
}

static int drawRect(lua_State *L)
{
    int32_t x = luaL_checkinteger(L, 1);
    int32_t y = luaL_checkinteger(L, 2);
    int32_t w = luaL_checkinteger(L, 3);
    int32_t h = luaL_checkinteger(L, 4);
    int32_t color = luaL_checkinteger(L, 5);
    tft.drawRect(x, y, w, h, color);
    return 0;
}

static const struct luaL_Reg tft_espi_lib[] = {
    {"init", init},
    {"setRotation", setRotation},
    {"fillScreen", fillScreen},
    {"setTextSize", setTextSize},
    {"setCursor", setCursor},
    {"getCursor", getCursor},
    {"print", print},
    {"drawRect", drawRect},
    {NULL, NULL}
};

int luaopen_tft_espi(lua_State *L)
{
    luaL_newlib(L, tft_espi_lib);
    LUA_REGISTER_CONSTANT(TFT_BLACK);
    LUA_REGISTER_CONSTANT(TFT_NAVY);
    LUA_REGISTER_CONSTANT(TFT_DARKGREEN);
    LUA_REGISTER_CONSTANT(TFT_DARKCYAN);
    LUA_REGISTER_CONSTANT(TFT_MAROON);
    LUA_REGISTER_CONSTANT(TFT_PURPLE);
    LUA_REGISTER_CONSTANT(TFT_OLIVE);
    LUA_REGISTER_CONSTANT(TFT_LIGHTGREY);
    LUA_REGISTER_CONSTANT(TFT_DARKGREY);
    LUA_REGISTER_CONSTANT(TFT_BLUE);
    LUA_REGISTER_CONSTANT(TFT_GREEN);
    LUA_REGISTER_CONSTANT(TFT_CYAN);
    LUA_REGISTER_CONSTANT(TFT_RED);
    LUA_REGISTER_CONSTANT(TFT_MAGENTA);
    LUA_REGISTER_CONSTANT(TFT_YELLOW);
    LUA_REGISTER_CONSTANT(TFT_WHITE);
    LUA_REGISTER_CONSTANT(TFT_ORANGE);
    LUA_REGISTER_CONSTANT(TFT_GREENYELLOW);
    LUA_REGISTER_CONSTANT(TFT_PINK);
    LUA_REGISTER_CONSTANT(TFT_BROWN);
    LUA_REGISTER_CONSTANT(TFT_GOLD);
    LUA_REGISTER_CONSTANT(TFT_SILVER);
    LUA_REGISTER_CONSTANT(TFT_SKYBLUE);
    LUA_REGISTER_CONSTANT(TFT_VIOLET);
    return 1;
}

#endif