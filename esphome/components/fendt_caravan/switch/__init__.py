import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import CONF_TYPE

from .. import CONF_KEY_NAME, CONF_PARENT_ID, CaravanDeviceComponent, fendt_caravan_ns

FendtSwitch = fendt_caravan_ns.class_(
    "FendtSwitch",
    switch.Switch,
    cg.Component,
    cg.Parented.template(CaravanDeviceComponent),
)


def _switch_schema(icon: str = cv.UNDEFINED, key_name_=cv.UNDEFINED) -> cv.Schema:
    return switch.switch_schema(FendtSwitch).extend(
        {
            cv.Required(CONF_PARENT_ID): cv.use_id(CaravanDeviceComponent),
            cv.Optional(CONF_KEY_NAME, default=key_name_): cv.string,
        }
    )


CONFIG_SCHEMA = cv.typed_schema(
    {
        "main_switch": _switch_schema(icon="mdi:switch", key_name_="MAIN_SWITCH"),
        "light_dusche": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DUSCHE"),
        "light_wasch": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_WASCH"),
        "light_amb1": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_AMB1"),
        "light_amb2": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_AMB2"),
        "light_amb3": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_AMB3"),
        "light_zusatzl": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_ZUSATZL"),
        "light_zusatzr": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_ZUSATZR"),
        "light_kueche": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_KUECHE"),
        "light_kueche2": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_KUECHE2"),
        "light_aussen": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_AUSSEN"),
        "light_dim0": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DIM0"),
        "light_dim1": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DIM1"),
        "light_dim2": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DIM2"),
        "light_dim3": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DIM3"),
        "light_dim4": _switch_schema(icon="mdi:lamp", key_name_="LIGHT_DIM4"),
        "all_lights": _switch_schema(icon="mdi:lamp", key_name_="ALL_LIGHTS_SWITCH"),
        "floor_heater": _switch_schema(
            icon="mdi:heat-wave", key_name_="FLOOR_HEATER_ON"
        ),
        "therme_on": _switch_schema(icon="mdi:thermometer", key_name_="THERME_ON"),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_PARENT_ID])
    var = await switch.new_switch(config)
    if CONF_KEY_NAME in config:
        cg.add(var.set_key_name(config[CONF_KEY_NAME]))
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)
    cg.add(getattr(parent, f"set_{config[CONF_TYPE]}_switch")(var))
