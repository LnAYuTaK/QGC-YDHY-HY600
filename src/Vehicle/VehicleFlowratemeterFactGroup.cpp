#include "VehicleFlowratemeterFactGroup.h"
#include "Vehicle.h"

const char* VehicleFlowRatemeterFactGroup::_sprayStateFactName="sprayState";
const char* VehicleFlowRatemeterFactGroup::_flowRateFactName=  "flowRate";


VehicleFlowRatemeterFactGroup::VehicleFlowRatemeterFactGroup(QObject *parent)
    : FactGroup{1000, ":/json/Vehicle/FlowRateMeterFact.json", parent}
    , _sprayStateFact            (0, _sprayStateFactName,           FactMetaData::valueTypeUint8)
    , _flowRateFact              (0, _flowRateFactName,             FactMetaData::valueTypeDouble)
{
    _addFact(&_sprayStateFact, _sprayStateFactName);
    _addFact(&_flowRateFact,_flowRateFactName);
    _sprayStateFact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _flowRateFact.setRawValue(std::numeric_limits<float>::quiet_NaN());
}
