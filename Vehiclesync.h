#pragma once
#include "Vehicle.h"
#include "VehicleRider.h"
#include "Entity.h"

void syncRiderToVehicle(Vehicle* v, Entity* riderEntity)
{
    if (v == NULL || riderEntity == NULL) return;
    if (!v->isOccupied()) return;

    float riderX = v->getX() + (v->getWidth() / 2.0f) - (riderEntity->getWidth() / 2.0f);
    float riderY = v->getY() - riderEntity->getHeight();

    riderEntity->setX(riderX);
    riderEntity->setY(riderY);
}