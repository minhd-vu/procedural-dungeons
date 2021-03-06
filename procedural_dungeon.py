import sys
import argparse
import random
from typing import List, Tuple

# hard code the level because room size are somewhat dependent on it
size = (50, 50)

# define the types of rooms we want to have in our level
room_sizes = [
    (6, 6),
    (6, 5),
    (6, 4),
    (5, 5),
    (4, 5),
    (4, 4),
    (3, 4),
    (3, 3),
]


class Rectangle:
    def __init__(self, x: int, y: int, width: int, height: int) -> None:
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def intersects(self, other) -> bool:
        # if two rectangles intersect
        return not (
            self.x + self.width < other.x or
            self.x > other.x + other.width or
            self.y > other.y + other.height or
            self.y + self.height < other.y
        )

    def contains(self, other) -> bool:
        # if rectangle contains another rectangle
        return (
            self.x < other.x < other.x + other.width < self.x + self.width and
            self.y < other.y < other.y + other.height < self.y + self.height
        )

    def contains(self, x: int, y: int) -> bool:
        # if rectangle contains a point
        return (
            self.x <= x <= self.x + self.width and
            self.y <= y <= self.y + self.height
        )

    def corner(self, x: int, y: int) -> bool:
        # check if a point is a corner
        return (
            (x == self.x and y == self.y) or
            (x == self.x and y == self.y + self.height - 1) or
            (x == self.x + self.width - 1 and y == self.y) or
            (x == self.x + self.width - 1 and y == self.y + self.height - 1)
        )

    def __str__(self) -> str:
        return f'Rectangle({self.x},{self.y},{self.width},{self.height})'


def get_neighbors(level: List[int], x: int, y: int):
    # get all neighbors of the given tile that are not conflicting
    neighbors = list()
    direction = list()

    # up
    if y - 1 >= 0:
        neighbors.append((x, y - 1, 0))
    # down
    if y + 1 < size[1]:
        neighbors.append((x, y + 1, 1))
    # left
    if x - 1 >= 0:
        neighbors.append((x - 1, y, 2))
    # right
    if x + 1 < size[0]:
        neighbors.append((x + 1, y, 3))

    return neighbors


def is_level_border(level: List[int], x: int, y: int):
    return x == 0 or x == size[0] - 1 or y == 0 or y == size[1] - 1


def is_valid(level: List[int], x: int, y: int, values: List[int]):
    return (
        not level[x][y] and
        not is_level_border(level, x, y)
    )


def recursive_dfs(level: List[int], x: int, y: int, init: bool = False, direction: int = None) -> None:
    # recursive depth first search to determine the paths
    level[x][y] = 3
    neighbors = get_neighbors(level, x, y)

    random.shuffle(neighbors)

    # choose a random direction to go in
    if (direction is None):
        direction = random.randrange(len(neighbors))
    else:
        for i in range(len(neighbors)):
            if (neighbors[i][2] == direction):
                direction = i
                break

    for i in range(len(neighbors)):
        neighbor = neighbors[(i + direction) % len(neighbors)]
        if is_valid(level, neighbor[0], neighbor[1], [0]):
            recursive_dfs(level, neighbor[0], neighbor[1], direction=neighbor[2])
            # break because we only want to go in one direction
            break


def find_path(level: List[int], x: int, y: int, end_x: int, end_y: int, visited: List[bool]) -> bool:
    visited[x][y] = True
    neighbors = get_neighbors(level, x, y)

    for neighbor in neighbors:
        if end_x == neighbor[0] and end_y == neighbor[1]:
            return True
        elif (level[neighbor[0]][neighbor[1]] and
              level[neighbor[0]][neighbor[1]] != 2 and
              not visited[neighbor[0]][neighbor[1]]):
            return find_path(level, neighbor[0], neighbor[1], end_x, end_y, visited)
    return False


def create_door(level: List[int], room: Rectangle) -> None:
    for i in range(room.x, room.x + room.width):
        for j in range(room.y, room.y + room.height):
            if level[i][j] == 2 and not room.corner(i, j):
                for neighbor in get_neighbors(level, i, j):
                    if level[neighbor[0]][neighbor[1]] == 3:
                        level[i][j] = 3
                        return


def room_contains(rooms: List[Rectangle], x: int, y: int) -> bool:
    return all([not room.contains(x, y) for room in rooms])


# ensure that therer is a path from the start to the random position
def random_room_position(rooms: List[Rectangle], level, start) -> Tuple[int]:
    for i in range(size[0]):
        visited = [[False for i in range(size[0])] for j in range(size[1])]
        rand_room = rooms[random.randrange(len(rooms))]
        x = random.randrange(rand_room.x + 1, rand_room.x + rand_room.width - 1)
        y = random.randrange(rand_room.y + 1, rand_room.y + rand_room.height - 1)

        if find_path(level, start[0], start[1], x, y, visited):
            return (x, y)

    return False


def generate_level() -> str:
    level = [[0 for i in range(size[0])] for j in range(size[1])]
    rooms = list()
    starts = list()

    for i in range(size[0] * size[1]):
        room_size = room_sizes[random.randrange(len(room_sizes))]

        # change the orientation of the room randomly
        if random.random() > 0.5:
            room_size = (room_size[1], room_size[0])

        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        # add borders to the room
        room = Rectangle(x - 1, y - 1, room_size[0] + 2, room_size[1] + 2)

        # only place the room if there is no collision
        collision = False
        for placed_room in rooms:
            if room.intersects(placed_room):
                collision = True
                break

        if not collision:
            rooms.append(room)

    # set some tiles as border tiles
    for room in rooms:
        # print(room, range(room.x, room.x + room.width))
        for i in range(room.x, room.x + room.width):
            for j in range(room.y, room.y + room.height):
                if (
                    i == room.x or
                    i == room.x + room.width - 1 or
                    j == room.y or
                    j == room.y + room.height - 1
                ):
                    level[i][j] = 2
                else:
                    level[i][j] = 1

    # create the paths
    for i in range(size[0]):
        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        if (room_contains(rooms, x, y)):
            starts.append((x, y))
            recursive_dfs(level, x, y)

    for room in rooms:
        # create the doors
        create_door(level, room)

        # clear borders
        for i in range(room.x, room.x + room.width):
            for j in range(room.y, room.y + room.height):
                if level[i][j] == 2:
                    level[i][j] = 0

    # add in booby traps
    for i in range(size[0]):
        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        if (level[x][y]):
            level[x][y] = 2

    # determine where the player starts
    # the player will always start somewhere that has a path
    start = starts[random.randrange(len(starts))]
    level[start[0]][start[1]] = 9

    # generate the goal and key tile
    goal = random_room_position(rooms, level, start)
    key = starts[random.randrange(len(starts))]

    if goal and key and goal != key != start:
        level[goal[0]][goal[1]] = 4
        level[key[0]][key[1]] = 5
        # create the text file string
        return '\n'.join([' '.join([str(i) for i in row]) for row in level])

    return generate_level()


# use for help with cli interaction
parser = argparse.ArgumentParser(description='Generate Procedural Dungeon')
parser.add_argument("output", help="output level file")
args = parser.parse_args()

# write the level to a file
with open(args.output, 'w') as output:
    output.write(generate_level())
