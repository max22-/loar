#ifndef LOAR_H
#define LOAR_H

#include <Arduino.h>
#define LUA_32BITS
#include "lua/lua.hpp"

struct lua_State;

class Loar {
public:
    Loar();
    Loar(Stream*);
    ~Loar();
    lua_State *get_state();
    void register_function(const char *name, int (*f)(struct lua_State*));
    void do_repl();
    void set_stream(Stream*);

private:
    Loar(const Loar&) = delete;
    Loar& operator=(const Loar&) = delete;
    void prompt();
    void l_print();
    struct lua_State *L = nullptr;
    Stream *stream = nullptr;
};

#endif