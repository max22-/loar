#include "loar.h"
#include <lua.hpp>
#include <Arduino.h>
#include "gpio.h"

static int test(lua_State *);

Loar::Loar()
{
  L = luaL_newstate();
  luaL_openlibs(L);
  register_gpio(*this);
}

Loar::Loar(Stream *stream) : Loar()
{
    set_stream(stream);
}

Loar::~Loar()
{
    lua_close(L);
}

lua_State *Loar::get_state()
{
    return L;
}

void Loar::do_repl()
{
  static char buffer[512] = {0};
  static int idx = 0;
  static bool prompt_flag = false;
  if(stream == nullptr)
    return;
  if(!prompt_flag) {
    prompt();
    prompt_flag = true;
  }    

  while(stream->available() > 0) {
    if(idx >= sizeof(buffer) - 2) {
        while(stream->available()) stream->read();
        stream->println("Error: input buffer overflow");
        idx = 0;
        break;
    }
    int c = stream->read();
    stream->print((char)c);
    if(c != '\n') buffer[idx++] = c; 
    else {
      buffer[idx] = 0;
      luaL_loadbuffer(L, buffer, strlen(buffer), "repl");
      if(lua_pcall(L, 0, 0, 0) != 0) {
        stream->printf("error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
      }
      idx=0;
      prompt();
    }
  }
}

void Loar::set_stream(Stream* stream)
{
    this->stream = stream;
}


// Private *****************

void Loar::prompt()
{
  if(stream == nullptr)
    return;
  stream->printf("> ");
  stream->flush();
}
