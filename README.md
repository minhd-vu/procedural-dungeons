# procedural-dungeons

![Demo Video](https://github.com/minhd-vu/procedural-dungeons/blob/master/gameplay.mkv)

## Running
```
make -B && ./build/procedural-dungeons
```

## Overview
Birb has hit her head and lost her way home! When she was going on a grocery trip, she lost one of her eggs! Help Birb find her egg and bring it back to her nest. Make sure you avoid trees and water as Birb can't swim!

## Requirements

- [x] The dungeon level shall be generated randomly
  - The procedural dungeon generation is similar to [this](https://www.tomstephensondeveloper.co.uk/post/creating-simple-procedural-dungeon-generation) but with modifications.
- [x] The dungeon shall have some way to be "interesting," it should not be a straight line to the goal
  - There are rooms and paths and generally, the random generation will make it interesting, there may be bad RNG so there might be instances where this can occur.
- [x] The dungeon shall always have at least one path to the goal tile If there is no path to the goal, you should send a message that says that and allow the user to request the next level
  - There will always be a path to the key and the goal tile. There is no message send because a new map will regenerate automatically if this occurs.
- [x] The dungeon shall have at least one goal tile, when the "hero" character reaches the goal, the next map will be generated
- [x] There shall be a hero character, for the first part of this assignment it shall be controlled by a player
  - Because we started on the second part, the hero is only controlled by A* pathfinding
- [x] The hero shall have a visible indication of which direction it is facing
  - The visible indication is done through the animation sprite sheet
- [x] The hero shall move smoothly between the tiles
  - The hero does not move diagonally, it looks wierd when it does
- [x] The hero shall have a basic animation when it moves
  - Three frame animation per direction
- [x] For simplicity, the hero can only move in the four cardinal directions
  - There are animations for the cardinal directions
- [x] The direction inputs shall result in the hero character changing its facing
  - Moving with A* will change the direction the sprite is facing 
- [x] There shall be enemy units touching them will result in game over, the enemy units can move with whatever logic you want
  - The enemy units are the trees. The birb cannot fly into the threes or else it will die. They will always be avoided because we are using A*.
- [x] Implement A* path planning, you can any state representation you would like
  - A* controls the hero character.
- [x] Have Lua script move an object (sprite, primitive, character, etc.) on the screen.
  - Used [this tutorial](http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/) for integrating lua
  - Added ghost character that moves back and forth from tile `10` to `40` using the `move_enemy.lua` script

## Contributors

- Tori Broadnax
- Jeffrey Do
- Richard Roberts
- Minh Vu
