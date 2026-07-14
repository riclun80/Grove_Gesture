#include "pag7660v2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pag7660v2 {

static const char *const TAG = "pag7660v2";

void PAG7660V2Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up PAG7660v2 Gesture Sensor...");

  uint8_t id_h, id_l;
  if (!this->read_byte(0x01, &id_h) || !this->read_byte(0x00, &id_l)) {
    this->mark_failed();
    ESP_LOGE(TAG, "Communication over I2C failed while reading ID.");
    return;
  }

  uint16_t id = (id_h << 8) | id_l;
  if (id != 0x7660) {
    this->mark_failed();
    ESP_LOGE(TAG, "Incorrect Chip ID verified: 0x%04X (Expected 0x7660)", id);
    return;
  }

  this->write_byte(0x10, 0x04);
  esphome::delay(10);
  this->write_byte(0x22, 0x05); // Default Mode: Combined Mode
  esphome::delay(10);
  this->write_byte(0x0A, 0x01); // Enable Core
  esphome::delay(250);

  ESP_LOGI(TAG, "PAG7660v2 Component initialized successfully!");
}

void PAG7660V2Component::loop() {
  uint8_t ready_flag;
  if (!this->read_byte(0x04, &ready_flag) || !(ready_flag & 0x02)) {
    return; // Frame output not available
  }

  pag7660_reg_out_t raw_data;
  if (this->read_bytes(0x3C, (uint8_t *)&raw_data, sizeof(raw_data))) {
    this->process_gesture(raw_data);
  }

  this->write_byte(0x04, 0x00); // Clear data interrupt ready states
}

void PAG7660V2Component::process_gesture(const pag7660_reg_out_t &reg) {
  uint8_t type = reg.result.ges.gesture_type;
  int16_t rotate = reg.result.ang_acc;
  uint8_t cursor_type = reg.result.ges.cursor_type;
  bool select = reg.result.ges.select;

  std::string gesture_name = "";

  switch (type) {
  case 0:
    if (select) {
      if (cursor_type == 1)
        gesture_name = "Tap";
      else if (cursor_type == 2)
        gesture_name = "Grab";
      else if (cursor_type == 3)
        gesture_name = "Pinch";
    }
    break;

  // Static mapping to prevent runtime exceptions
  case 1:
    gesture_name = "1-finger";
    break;
  case 2:
    gesture_name = "2-finger";
    break;
  case 3:
    gesture_name = "3-finger";
    break;
  case 4:
    gesture_name = "4-finger";
    break;
  case 5:
    gesture_name = "5-finger";
    break;

  case 6:
    gesture_name = "Rotate Right";
    if (this->rotation_sensor_ != nullptr)
      this->rotation_sensor_->publish_state(rotate);
    break;
  case 7:
    gesture_name = "Rotate Left";
    if (this->rotation_sensor_ != nullptr)
      this->rotation_sensor_->publish_state(rotate);
    break;
  case 8:
    gesture_name = "Swipe Left";
    break;
  case 9:
    gesture_name = "Swipe Right";
    break;

  // Static mapping for multi-finger push actions
  case 19:
    gesture_name = "1-finger push";
    break;
  case 20:
    gesture_name = "2-finger push";
    break;
  case 21:
    gesture_name = "3-finger push";
    break;
  case 22:
    gesture_name = "4-finger push";
    break;
  case 23:
    gesture_name = "5-finger push";
    break;

  default:
    break;
  }

  if (!gesture_name.empty() && this->gesture_text_sensor_ != nullptr) {
    this->gesture_text_sensor_->publish_state(gesture_name);
  }
}

} // namespace pag7660v2
} // namespace esphome
