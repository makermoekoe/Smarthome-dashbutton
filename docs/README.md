# Smarthome-dashbutton

Here is something for the smart home lovers which want to control their whole lights, thermostats or any other smart devices from the sofa without the need of actuating the wall switch.

The goal of this project is to build an electronic device which occupies following aspects:
- one control button
- as small as possible
- as fast as possible
- portable (battery powered)
- wifi ability

The result in general consists out of a small PCB, an ESP8285-M3 microcontroller which has wifi on board and a small 100mAh LiPo battery. Especially because the dashbutton should be as small as possible there are only the most necessary parts onto the PCB.

<div>
<img src="images/both_front.jpg" height="200px" style="margin:5px">
<img src="images/both_back.jpg" height="200px" style="margin:5px">
</div>


Here is a video to see the first version of the dashbutton in action. (Click on the image)

<a href="https://www.instagram.com/p/Bqrb7guHYCT/?utm_source=ig_web_button_share_sheet"><img src="images/video.png" width="200px"></a>


## Requirements

In total the parts for each dashbutton amount to a considerable sum of just 5€. If you click on the component you will be forwarded to an example product on aliexpress.

- PCB (... following, but the eagle files are accessible in this GitHub repository)
- [ESP8285-M3](https://de.aliexpress.com/item/ESP8285-ESP-M3-Serial-Port-Transparent-Drahtlose-WiFi-Steuer-Modul-Kompatibel-mit-ESP8266/32906969552.html?spm=a2g0x.search0104.3.8.5dd24d46hq1LnX&ws_ab_test=searchweb0_0%2Csearchweb201602_5_10065_10068_319_317_10548_10696_453_10084_454_10083_10618_10307_10820_10821_538_10303_537_10302_536_10059_10884_10887_100031_10319_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=9139143b-1052-497f-be3f-c89ec20699f7&algo_expid=9139143b-1052-497f-be3f-c89ec20699f7-1)
- [Two SMD capacitors (1 microfarads with the dimensions of 1206)](https://de.aliexpress.com/item/100-st-cke-10PF-47UF-1206-SMD-500-v-X7R-Fehler-10-10-uf-106-karat/32880416347.html?spm=a2g0x.search0104.3.1.5daa50edPwDDts&ws_ab_test=searchweb0_0%2Csearchweb201602_5_10065_10068_319_317_10548_10696_453_10084_454_10083_10618_10307_10820_10821_538_10303_537_10302_536_10059_10884_10887_100031_10319_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=de978347-54bc-48d4-8777-ec8e9227c7c1&algo_expid=de978347-54bc-48d4-8777-ec8e9227c7c1-0)
- [MCP1700 3.3V LDO](https://de.aliexpress.com/item/20-ST-CKE-MCP1700T-3302E-TT-MCP1700-LDO-3-3-V-0-25A-SOT23-3/32683211391.html?spm=a2g0x.search0104.3.8.671a1508KFSKpi&ws_ab_test=searchweb0_0%2Csearchweb201602_5_10065_10068_319_317_10548_10696_453_10084_454_10083_10618_10307_10820_10821_538_10303_537_10302_536_10059_10884_10887_100031_10319_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=6d769164-1ec4-4199-af59-74da9f097174&algo_expid=6d769164-1ec4-4199-af59-74da9f097174-1)
- [3x6mm SMD button](https://de.aliexpress.com/item/10-teile-los-Micro-mini-Schalter-Momentary-Zwei-Pin-Push-Button-Switch-10-teile-los-SMD/32888197120.html?spm=a2g0x.search0104.3.59.52ba1778oRTAR2&ws_ab_test=searchweb0_0%2Csearchweb201602_5_10065_10068_319_317_10548_10696_453_10084_454_10083_10618_10307_10820_10821_538_10303_537_10302_536_10059_10884_10887_100031_10319_321_322_10103%2Csearchweb201603_51%2CppcSwitch_0&algo_pvid=ea31593b-9072-4493-b513-6a35a021b6b3&algo_expid=ea31593b-9072-4493-b513-6a35a021b6b3-8)
- JST-PH 2mm 90° SMD connector
- Lipo battery (with dimensions of 25x12mm)

## How the code works

It is up to you where you want to use the smart home dashbutton for. In my case it is integrated to Apples HomeKit, but it should be easy to shift it to another framework, because the current code is based on a separated bridge which communicates over the MQTT protocol.


After rebooting the ESP8285 will connect to the specified wifi network as well as to the MQTT broker (which is in my case the bridge). When the connection could be established the dashbutton sends a single '0' to the MQTT broker before it will go back to deepsleep mode. When the connection could not be established within five seconds, it will fall back into deepsleep mode as well but without publishing anything. This is just for the case if the network is unreachable and the dashbutton tries to connect until the battery is empty. The button itself does the magic by simply resetting the ESP8285.
The string which will be send by the dashbutton when the button is pressed depends on your used home automation service. In my case I am using the 'programmable switch event' service in HomeKit (HAP-NodeJS) which operates with three states (0, 1, 2). Depending on that state HomeKit is able to act differently. A 0 will be interpreted as a single button press, a 1 will be interpreted as a double button press and a 2 will be interpreted as a long button press. Of course, this functionality is not usable with this kind of dashbutton cause it actually can only detect a single button press (as a microcontroller reset).


## FLashing the dashbutton

The ESP has to be flashed by contacting the four wire pads (Rx, Tx, 3.3v, GND) to an external FTDI adapter. This could be done without soldering some wires to the pads. Just take a 4-pin pinheader and hold it against the four wire pads while flashing. Before this can be done, it is necessary to put the ESP8285 to flash mode by shorten the GPIO0 solder jumper pad between the two capacitors. As soon as the reset button will be pressed the microcontroller will enter flash mode and never run the sketch which has been flashed on before.

Open the code with Arduino IDE, add your wifi credentials, select the 'Generic ESP8285' board in the board manager as well as the correct port of your ESP and hit upload. When it is ready with compiling and the 'upload' massage appears the reset button has to be pressed once. After this there should appear some red dots which show the current upload state.


## Schematics and PCB


<center><img src="images/schematics.png" width="80%"></center>

Revision 1.3 was my first final version which has some things to optimize. Maybe I will update it in the future but it is working already.

<center><img src="images/Dashbutton.png" width="80%"></center>

Revision 2.2 consists of another outer shape of the PCB. It is round with a diameter of 30mm and includes a ground plane over two-thirds of the area. The other third is the antenna of the microcontroller and should not be overlapped with any of the traces or ground signals to reduce interferences.

<center><img src="images/Dashbutton_round.png" width="80%"></center>
