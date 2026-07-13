import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

from . import pag7660v2_ns, PAG7660V2Component

CONF_ROTATION = "rotation"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_ID): cv.use_id(PAG7660V2Component),
    cv.Required(CONF_ROTATION): sensor.sensor_schema(
        accuracy_decimals=0,
    ),
})

async def to_code(config):
    hub = await cg.get_variable(config[CONF_ID])
    sens = await sensor.new_sensor(config[CONF_ROTATION])
    cg.add(hub.set_rotation_sensor(sens))