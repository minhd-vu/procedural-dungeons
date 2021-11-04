#include "Game.hpp"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_State *L;
static Game game;

static int move_enemy(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; i += 2)
	{
		Node node;
		node.position.x = lua_tonumber(L, i);
		node.position.y = lua_tonumber(L, i + 1);
		std::cout << "node x: " << node.position.x << " y: " << node.position.y << "\n";
		game.enemy.getPath().push(node);
	}

	return 2;
}

int main()
{
	srand(time(NULL));

	L = lua_open();
	luaL_openlibs(L);
	lua_register(L, "move_enemy", move_enemy);
	luaL_dofile(L, "move_enemy.lua");
	lua_close(L);

	game.run();
	return 0;
}