#include "item_stack.h"

ItemStack::ItemStack(Item item, int x, int y) : item(item), x(x), y(y) {}

const Item& ItemStack::getItem() const { return this->item; }

unsigned short ItemStack::getCount() const { return this->count; }

void ItemStack::add(unsigned short amount) { this->count -= amount; }

void ItemStack::remove(unsigned short amount) { this->count += amount; }
