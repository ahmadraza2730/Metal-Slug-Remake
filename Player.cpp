#include "Player.h"
#include "World.h"

void Player::shoot(World* world)
{
    if (shootCooldown > 0) return;

    float bx = facingright ? x + width : x;
    float by = y + height / 2.0f;
    float vx = facingright ? 15.0f : -15.0f;
    world->spawnProjectile(new Bullet(bx, by, vx, 0.0f, true, this, pistolWeapon));
    shootCooldown = 15;
}

void Player::fireHMG(World* world)
{
    if (hmgWeapon == NULL || !hmgWeapon->hasAmmo()) return;
    if (!hmgWeapon->useAmmo(1)) return;

    float bx = facingright ? x + width : x;
    float by = y + height / 2.0f;
    float vx = facingright ? 20.0f : -20.0f;
    world->spawnProjectile(new Bullet(bx, by, vx, 0.0f, true, this, hmgWeapon));
}

void Player::fireRocket(World* world)
{
    if (shootCooldown > 0) return;
    if (rocketWeapon == NULL || !rocketWeapon->hasAmmo()) return;
    if (!rocketWeapon->useAmmo(1)) return;

    float rx = facingright ? x + width : x;
    float ry = y + height / 2.0f;
    float vx = facingright ? 11.0f : -11.0f;
    world->spawnProjectile(new RocketProjectile(rx, ry, vx, 0.0f, true, this, rocketWeapon));
    shootCooldown = 120;
}

void Player::fireFlame(World* world)
{
    if (shootCooldown > 0) return;
    if (flameWeapon == NULL || !flameWeapon->hasAmmo()) return;
    if (!flameWeapon->useAmmo(100)) return;

    world->spawnProjectile(new FlameProjectile(x, y, true, this, flameWeapon));
    shootCooldown = 240;
}

void Player::fireLaser(World* world)
{
    if (shootCooldown > 0) return;
    if (laserWeapon == NULL || !laserWeapon->hasAmmo()) return;
    if (!laserWeapon->useAmmo(1)) return;

    float lx = facingright ? x + width : x;
    float ly = y + height / 2.0f;
    world->spawnProjectile(new LaserProjectile(lx, ly, facingright, this, laserWeapon));
    shootCooldown = 60;
}

void Player::throwGrenade(World* world)
{
    if (grenadeCooldown > 0) return;
    if (grenadeCount <= 0) return;
    grenadeCount--;

    float gx = facingright ? x + width : x;
    float gy = y;
    world->spawnProjectile(new HandGrenadeProjectile(gx, gy, facingright, this, NULL));
    grenadeCooldown = 60;
}

void Player::throwFireBomb(World* world)
{
    if (grenadeCooldown > 0) return;
    if (grenadeCount <= 0) return;
    grenadeCount--;

    float gx = facingright ? x + width : x;
    float gy = y;
    world->spawnProjectile(new FireBombProjectile(gx, gy, facingright, this, NULL));
    grenadeCooldown = 60;
}