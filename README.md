# Grove Smart IR Gesture Sensor (PAJ7660) for use in ESPHome

<img src=https://files.seeedstudio.com/wiki/grove-gesture-paj7620/main.jpg width=300>

[Grove - Gesture（PAJ7660)](https://www.seeedstudio.com/s/Grove-Gesture（PAJ7620U2）-p-2463.html)

**Description**

The sensor on the Grove Smart IR Gesture Sensor (PAJ7660) integrates a gesture recognition function with a general I2C/SPI/USB interface into a single chip. This code utilises the I2C interface.
It can recognise 15 gestures, including Static Finger, Push, Rotate, Tap, Pinch, Grab, and Swipe.
It has 2 IR LED's, so it recognises gestures in complete darkness!

Place the files in the ESPHome folder in the Home Assistant config directory so the component files end up under \esphome\components\pag7660v2
Add the lines in your ESP devices YAML to get a "text sensor" with the last gesture and a "sensor" with rotation step.

For more information, please visit the [wiki](https://wiki.seeedstudio.com/grove_gesture_paj7660/).


---
Original Arduino software is written by Jack Wu for Seeed Studio, and this software is modified by Richard Lundholm to be used in ESPHome<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check LICENSE for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed is a hardware innovation platform for makers to grow inspirations into differentiating products. By working closely with technology providers of all scale, Seeed provides accessible technologies with quality, speed and supply chain knowledge. When prototypes are ready to iterate, Seeed helps productize 1 to 1,000 pcs using in-house engineering, supply chain management and agile manufacture forces. Seeed also team up with incubators, Chinese tech ecosystem, investors and distribution channels to portal Maker startups beyond.
