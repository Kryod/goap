#include "world.h"
#include "texture_loader.h"

World::World(Map& map) : map(map) {
    TextureLoader& tl = TextureLoader::instance();

    this->itemSprites[WoodLog] =
        sf::Sprite(*tl.get("environment/medievalEnvironment_06"));
    this->itemSprites[WoodStick] = sf::Sprite(*tl.get("items/sticks"));
    this->itemSprites[Firewood] = sf::Sprite(*tl.get("items/firewood"));
    this->itemSprites[Tool] = sf::Sprite(*tl.get("items/pick_iron"));
    this->itemSprites[Tree] =
        sf::Sprite(*tl.get("environment/medievalEnvironment_02"));
}

World* World::instance = nullptr;

void World::addItemStack(const ItemStack& itemStack) {
    this->itemStacks.emplace_back(itemStack);
}

ItemStack* World::findItem(Item type) {
    for (ItemStack& stack : this->itemStacks) {
        if (stack.getItem() == type) {
            return &stack;
        }
    }
    return nullptr;
}

void World::draw(sf::RenderTarget& target) {
    this->map.draw(target);
    for (const ItemStack& stack : this->itemStacks) {
        sf::Sprite& sprite = this->itemSprites[stack.getItem()];
        sprite.setPosition(
            static_cast<sf::Vector2f>(stack.getPos() * Map::TILE_SIZE));
        target.draw(sprite);
    }
}
