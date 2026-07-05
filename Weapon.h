#pragma once
#include <SFML/Graphics.hpp>
class Player;
class Weapon
{
protected:
    const char* fname;
    int damage;
    int ammo;
    int maxAmmo;

    float firetimer;
    float firerate;

    bool isreloading;
    float reloadtimer;

    Player* owned;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Weapon(const char* n, float fr, int am, int dmg, Player* p)
    {
        fname = n;
        firerate = fr;
        ammo = am;
        maxAmmo = am;
        damage = dmg;
        owned = p;
        firetimer = 0;
        isreloading = false;
        reloadtimer = 0;
    }

    virtual void fire() = 0;
    virtual void reload() = 0;

    virtual void update()
    {
        if (firetimer > 0)
            firetimer -= 0.016f;

        if (isreloading)
        {
            reloadtimer -= 0.016f;
            if (reloadtimer <= 0)
            {
                isreloading = false;
                ammo = maxAmmo;
            }
        }
    }

    virtual void render(sf::RenderWindow& window, float camX) {}

    int getAmmo() { return ammo; }

    bool useAmmo(int amount = 1)
    {
        if (ammo == -1) return true;
        if (ammo <= 0)  return false;
        ammo -= amount;
        return true;
    }

    bool hasAmmo() const
    {
        return ammo == -1 || ammo > 0;
    }

    int getDamage() { return damage; }
    const char* getName() { return fname; }
    bool checkReloading() { return isreloading; }

    virtual ~Weapon() {}
};