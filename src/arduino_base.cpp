#include <Arduino.h>
#include <lua.hpp>
#include "loar.h"

#define LUA_REGISTER_CONSTANT(c) \
  do { \
    lua_pushinteger(L, c); \
    lua_setglobal(L, #c); \
  } while (0)

static int lua_serial_print(lua_State *L)
{
  int nargs = lua_gettop(L);
  for(int i = 1; i <= nargs; i++) {
    if(lua_isstring(L, i))
      Serial.print(lua_tostring(L, i));
    else {
      int type = lua_type(L, i);
      switch(type) {
        case LUA_TBOOLEAN:
          Serial.print(lua_toboolean(L, i) ? "true": "false");
          break;
        case LUA_TNUMBER:
          if(lua_isinteger(L, i))
            Serial.print(lua_tointeger(L, i));
          else
            Serial.print(lua_tonumber(L, i));
          break;
        default:
          Serial.print(lua_typename(L, lua_type(L, i)));
          break;
      }
    }
    if(i != nargs) Serial.print('\t');
  }
  Serial.println();
  return 0;
}

static int lua_pinMode(lua_State *L)
{
  uint8_t pin = luaL_checknumber(L, 1);
  uint8_t mode = luaL_checknumber(L, 2);
  pinMode(pin, mode);
  return 0;
}

static int lua_digitalWrite(lua_State *L)
{
  uint8_t pin = luaL_checknumber(L, 1);
  uint8_t val = luaL_checknumber(L, 2);
  digitalWrite(pin, val);
  return 0;
}

static int lua_analogRead(lua_State *L)
{
  uint8_t pin = luaL_checknumber(L, 1);
  lua_pushinteger(L, analogRead(pin));
  return 1;
}

static int lua_delay(lua_State *L)
{
    uint32_t ms = luaL_checkinteger(L, 1);
    delay(ms);
    return 0;
}

static int lua_millis(lua_State *L)
{
  lua_pushinteger(L, millis());
  return 1;
}

void register_arduino_base(Loar& loar)
{
  lua_State *L = loar.get_state();

  lua_pushcfunction(L, lua_serial_print);
  lua_setglobal(L, "print");

  lua_pushcfunction(L, lua_pinMode);
  lua_setglobal(L, "pinMode");

  LUA_REGISTER_CONSTANT(INPUT);
  LUA_REGISTER_CONSTANT(OUTPUT);
  LUA_REGISTER_CONSTANT(INPUT_PULLUP);
  LUA_REGISTER_CONSTANT(INPUT_PULLDOWN);

  lua_pushcfunction(L, lua_digitalWrite);
  lua_setglobal(L, "digitalWrite");
  LUA_REGISTER_CONSTANT(LOW);
  LUA_REGISTER_CONSTANT(HIGH);

  lua_pushcfunction(L, lua_analogRead);
  lua_setglobal(L, "analogRead");

  lua_pushcfunction(L, lua_delay);
  lua_setglobal(L, "delay");

  lua_pushcfunction(L, lua_millis);
  lua_setglobal(L, "millis");

}