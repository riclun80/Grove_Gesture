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
  delay(10);
  this->write_byte(0x22, 0x05); // Default Mode: Combined Mode[cite: 3, 5]
  delay(10);
  this->write_byte(0x0A, 0x01); // Enable Core[cite: 1]
  delay(250);

  ESP_LOGI(TAG, "PAG7660v2 Component initialized successfully!");
}

void PAG7660V2Component::loop() {
  uint8_t ready_flag;
  if (!this->read_byte(0x04, &ready_flag) || !(ready_flag & 0x02)) {
    return; // Frame output not available[cite: 1]
  }

  pag7660_reg_out_t raw_data;
  if (this->read_bytes(0x3C, (uint8_t *)&raw_data,
                       sizeof(raw_data))) { //[cite: 1]
    this->process_gesture(raw_data);
  }

  this->write_byte(0x04, 0x00); // Clear data interrupt ready states[cite: 1]
}

void PAG7660V2Component::process_gesture(const pag7660_reg_out_t &reg) {
  uint8_t type = reg.result.ges.gesture_type;       //[cite: 1]
  int16_t rotate = reg.result.ang_acc;              //[cite: 1]
  uint8_t cursor_type = reg.result.ges.cursor_type; //[cite: 1]
  bool select = reg.result.ges.select;              //[cite: 1]

  std::string gesture_name = "";

  switch (type) {
  case 0:
    if (select) { //[cite: 5]
      if (cursor_type == 1)
        gesture_name = "Tap"; //[cite: 5]
      else if (cursor_type == 2)
        gesture_name = "Grab"; //[cite: 5]
      else if (cursor_type == 3)
        gesture_name = "Pinch"; //[cite: 5]
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    gesture_name = std::to_string(type) + "-finger"; //[cite: 5]
    break;
  case 6:
    gesture_name = "Rotate Right"; //[cite: 5]
    if (this->rotation_sensor_ != nullptr)
      this->rotation_sensor_->publish_state(rotate);
    break;
  case 7:
    gesture_name = "Rotate Left"; //[cite: 5]
    if (this->rotation_sensor_ != nullptr)
      this->rotation_sensor_->publish_state(rotate);
    break;
  case 8:
    gesture_name = "Swipe Left"; //[cite: 5]
    break;
  case 9:
    gesture_name = "Swipe Right"; //[cite: 5]
    break;
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
    gesture_name = std::to_string(type - 19 + 1) + "-finger push"; //[cite: 5]
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