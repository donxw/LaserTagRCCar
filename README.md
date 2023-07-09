# LaserTagRCCar
ESP Now based RC Car and controller with Laser and Photodetector to play Tag

![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/12c061cf-f554-4d35-9a31-0183c41dfc35)

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
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/79f4feb3-6f31-416d-b56f-fd053e646fe4)
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/af7678ca-64b6-4249-8c18-de202f3bc0e8)
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/2fb21c9e-f60c-4e4b-92f6-062df35f97b7)

### Assemble Body
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/3b821f34-f054-46cb-b885-a030488168ec)

### Car Wiring
![Schematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/0395bd82-0c10-4ed3-b41e-0046131874ad)
![NeopixelLEDPinOut](https://github.com/donxw/LaserTagRCCar/assets/31633408/8b121850-3834-4be7-a6ce-24b9217479a4)
![CarWiring](https://github.com/donxw/LaserTagRCCar/assets/31633408/39968a68-8d50-41bf-b99f-6f536df59da6)

### Remote Control Wiring
![RemoteControlSchematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/3a873c28-8bed-442e-b47b-2344d01ab724)
![16_WireRCParts](https://github.com/donxw/LaserTagRCCar/assets/31633408/58ca24b4-1c06-4ce2-84c9-5fed1ec5fefe)

Slide Switch 
![SlideSwitch-AliExpress](https://github.com/donxw/LaserTagRCCar/assets/31633408/a27ece8d-472b-4e03-a1c9-76e23f43cc1a)

### Car Code
Before flasing the code to the car, the MAC of the ESP32 dev board in the Remote Control unit needs to be obtained and put into the ESP8266 arduino code for the car.  This can be done by uploading the code to the remote control unit ESP32 and watching the Serial Port for the MAC.  Copy this, and put the ESP32 address into the code for the ESP8266 of the car.  Now flash the car code and watch the Serial Port for the ESP8266 MAC.  Copy this and put it into the remote control unit ESP32 code, then re-flash the ESP32.

The car code is titled: "NodeMCUMotorShield_RCCar_Receiver_Laser_BiDir_Photosensor.ino".  Use board NodeMCU 1.0.
The remote control code is titled:  "Joystick_send_TTGO_BiDirectional.ino"  Use board NodeMCU 1.0.  Also, this code uses the TFT_eSPI library for the TFT so update the User_Setup_Select.h file to uncomment this setup line only: #include <User_Setups/Setup25_TTGO_T_Display.h>.

Test to be sure the remote control and car communicate to each other before final assembly.

### Complete Car Assembly
After flashing the code to the car, place the body onto the chassis taking care to tuck wiring in without getting under the on-off push button.  Flip the car over to insert fasteners and the 9V usb rechargable battery.
![AttachBodyandBattery](https://github.com/donxw/LaserTagRCCar/assets/31633408/1a7b01af-68c7-44bc-afa8-15e465527516)

To assemble the front wheels, locate the smaller set of wheels and 2x M2 x 16 screws.  Take the screw and push them through the wheel holes to clean out the thin layer of support material left from printing.  Pushing the screw in from the reverse direction works fine.  Or use a 3mm drill bit and clean out the hole with a hand drill.  Once cleaned put a small drop of oil on the screw and push it in the correct direction - see image 3.
![PrepIdleWheels](https://github.com/donxw/LaserTagRCCar/assets/31633408/3c83edad-6604-4e06-8e0a-6bcffcc50f69)

Attach the front wheels, taking care to be sure the wheels are aligned correctly.  Attache the rear wheels to the motor by aligning the flat side of the motor shaft to the flat part of the hole in the wheel.  Stretch the 75mm x 3mm o-ring over the wheels into the v-groove.  Snap on the hood scoop.
![Wheels_Oring_Scoop](https://github.com/donxw/LaserTagRCCar/assets/31633408/072ac189-15bc-4ba7-a984-be9f007a32af)

#### Assemble Remote Control
![AssembleRemote](https://github.com/donxw/LaserTagRCCar/assets/31633408/7b3fcec2-8144-4f4d-8e18-9568a467a4a9)

### Final car and remote control appearance 
![Complete](https://github.com/donxw/LaserTagRCCar/assets/31633408/5f7dac71-c703-43bb-8ee0-f414c3d0c237)








