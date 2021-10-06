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
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def intersects(self, other):
        return not (
            self.x + self.width < other.x or
            self.x > other.x + other.width or
            self.y > other.y + other.height or
            self.y + self.height < other.y
        )

    def contains(self, other):
        return (
            self.x < other.x < other.x + other.width < self.x + self.width and
            self.y < other.y < other.y + other.width < self.y + self.width
        )

    def __str__(self):
        return f'Rectangle({self.x},{self.y},{self.width},{self.height})'


def generate_level() -> str:
    level = [[0 for i in range(size[0])] for j in range(size[1])]
    rooms = list()

    for i in range(size[0] * size[1]):
        room_size = room_sizes[random.randrange(len(room_sizes))]

        if random.random() > 0.5:
            room_size = (room_size[1], room_size[0])

        x = random.randrange(2, size[0] - room_size[0] - 1)
        y = random.randrange(2, size[1] - room_size[1] - 1)

        room = Rectangle(x - 1, y - 1, room_size[0] + 1, room_size[1] + 1)

        collision = False
        for placed_room in rooms:
            if room.intersects(placed_room):
                collision = True
                break

        if not collision:
            rooms.append(room)
            print(room)

    for room in rooms:
        for i in range(room.x, room.x + room.width):
            for j in range(room.y, room.y + room.height):
                level[i][j] = 1

    return '\n'.join([' '.join([str(i) for i in row]) for row in level])


parser = argparse.ArgumentParser(description='Generate Procedural Dungeon')
parser.add_argument("output", help="output level file")
args = parser.parse_args()

with open(args.output, 'w') as output:
    output.write(generate_level())
