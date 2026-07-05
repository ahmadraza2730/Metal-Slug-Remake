#pragma once

class VehicleRider
{
public:
    virtual void boardVehicle(class Vehicle* v) = 0;
    virtual void exitVehicle() = 0;
    virtual bool isInVehicle() = 0;
    virtual class Vehicle* getVehicle() = 0;
    virtual ~VehicleRider() {}
};