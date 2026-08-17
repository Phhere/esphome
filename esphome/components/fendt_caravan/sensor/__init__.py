import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_TYPE,
    DEVICE_CLASS_BATTERY,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    ENTITY_CATEGORY_DIAGNOSTIC,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_EMPTY,
    UNIT_PERCENT,
    UNIT_VOLT,
)
from esphome.cpp_generator import MockObjClass

from .. import (
    CONF_KEY_NAME,
    CONF_PARENT_ID,
    CaravanDeviceComponent,
    FendtCaravan,
    fendt_caravan_ns,
)

ControlUnitDeviceSensor = fendt_caravan_ns.class_(
    "ControlUnitDeviceSensor",
    CaravanDeviceComponent,
    sensor.Sensor,
    cg.Parented.template(FendtCaravan),
)

FendtSensor = fendt_caravan_ns.class_(
    "FendtSensor",
    sensor.Sensor,
    cg.Component,
    cg.Parented.template(CaravanDeviceComponent),
)

IntFendtSensor = fendt_caravan_ns.class_(
    "IntFendtSensor",
    sensor.Sensor,
    cg.Component,
    cg.Parented.template(CaravanDeviceComponent),
)


def _device_schema(class_: MockObjClass, key_name_=cv.UNDEFINED) -> cv.Schema:
    return (
        sensor.sensor_schema(
            class_,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ).extend(
            {
                cv.Required(CONF_PARENT_ID): cv.use_id(FendtCaravan),
            }
        )
    ).extend(cv.COMPONENT_SCHEMA)


def _sensor_schema(
    class_: MockObjClass,
    unit_of_measurement: str = cv.UNDEFINED,
    accuracy_decimals: int = cv.UNDEFINED,
    device_class: str = cv.UNDEFINED,
    state_class: str = cv.UNDEFINED,
    key_name_: str = cv.UNDEFINED,
) -> cv.Schema:
    return (
        sensor.sensor_schema(
            class_,
            unit_of_measurement=unit_of_measurement,
            accuracy_decimals=accuracy_decimals,
            device_class=device_class,
            state_class=state_class,
        ).extend(
            {
                cv.Required(CONF_PARENT_ID): cv.use_id(CaravanDeviceComponent),
                cv.Optional(CONF_KEY_NAME, default=key_name_): cv.string,
            }
        )
    ).extend(cv.COMPONENT_SCHEMA)


CONFIG_SCHEMA = cv.typed_schema(
    {
        "mcu_device": _device_schema(ControlUnitDeviceSensor),
        "temp_in": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_TEMPERATURE,
            key_name_="TEMP_IN",
        ),
        "temp_out": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_TEMPERATURE,
            key_name_="TEMP_OUT",
        ),
        "battery_voltage": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_VOLTAGE,
            key_name_="UBAT",
        ),
        "battery_voltage2": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_VOLTAGE,
            key_name_="UBATM",
        ),
        "ibs0_ubat": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_VOLTAGE,
            key_name_="IBS0_UBAT",
        ),
        "ibs0_ibat": _sensor_schema(
            FendtSensor,
            unit_of_measurement="A",
            accuracy_decimals=2,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_CURRENT,
            key_name_="IBS0_IBAT",
        ),
        "battery_loading_status": _sensor_schema(
            IntFendtSensor,
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            key_name_="IBAT_BAL",
        ),
        "temp_in_offset": _sensor_schema(
            IntFendtSensor,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            key_name_="TEMP_IN_OFFSET",
        ),
        "temp_out_offset": _sensor_schema(
            IntFendtSensor,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            key_name_="TEMP_OUT_OFFSET",
        ),
        "ibs0_capacity": _sensor_schema(
            IntFendtSensor,
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            key_name_="IBS0_CAPACITY",
        ),
        "ibs0_soc2": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_PERCENT,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_BATTERY,
            key_name_="IBS0_SOC2",
        ),
        "ibs0_remaining_time": _sensor_schema(
            FendtSensor,
            unit_of_measurement="h",
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
            key_name_="IBS0_REMAINING_TIME",
        ),
        "ibs0_temp": _sensor_schema(
            FendtSensor,
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_TEMPERATURE,
            key_name_="IBS0_TEMPERATURE",
        ),
    }
)

AUTO_SENSOR_ENTITIES = [
    {"name": "temp_in", "key_name": "TEMP_IN", "unit": UNIT_CELSIUS, "accuracy_decimals": 1, "device_class": DEVICE_CLASS_TEMPERATURE, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "temp_out", "key_name": "TEMP_OUT", "unit": UNIT_CELSIUS, "accuracy_decimals": 1, "device_class": DEVICE_CLASS_TEMPERATURE, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "battery_voltage", "key_name": "UBAT", "unit": UNIT_VOLT, "accuracy_decimals": 2, "device_class": DEVICE_CLASS_VOLTAGE, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "battery_voltage2", "key_name": "UBATM", "unit": UNIT_VOLT, "accuracy_decimals": 2, "device_class": DEVICE_CLASS_VOLTAGE, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_ubat", "key_name": "IBS0_UBAT", "unit": UNIT_VOLT, "accuracy_decimals": 2, "device_class": DEVICE_CLASS_VOLTAGE, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_ibat", "key_name": "IBS0_IBAT", "unit": "A", "accuracy_decimals": 2, "device_class": DEVICE_CLASS_CURRENT, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "battery_loading_status", "key_name": "IBAT_BAL", "unit": UNIT_EMPTY, "accuracy_decimals": 0, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "temp_in_offset", "key_name": "TEMP_IN_OFFSET", "unit": UNIT_CELSIUS, "accuracy_decimals": 0, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "temp_out_offset", "key_name": "TEMP_OUT_OFFSET", "unit": UNIT_CELSIUS, "accuracy_decimals": 0, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_capacity", "key_name": "IBS0_CAPACITY", "unit": UNIT_EMPTY, "accuracy_decimals": 0, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_soc2", "key_name": "IBS0_SOC2", "unit": UNIT_PERCENT, "accuracy_decimals": 1, "device_class": DEVICE_CLASS_BATTERY, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_remaining_time", "key_name": "IBS0_REMAINING_TIME", "unit": "h", "accuracy_decimals": 1, "state_class": STATE_CLASS_MEASUREMENT},
    {"name": "ibs0_temp", "key_name": "IBS0_TEMPERATURE", "unit": UNIT_CELSIUS, "accuracy_decimals": 1, "device_class": DEVICE_CLASS_TEMPERATURE, "state_class": STATE_CLASS_MEASUREMENT},
]


async def _create_auto_sensor(parent, item):
    config = {
        "id": cg.new_id(f"fendt_auto_{item['name']}"),
        "name": item["name"],
        "unit_of_measurement": item["unit"],
        "accuracy_decimals": item["accuracy_decimals"],
    }
    if item.get("device_class") is not None:
        config["device_class"] = item["device_class"]
    if item.get("state_class") is not None:
        config["state_class"] = item["state_class"]
    var = await sensor.new_sensor(config)
    cg.add(var.set_key_name(item["key_name"]))
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)
    cg.add(getattr(parent, f"set_{item['name']}_sensor")(var))


async def to_code(config):
    parent = await cg.get_variable(config[CONF_PARENT_ID])
    var = await sensor.new_sensor(config)
    if CONF_KEY_NAME in config:
        cg.add(var.set_key_name(config[CONF_KEY_NAME]))
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)
    cg.add(getattr(parent, f"set_{config[CONF_TYPE]}_sensor")(var))

    if config[CONF_TYPE] == "mcu_device":
        for item in AUTO_SENSOR_ENTITIES:
            await _create_auto_sensor(parent, item)
