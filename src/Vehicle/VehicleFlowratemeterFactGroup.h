#pragma once

#include <FactGroup.h>
#include "QGCMAVLink.h"

class Vehicle;

///创建喷雾Fact组用于加载到Vehicle类里
class VehicleFlowRatemeterFactGroup : public FactGroup
{
    Q_OBJECT
public:
    explicit VehicleFlowRatemeterFactGroup(QObject *parent = nullptr);

    Q_PROPERTY(Fact* sprayState      READ sprayState    CONSTANT)
    Q_PROPERTY(Fact* flowRate        READ flowRate      CONSTANT)

    Fact* sprayState             () { return &_sprayStateFact; }
    Fact* flowRate               () { return &_flowRateFact; }

    static const char* _sprayStateFactName;
    static const char* _flowRateFactName;

private:
    Fact        _sprayStateFact;
    Fact        _flowRateFact;

};
