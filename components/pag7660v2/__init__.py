import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["sensor", "text_sensor"]

pag7660v2_ns = cg.esphome_ns.namespace("pag7660v2")
PAG7660V2Component = pag7660v2_ns.class_("PAG7660V2Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PAG7660V2Component),
}).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x68))

async def to_code(config):
    # Fix applied here: Use cg.new_Pvariable instead
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)