#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
class Node
{
public:
    sf::Vector2u position;
    sf::Vector2u parent;
    float g;
    float h;
    float f;
};

static inline bool
operator<(const Node &l, const Node &r)
{
    return l.f < r.f;
}

#endif //NODE_H