# Grove Smart IR Gesture Sensor (PAJ7660) for use in ESPHome

<img src=https://files.seeedstudio.com/wiki/grove-gesture-paj7620/main.jpg width=300>

[Grove Smart IR Gesture Sensor (PAJ7660)](https://www.seeedstudio.com/Grove-Smart-IR-Gesture-Sensor-p-5721.html)

**Description**<br>
The sensor on the Grove Smart IR Gesture Sensor (PAJ7660/PAG7660) integrates a gesture recognition function with a I2C/SPI/USB interface configurable by DIP switches.<br>
It has 2 IR LED's, so it recognises gestures in complete darkness!<br>
This code utilises the I2C interface and can recognize 17 types of gestures, such as:<br> 
Static finger 1 to 5, Push finger 1 to 5, Clockwise rotation, Counter-clockwise rotation, Swipe Left, Swipe Right, Tap, Grab, Pinch.

**Setup**<br>
Place the files in the ESPHome folder so the component files end up under \esphome\components\pag7660v2<br>
Add the lines from "paj7660.yaml" in your devices config to get a "text sensor" with the last **gesture** and a "sensor" with **rotation step**.<br>
In "home assistant automation.yaml" you find example automation that I utilizes for my device installed in my bedroom projector clock.<br>

For more information about the sensor, please visit the [wiki](https://wiki.seeedstudio.com/grove_gesture_paj7660/).


---
Original Arduino software is written by [Jack Wu](https://github.com/Seeed-Studio/Grove_Gesture) for Seeed Studio, this software is modified by me+Gemini to be used in ESPHome
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check LICENSE for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed is a hardware innovation platform for makers to grow inspirations into differentiating products. By working closely with technology providers of all scale, Seeed provides accessible technologies with quality, speed and supply chain knowledge. When prototypes are ready to iterate, Seeed helps productize 1 to 1,000 pcs using in-house engineering, supply chain management and agile manufacture forces. Seeed also team up with incubators, Chinese tech ecosystem, investors and distribution channels to portal Maker startups beyond.
