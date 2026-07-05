#include "FlameProjectile.h"
#include "Player.h"

void FlameProjectile::update()
{
    if (!active) return;
    x = firedBy->getX();
    y = firedBy->getY() + 40.0f;
    duration--;
    if (duration <= 0)
        active = false;
}

void FlameProjectile::draw(sf::RenderWindow& window, float camX)
{
    if (!active) return;
    if (firedBy->isFacingRight())
        shape.setPosition(x + firedBy->getWidth() - camX-20, y);
    else
        shape.setPosition(x - range - camX-60, y);
    window.draw(shape);
}

sf::FloatRect FlameProjectile::getBounds() const
{
    if (firedBy->isFacingRight())
        return sf::FloatRect(x + firedBy->getWidth(), y, range, 20.0f);
    else
        return sf::FloatRect(x - range, y, range, 20.0f);
}