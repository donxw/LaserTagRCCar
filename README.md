# LaserTagRCCar
ESP Now based RC Car and controller with Laser and Photodetector to play Tag

![CoverShot](https://github.com/donxw/LaserTagRCCar/assets/31633408/ed9588b4-275d-4282-90f4-00b7788a9374)

Remote control car and joystick wireless controller with a display showing life left.  Each car has an LED (replaced the laser for child safety) and a photoresistor to sense a "hit".  The RC Car and controller communicate wirelessly using the ESP-NOW communication link.
## Bill of Materials
### Car
* 3D printed parts
* NodeMCU ESP8266 30pin Dev board
* ESP12E Motor Shield HW-588A.  Do not purchase an ESP8266 Motor Shield if it is not marked as HW-588A.
* 2x 6V, 500 RPM N20 Gearmotor.  Faster motors will work as well, but are more difficult to control (especially at low speeds)
* 9V USB rechargable LiPo battery
* 1x Neopixel LED (5mm, 3.3V)
* 1x Clear LED
* 1x Photoresistor (5506)
* 1x 20K Resistor
* 2x 75mm x 3mm O-ring (McMaster-Carr)
* Screws:
  * 1x M2x5
  * 5x M2x6
  * 2x M2x8
  * 3x M2.6x6
  * 2x M3x6
  * 2x M3x16
### Remote Control
* 3D printed parts
* TTGO T-Display ESP32 Board
* Joystick (https://www.mouser.com/ProductDetail/611-THB001P)
* 380 mAH Lipo battery
* Slide switch (https://www.aliexpress.us/item/2251832535125782.html?spm=a2g0o.productlist.main.13.442b586dJ7hWyj&algo_pvid=bee75389-0b26-42fb-8bb7-ce1bfa27d7a0&algo_exp_id=bee75389-0b26-42fb-8bb7-ce1bfa27d7a0-6&pdp_npi=3%40dis%21USD%211.45%211.45%21%21%211.45%21%21%40211bea0816886811639263773d07c5%2161208924650%21sea%21US%21950932793&curPageLogUid=bkxjtxJb6tvA)

## Assembly
### Assemble Chassis
![AssembleChassis_1](https://github.com/donxw/LaserTagRCCar/assets/31633408/e0393fd0-7d51-4b9b-9516-7a31397fddef)
![AssembleChassis_2](https://github.com/donxw/LaserTagRCCar/assets/31633408/38259e16-cbf0-4805-a58b-43195cd261bb)
![AssembleChassis_3](https://github.com/donxw/LaserTagRCCar/assets/31633408/7ec46d23-d3d4-49d3-b172-5147fc86064f)

### Assemble Body
![AssembleBody](https://github.com/donxw/LaserTagRCCar/assets/31633408/5f529553-c608-4f4e-a3b3-4f63f9abf97b)

### Car Wiring
![Schematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/2f2e11e1-d49d-4177-afff-c6210cf459d3)
![NeopixelLEDPinOut](https://github.com/donxw/LaserTagRCCar/assets/31633408/f2195e55-ada4-4983-a5e6-01906b28ae06)
![CarWiring](https://github.com/donxw/LaserTagRCCar/assets/31633408/6c48de2f-ebf4-47c2-979c-226c309b613a)

### Remote Control Wiring
![RemoteControlSchematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/8253718d-3fb9-40db-ae82-d5cde67e85e1)
![16_WireRCParts](https://github.com/donxw/LaserTagRCCar/assets/31633408/fc51fd4f-9b69-40e8-838b-3405f47cccdc)

Slide Switch 
![SlideSwitch-AliExpress](https://github.com/donxw/LaserTagRCCar/assets/31633408/85c09965-0365-4f19-a41a-b2f01f3f8d6e)

### Car Code
Before flasing the code to the car, the MAC of the ESP32 dev board in the Remote Control unit needs to be obtained and put into the ESP8266 arduino code for the car.  This can be done by uploading the code to the remote control unit ESP32 and watching the Serial Port for the MAC.  Copy this, and put the ESP32 address into the code for the ESP8266 of the car.  Now flash the car code and watch the Serial Port for the ESP8266 MAC.  Copy this and put it into the remote control unit ESP32 code, then re-flash the ESP32.

The car code is titled: "NodeMCUMotorShield_RCCar_Receiver_Laser_BiDir_Photosensor.ino".  Use board NodeMCU 1.0.

The remote control code is titled:  "Joystick_send_TTGO_BiDirectional.ino"  Use board ESP32 Dev Module.  This code uses the TFT_eSPI library for the TFT so update the User_Setup_Select.h file to uncomment this setup line only: #include <User_Setups/Setup25_TTGO_T_Display.h>.

Test to be sure the remote control and car communicate to each other before final assembly.

### Complete Car Assembly
After flashing the code to the car, place the body onto the chassis taking care to tuck wiring in without getting under the on-off push button.  Flip the car over to insert fasteners and the 9V usb rechargable battery.
![AttachBodyandBattery](https://github.com/donxw/LaserTagRCCar/assets/31633408/1476a580-3f6f-4ea2-8026-dc15489eff86)

To assemble the front wheels, locate the smaller set of wheels and 2x M2 x 16 screws.  Take the screw and push them through the wheel holes to clean out the thin layer of support material left from printing.  Pushing the screw in from the reverse direction works fine.  Or use a 3mm drill bit and clean out the hole with a hand drill.  Once cleaned put a small drop of oil on the screw and push it in the correct direction - see image 3.
![PrepIdleWheels](https://github.com/donxw/LaserTagRCCar/assets/31633408/be86b1f6-f8ad-4977-a77f-280669177355)

Attach the front wheels, taking care to be sure the wheels are aligned correctly.  Attache the rear wheels to the motor by aligning the flat side of the motor shaft to the flat part of the hole in the wheel.  Stretch the 75mm x 3mm o-ring over the wheels into the v-groove.  Snap on the hood scoop.
![Wheels_Oring_Scoop](https://github.com/donxw/LaserTagRCCar/assets/31633408/f8ff86e1-3f1d-46d7-90f6-55d6aa9b19bb)

#### Assemble Remote Control
![AssembleRemote](https://github.com/donxw/LaserTagRCCar/assets/31633408/a21349a7-2f35-4e37-8d58-2281b9cc9007)

### Final car and remote control appearance 
![Complete](https://github.com/donxw/LaserTagRCCar/assets/31633408/341ffcf6-d59d-459a-a089-c7980ab5dd3f)









