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

std::map<std::string, Item> World::itemTypes { { "tool", Tool },
                                            { "tree", Tree },
                                            { "woodlog", WoodLog },
                                            { "woodsticks", WoodStick },
                                            { "chopping_block", ChoppingBlock }  };

std::map<std::string, std::string> World::stateMap { { "tool", "has_tool" },
                                            { "tree", "tree_available" },
                                            { "woodlog", "has_wood_logs" },
                                            { "woodsticks", "has_sticks" },
                                            { "chopping_block", "chopping_block_available" }  };

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

std::unordered_set<std::string> World::getState() {
    std::unordered_set<std::string> states;

    for (const ItemStack& stack : this->itemStacks) {
        std::map<std::string, Item>::iterator findResult = std::find_if(std::begin(this->itemTypes), std::end(this->itemTypes), [&](const std::pair<std::string, Item> &pair)
        {
            return pair.second == stack.getItem();
        });
        if (findResult != std::end(itemTypes)) {
            states.emplace(this->stateMap[findResult->first]);
        }
    }

    return states;
}
