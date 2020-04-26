#pragma once

#include <SFML/System/Vector2.hpp>

#include "item.h"

class ItemStack {
public:
    ItemStack(Item item, int x, int y);

    const Item& getItem() const;
    unsigned short getCount() const;
    int getX() const;
    int getY() const;
    sf::Vector2i getPos() const;

    void add(unsigned short amount);
    void remove(unsigned short amount);

private:
    Item item;
    int x;
    int y;
    unsigned short count;
};
