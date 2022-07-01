#include <Arduino.h>
#include "loar.h"

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

static int lua_digitalRead(lua_State *L)
{
  uint8_t pin = luaL_checkinteger(L, 1);
  lua_pushinteger(L, digitalRead(pin));
  return 1;
}

static int lua_digitalWrite(lua_State *L)
{
  uint8_t pin = luaL_checkinteger(L, 1);
  uint8_t val = luaL_checkinteger(L, 2);
  digitalWrite(pin, val);
  return 0;
}

static int lua_pinMode(lua_State *L)
{
  uint8_t pin = luaL_checkinteger(L, 1);
  uint8_t mode = luaL_checkinteger(L, 2);
  pinMode(pin, mode);
  return 0;
}

static int lua_analogRead(lua_State *L)
{
  uint8_t pin = luaL_checkinteger(L, 1);
  lua_pushinteger(L, analogRead(pin));
  return 1;
}

static int lua_shiftOut(lua_State *L)
{
  uint8_t 
    data_pin = luaL_checkinteger(L, 1),
    clock_pin = luaL_checkinteger(L, 2),
    bit_order = luaL_checkinteger(L, 3),
    value = luaL_checkinteger(L, 4);
#ifdef ARDUINO_ARCH_RP2040
  shiftOut(data_pin, clock_pin, (BitOrder)bit_order, value);
#else
  shiftOut(data_pin, clock_pin, bit_order, value);
#endif

  
  return 0;
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

static int lua_micros(lua_State *L)
{
  lua_pushinteger(L, micros());
  return 1;
}

void register_arduino_base(Loar& loar)
{
  lua_State *L = loar.get_state();

  lua_register(L, "print", lua_serial_print);
  lua_register(L, "digitalRead", lua_digitalRead);
  lua_register(L, "digitalWrite", lua_digitalWrite);
  lua_register(L, "pinMode", lua_pinMode);
  lua_register(L, "analogRead", lua_analogRead);
  lua_register(L, "shiftOut", lua_shiftOut);
  lua_register(L, "delay", lua_delay);
  lua_register(L, "millis", lua_millis);
  lua_register(L, "micros", lua_micros);

  LUA_REGISTER_CONSTANT(INPUT);
  LUA_REGISTER_CONSTANT(OUTPUT);
  LUA_REGISTER_CONSTANT(INPUT_PULLUP);
  LUA_REGISTER_CONSTANT(INPUT_PULLDOWN);
  LUA_REGISTER_CONSTANT(LOW);
  LUA_REGISTER_CONSTANT(HIGH);
  LUA_REGISTER_CONSTANT(LSBFIRST);
  LUA_REGISTER_CONSTANT(MSBFIRST);

}