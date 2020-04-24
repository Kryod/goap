#pragma once

#include "item.h"

class ItemStack {
public:
    ItemStack(Item item, int x, int y);

    const Item& getItem() const;
    unsigned short getCount() const;
    void add(unsigned short amount);
    void remove(unsigned short amount);

private:
    Item item;
    int x;
    int y;
    unsigned short count;
};
