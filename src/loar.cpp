#include "loar.h"
#include "arduino_base.h"
#include "boards/boards.h"
#include "libraries/loar_libraries.h"

Loar::Loar()
{
  L = luaL_newstate();
  luaL_openlibs(L);
  register_arduino_base(*this);
  luaopen_board(L); // Registers board specific libraries
  luaopen_loar_libraries(L);
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
  static unsigned int idx = 0;
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
      if(lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK)
        l_print();
      else {
        stream->print("error: ");
        stream->println(lua_tostring(L, -1));
      }
      lua_settop(L, 0);
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
  stream->print("> ");
  stream->flush();
}

/*
** Prints (calling the Lua 'print' function) any values on the stack
** (Copied from lua.c, and adapted)
*/
void Loar::l_print()
{
  int n = lua_gettop(L);
  if (n > 0) {  /* any result to be printed? */
    luaL_checkstack(L, LUA_MINSTACK, "too many results to print");
    lua_getglobal(L, "print");
    lua_insert(L, 1);
    if (lua_pcall(L, n, 0, 0) != LUA_OK) {
      stream->print("error calling 'print' (");
      stream->print(lua_tostring(L, -1));
      stream->println(")");
    }
  }
}