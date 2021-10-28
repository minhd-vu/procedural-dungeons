#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Node.hpp"
#include <vector>
#include <array>
#include <limits>
#include <float.h>
#include <stack>
#include <queue>

// generate a tile map
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string tileset,
              sf::Vector2u tileSize,
              const std::string level,
              unsigned int width,
              unsigned int height)
    {
        this->tileSize = tileSize;
        this->width = width;
        this->height = height;

        tiles.clear();

        std::ifstream in(level, std::ios::in);
        int number;
        while (in >> number)
        {
            tiles.push_back(number);
        }
        in.close();

        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int index = i + j * width;
                int tileNumber = tiles[index];

                // hardcode here to determine where the player spawns
                switch (tileNumber)
                {
                case 0:
                    tileNumber = 1;
                    break;
                case 1:
                    tileNumber = 0;
                    break;
                case 3:
                    tileNumber = 0;
                    break;
                case 4:
                    goal = sf::Vector2u(i, j);
                    break;
                case 5:
                    key = sf::Vector2u(i, j);
                    break;
                case 9:
                    tileNumber = 0;
                    start = sf::Vector2u(i, j);
                    break;
                default:
                    break;
                }

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex *quad = &m_vertices[index * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

    unsigned int getWidth() const
    {
        return width;
    }

    unsigned int getHeight() const
    {
        return height;
    }

    sf::Vector2u getTileSize() const
    {
        return tileSize;
    }

    std::vector<int> &getTiles()
    {
        return tiles;
    }

    sf::VertexArray& getVertices()
    {
        return m_vertices;
    }

    // a* pathfinding
    std::queue<Node> getPath(sf::Vector2u start, sf::Vector2u dest, std::queue<Node> &queue)
    {
        std::queue<Node> empty;
        std::vector<std::vector<bool>> closed(width, std::vector<bool>(height));
        std::vector<std::vector<Node>> nodes(width, std::vector<Node>(height));

        // initialize the map
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                nodes[x][y].f = FLT_MAX;
                nodes[x][y].g = FLT_MAX;
                nodes[x][y].h = FLT_MAX;
                nodes[x][y].parent.x = -1;
                nodes[x][y].parent.y = -1;
                nodes[x][y].position.x = x;
                nodes[x][y].position.y = y;

                closed[x][y] = false;
            }
        }

        // initial starting position
        int x = start.x;
        int y = start.y;
        nodes[x][y].f = 0.0;
        nodes[x][y].g = 0.0;
        nodes[x][y].h = 0.0;
        nodes[x][y].parent.x = x;
        nodes[x][y].parent.y = y;

        std::vector<Node> open;
        open.emplace_back(nodes[x][y]);

        while (!open.empty() && open.size() < width * height)
        {
            Node node;
            // get the minimum f cost node
            do
            {
                float temp = FLT_MAX;
                std::vector<Node>::iterator itn;
                for (std::vector<Node>::iterator it = open.begin(); it != open.end(); it = next(it))
                {
                    Node n = *it;
                    if (n.f < temp)
                    {
                        temp = n.f;
                        itn = it;
                    }
                }
                node = *itn;
                open.erase(itn);
            } while (isValid(node.position.x, node.position.y) == false);

            x = node.position.x;
            y = node.position.y;
            closed[x][y] = true;

            // for each neighbor starting from NW to SE
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    // prevent from going diagonally
                    if (abs(dx) == abs(dy))
                    {
                        continue;
                    }

                    double g, h, f;
                    if (isValid(x + dx, y + dy))
                    {
                        if (isDestination(x + dx, y + dy, dest))
                        {
                            // found destination
                            nodes[x + dx][y + dy].parent.x = x;
                            nodes[x + dx][y + dy].parent.y = y;

                            try
                            {
                                int x = dest.x;
                                int y = dest.y;
                                std::stack<Node> stack;
                                // std::queue<Node> queue;

                                while (!(nodes[x][y].parent.x == x && nodes[x][y].parent.y == y) &&
                                       nodes[x][y].position.x != -1 && nodes[x][y].position.y != -1)
                                {
                                    stack.push(nodes[x][y]);
                                    sf::Vector2i temp = sf::Vector2i(nodes[x][y].parent.x, nodes[x][y].parent.y);
                                    x = temp.x;
                                    y = temp.y;
                                }
                                stack.push(nodes[x][y]);

                                while (!stack.empty())
                                {
                                    Node top = stack.top();
                                    stack.pop();
                                    queue.push(top);
                                }

                                return queue;
                            }
                            catch (const std::exception &e)
                            {
                                std::cout << e.what() << "\n";
                            }
                        }
                        else if (closed[x + dx][y + dy] == false)
                        {
                            g = node.g + 1.0;
                            h = calculateH(x + dx, y + dy, dest);
                            f = g + h;

                            // check if there is better path
                            if (nodes[x + dx][y + dy].f == FLT_MAX ||
                                nodes[x + dx][y + dy].f > f)
                            {
                                // update neighbors
                                nodes[x + dx][y + dy].f = f;
                                nodes[x + dx][y + dy].g = g;
                                nodes[x + dx][y + dy].h = h;
                                nodes[x + dx][y + dy].parent.x = x;
                                nodes[x + dx][y + dy].parent.y = y;
                                open.emplace_back(nodes[x + dx][y + dy]);
                            }
                        }
                    }
                }
            }
        }

        return empty;
    }

    sf::Vector2u getStart() const
    {
        return start;
    }

    sf::Vector2u getGoal() const
    {
        return goal;
    }

    sf::Vector2u getKey() const
    {
        return key;
    }

private:
    bool isValid(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < width && y < height && tiles[x + y * width] != 2 && tiles[x + y * width];
    }

    bool isDestination(int x, int y, sf::Vector2u dest) const
    {
        return x == dest.x && y == dest.y;
    }

    double calculateH(int x, int y, sf::Vector2u dest) const
    {
        return sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y));
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u tileSize;
    unsigned int width, height;
    std::vector<int> tiles;
    sf::Vector2u start, goal, key;
};

#endif // TILEMAP_H