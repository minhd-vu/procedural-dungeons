import sys
import argparse
import random

size = (50, 50)

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
    def __init__(self, x: int, y: int, width: int, height: int):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def intersects(self, other) -> bool:
        return not (
            self.x + self.width < other.x or
            self.x > other.x + other.width or
            self.y > other.y + other.height or
            self.y + self.height < other.y
        )

    def contains(self, other) -> bool:
        return (
            self.x < other.x < other.x + other.width < self.x + self.width and
            self.y < other.y < other.y + other.height < self.y + self.height
        )

    def contains(self, x: int, y: int) -> bool:
        return (
            self.x <= x <= self.x + self.width and
            self.y <= y <= self.y + self.height
        )

    def __str__(self) -> str:
        return f'Rectangle({self.x},{self.y},{self.width},{self.height})'


def room_with_borders(room: Rectangle) -> Rectangle:
    return Rectangle(room.x - 1, room.y - 1, room.width + 1, room.height + 1)


def get_neighbors(level: list, x: int, y: int):
    neighbors = list()
    # right
    if x + 1 < size[0] and not level[x + 1][y]:
        neighbors.append((x + 1, y))
    # left
    if x - 1 < 0 and not level[x - 1][y]:
        neighbors.append((x - 1, y))
    # up
    if y - 1 < 0 and not level[x][y - 1]:
        neighbors.append((x, y - 1))
    # down
    if y + 1 < size[1] and not level[x][y + 1]:
        neighbors.append((x, y + 1))
    return neighbors


def recursive_dfs(level: list, x: int, y: int, init=False) -> None:
    level[x][y] = 3
    neighbors = get_neighbors(level, x, y)
    random.shuffle(neighbors)
    for neighbor in neighbors:
        recursive_dfs(level, neighbor[0], neighbor[1])
        break


def room_contains(rooms: list, x: int, y: int) -> bool:
    return all([not room.contains(x, y) for room in rooms])


def generate_level() -> str:
    level = [[0 for i in range(size[0])] for j in range(size[1])]
    rooms = list()
    starts = list()

    for i in range(size[0] * size[1]):
        room_size = room_sizes[random.randrange(len(room_sizes))]

        if random.random() > 0.5:
            room_size = (room_size[1], room_size[0])

        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        room = Rectangle(x - 1, y - 1, room_size[0] + 2, room_size[1] + 2)

        collision = False
        for placed_room in rooms:
            if room.intersects(placed_room):
                collision = True
                break

        if not collision:
            rooms.append(room)

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

    for i in range(size[0]):
        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        if (room_contains(rooms, x, y)):
            recursive_dfs(level, x, y)

    return '\n'.join([' '.join([str(i) for i in row]) for row in level])


parser = argparse.ArgumentParser(description='Generate Procedural Dungeon')
parser.add_argument("output", help="output level file")
args = parser.parse_args()

with open(args.output, 'w') as output:
    output.write(generate_level())
