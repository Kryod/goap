#include "world.h"
#include "texture_loader.h"
#include <cmath>

World::World(Map& map) : map(map) {
    TextureLoader& tl = TextureLoader::instance();

    this->itemSprites[WoodLog] =
        sf::Sprite(*tl.get("environment/medievalEnvironment_06"));
    this->itemSprites[WoodStick] = sf::Sprite(*tl.get("items/sticks"));
    this->itemSprites[Firewood] = sf::Sprite(*tl.get("items/firewood"));
    this->itemSprites[Tool] = sf::Sprite(*tl.get("items/pick_iron"));
    this->itemSprites[Tree] =
        sf::Sprite(*tl.get("environment/medievalEnvironment_02"));
    this->itemSprites[ChoppingBlock] =
        sf::Sprite(*tl.get("items/chopping_block"));
}

World* World::instance = nullptr;

std::map<std::string, Item> World::itemTypes { { "tool", Tool },
                                               { "tree", Tree },
                                               { "woodlog", WoodLog },
                                               { "woodsticks", WoodStick },
                                               { "chopping_block",
                                                 ChoppingBlock } };

std::map<Item, std::string> World::stateMap { { Tool, "has_tool" },
                                              { Tree, "tree_available" },
                                              { WoodLog, "has_wood_logs" },
                                              { WoodStick, "has_sticks" },
                                              { ChoppingBlock,
                                                "chopping_block_available" } };

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

float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

ItemStack* World::getNearestItemStack(const Item item,
                                      const sf::Vector2f& pos) {
    ItemStack* nearest = nullptr;

    for (ItemStack& itemstack : this->itemStacks) {
        if (itemstack.getItem() == item) {
            sf::Vector2f moveTarget =
                static_cast<sf::Vector2f>(itemstack.getPos() * Map::TILE_SIZE);
            if (nearest == nullptr ||
                distance(pos, moveTarget) <
                    distance(pos, static_cast<sf::Vector2f>(nearest->getPos() *
                                                            Map::TILE_SIZE))) {
                nearest = &itemstack;
            }
        }
    }

    return nearest;
}

std::unordered_set<std::string> World::getState() const {
    std::unordered_set<std::string> states;

    for (const ItemStack& stack : this->itemStacks) {
        std::map<Item, std::string>::iterator findResult =
            this->stateMap.find(stack.getItem());
        if (findResult != std::end(this->stateMap)) {
            states.emplace(findResult->second);
        }
    }

    return states;
}
