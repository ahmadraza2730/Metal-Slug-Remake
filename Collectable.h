#pragma once
#include <SFML/Graphics.hpp>
class Player;
class CollectableManager;

class Collectable
{
protected:
    float x, y;
    float width, height;
    bool active;
    sf::Texture texture;
    sf::Sprite  sprite;

public:
    Collectable(float x, float y, float w, float h)
        : x(x), y(y), width(w), height(h), active(true) {
    }

    virtual void onCollect(Player* player) = 0;
    virtual void update() {}

    // override this to spawn extra collectables (e.g. POW crate drop)
    // returns nullptr by default — no cast needed
    virtual Collectable* spawnExtra() { return nullptr; }

    void loadTexture(const char* path)
    {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }

    virtual void draw(sf::RenderWindow& window, float camX)
    {
        if (!active) return;
        sprite.setPosition(x - camX, y);
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const
    {
        return sf::FloatRect(x, y, width, height);
    }

    bool isActive()   const { return active; }
    void deactivate() { active = false; }

    float getX() const { return x; }
    float getY() const { return y; }

    virtual ~Collectable() {}
};