# Grove Smart IR Gesture Sensor (PAJ7660) for use in ESPHome

<img src=https://files.seeedstudio.com/wiki/grove-gesture-paj7620/13.png width=300> <img src=https://files.seeedstudio.com/wiki/grove-gesture-paj7620/hardware.png width=300>

[Grove Smart IR Gesture Sensor (PAJ7660)](https://www.seeedstudio.com/Grove-Smart-IR-Gesture-Sensor-p-5721.html)

**Description**<br>
The sensor on the Grove Smart IR Gesture Sensor (PAJ7660/PAG7660) integrates a gesture recognition function with a I2C/SPI/USB interface configurable by DIP switches.<br>
It has 2 IR LED's, so it recognises gestures in complete darkness!<br>
This code utilises the I2C interface and can recognise 17 types of gestures, such as:<br> 
Static finger 1 to 5, Push finger 1 to 5, Clockwise rotation, Counter-clockwise rotation, Swipe Left, Swipe Right, Tap, Grab, Pinch.

**Device setup**<br>
Place the files in the ESPHome folder so the component files end up under \esphome\components\pag7660v2<br>
Add the lines in your device's config to get a "text sensor" with the last **gesture** and a "sensor" with **rotation step**.<br>
```
external_components:
  - source:
      type: local
      path: components

i2c:
  scl: GPIO5 # Change for your setup
  sda: GPIO4 # Change for your setup
  scan: true
  frequency: 200kHz
  id: i2c_bus

pag7660v2:
  id: my_gesture_sensor
  address: 0x68
  i2c_id: i2c_bus

text_sensor:
  - platform: pag7660v2
    gesture:
      name: "Gesture Sensor"
      
sensor:
  - platform: pag7660v2
    rotation:
      name: "Gesture Rotation Step"
      unit_of_measurement: "°"
```

In [home assistant automation.yaml](https://github.com/riclun80/Grove_Gesture_PAJ7660_ESPhome/blob/master/home%20assistant%20automation.yaml) you find an example automation that I utilise for my device installed in my bedroom projector clock.<br>

For more information about the sensor, please visit the [wiki](https://wiki.seeedstudio.com/grove_gesture_paj7660/).


---
Original Arduino software is written by [Jack Wu](https://github.com/Seeed-Studio/Grove_Gesture) for Seeed Studio. This software is modified by me+Gemini to be used in ESPHome
ESP-IDF framework external component and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check LICENSE for more information.<br>
