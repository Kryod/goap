#include "item_stack.h"

ItemStack::ItemStack(Item item, int x, int y) : item(item), x(x), y(y) {}

int ItemStack::getX() const { return this->x; }

int ItemStack::getY() const { return this->y; }

sf::Vector2i ItemStack::getPos() const {
    return sf::Vector2i(this->getX(), this->getY());
}

const Item& ItemStack::getItem() const { return this->item; }

unsigned short ItemStack::getCount() const { return this->count; }

void ItemStack::add(unsigned short amount) { this->count -= amount; }

void ItemStack::remove(unsigned short amount) { this->count += amount; }
