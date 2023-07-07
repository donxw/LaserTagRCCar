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
* 350 mAH Lipo battery
* Slide switch (https://www.aliexpress.us/item/2251832535125782.html?spm=a2g0o.productlist.main.13.442b586dJ7hWyj&algo_pvid=bee75389-0b26-42fb-8bb7-ce1bfa27d7a0&algo_exp_id=bee75389-0b26-42fb-8bb7-ce1bfa27d7a0-6&pdp_npi=3%40dis%21USD%211.45%211.45%21%21%211.45%21%21%40211bea0816886811639263773d07c5%2161208924650%21sea%21US%21950932793&curPageLogUid=bkxjtxJb6tvA)

## Assembly
### Car
#### Assemble Chassis
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/79f4feb3-6f31-416d-b56f-fd053e646fe4)
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/af7678ca-64b6-4249-8c18-de202f3bc0e8)
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/2fb21c9e-f60c-4e4b-92f6-062df35f97b7)

#### Assemble Body
![image](https://github.com/donxw/LaserTagRCCar/assets/31633408/3b821f34-f054-46cb-b885-a030488168ec)

#### Car Wiring
![Schematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/0395bd82-0c10-4ed3-b41e-0046131874ad)
![NeopixelLEDPinOut](https://github.com/donxw/LaserTagRCCar/assets/31633408/8b121850-3834-4be7-a6ce-24b9217479a4)
![CarWiring](https://github.com/donxw/LaserTagRCCar/assets/31633408/39968a68-8d50-41bf-b99f-6f536df59da6)


### Remote Control

#### Assemble Remote Control
![AssembleRemote](https://github.com/donxw/LaserTagRCCar/assets/31633408/7b3fcec2-8144-4f4d-8e18-9568a467a4a9)

#### Remote Control Wiring
![RemoteControlSchematic](https://github.com/donxw/LaserTagRCCar/assets/31633408/3a873c28-8bed-442e-b47b-2344d01ab724)
![16_WireRCParts](https://github.com/donxw/LaserTagRCCar/assets/31633408/58ca24b4-1c06-4ce2-84c9-5fed1ec5fefe)

Slide Switch 
![SlideSwitch-AliExpress](https://github.com/donxw/LaserTagRCCar/assets/31633408/a27ece8d-472b-4e03-a1c9-76e23f43cc1a)





