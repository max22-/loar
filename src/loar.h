#ifndef LOAR_H
#define LOAR_H

struct lua_State;
class Stream;

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
    struct lua_State *L = nullptr;
    Stream *stream = nullptr;
};

#endif