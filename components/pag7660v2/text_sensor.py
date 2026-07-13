import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID

from . import pag7660v2_ns, PAG7660V2Component

CONF_GESTURE = "gesture"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_ID): cv.use_id(PAG7660V2Component),
    cv.Required(CONF_GESTURE): text_sensor.text_sensor_schema(),
})

async def to_code(config):
    hub = await cg.get_variable(config[CONF_ID])
    sens = await text_sensor.new_text_sensor(config[CONF_GESTURE])
    cg.add(hub.set_gesture_text_sensor(sens))