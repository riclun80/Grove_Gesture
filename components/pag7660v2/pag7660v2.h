#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/component.h"


namespace esphome {
namespace pag7660v2 {

#define GESTURE_MAX_TIPS 5

#pragma pack(push, 1)
typedef struct {
  uint8_t palm : 1;
  uint8_t tips : GESTURE_MAX_TIPS;
  uint8_t __rsv : 2;
} pag7660_reg_valid_t;

typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t r;
  uint8_t b;
} pag7660_reg_palm_t;

typedef struct {
  uint8_t palm : 1;
  uint8_t tips : GESTURE_MAX_TIPS;
  uint8_t __rsv : 2;
} pag7660_reg_bit8_t;

typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t b;
  uint8_t id : 3;
  uint8_t __rsv : 5;
} pag7660_reg_tip_t;

typedef struct {
  struct {
    uint8_t thumb_up : 1;
    uint8_t cursor_type : 2;
    uint8_t gesture_type : 5;
    uint8_t select : 1;
    uint8_t __rsv : 2;
    uint8_t zoom : 5;
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t thumb_down : 1;
    uint8_t __rsv2 : 7;
  } ges;
  int16_t ang_acc;
  struct {
    uint8_t binning : 1;
    uint8_t __rsv : 7;
    uint8_t x;
    uint8_t y;
  } crop;
  struct {
    uint8_t x : 3;
    uint8_t y : 3;
    uint8_t __rsv : 2;
  } cursor_hb;
} pag7660_reg_result_t;

typedef struct {
  pag7660_reg_valid_t valid;
  pag7660_reg_palm_t palm;
  pag7660_reg_bit8_t bit8[2];
  pag7660_reg_tip_t tips[GESTURE_MAX_TIPS];
  pag7660_reg_result_t result;
} pag7660_reg_out_t;
#pragma pack(pop)

class PAG7660V2Component : public Component, public i2c::I2CDevice {
public:
  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_gesture_text_sensor(text_sensor::TextSensor *s) {
    gesture_text_sensor_ = s;
  }
  void set_rotation_sensor(sensor::Sensor *s) { rotation_sensor_ = s; }

protected:
  text_sensor::TextSensor *gesture_text_sensor_{nullptr};
  sensor::Sensor *rotation_sensor_{nullptr};
  void process_gesture(const pag7660_reg_out_t &reg);
};

} // namespace pag7660v2
} // namespace esphome