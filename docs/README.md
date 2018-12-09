# Smarthome-dashbutton

<div>
<img src="images/both_front.jpg" width="30%" style="margin:5px">
<img src="images/both_back.jpg" width="30%" style="margin:5px">
</div>


Here is something for the smart home lovers which want to control their whole lights, thermostats or any other smart devices from the sofa without the need of actuating the wall switch.

The goal of this project is to build an electronic device which occupies following aspects:
- one control button
- as small as possible
- as fast as possible
- portable (battery powered)
- wifi ability

The result in general consists out of a small PCB, an ESP8285-M3 microcontroller which has wifi on board and a small 100mAh LiPo battery. Especially because the dashbutton should be as small as possible there are only the most necessary parts onto the PCB. Therefore the ESP has to be flashed by contacting the four wire pads (Rx, Tx, 3.3v, GND) to an external FTDI adapter and a shorten jumper pad (GPIO0). Of course that is not the easiest way, but it does not have to be flashed that often and it reduces the amount of parts needed.

## Requirements

In total the parts for each dashbutton amount to a considerable sum of just 5€.

- PCB
- ESP8285-M3
- Two SMD capacitors (1 microfarads with the dimensions of 1206)
- MCP1700 3.3V LDO
- 3x6mm SMD button
- JST-PH 2mm 90° SMD connector
- Lipo battery (with dimensions of 25x12mm)

## How the code works

It is up to you where you want to use the smart home dashbutton for. In my case it is integrated to Apples HomeKit, but it should be easy to shift it to another framework, because the current code is based on a separated bridge which communicates over the MQTT protocol.


After rebooting the ESP8285 it simply connects to the specified wifi network as well as to the MQTT broker (which is in my case the bridge). When the connection could be established the dashbutton sends a single '1' to the MQTT broker before it will go back to deepsleep. When the connection could not be established within five seconds, it will fall back into deepsleep as well but without publishing anything. This is just for the case if the network is unreachable and the dashbutton tries to connect until the battery is empty. The button itself does the magic by only resetting the ESP8285.


## Schematics and PCB


<center><img src="images/schematics.png" width="80%"></center>

Revision 1.3 was my first final version which has some things to optimize. Maybe I will update it in the future but it is working already.

<center><img src="images/Dashbutton.png" width="80%"></center>

Revision 2.2 consists of another outer shape of the PCB. It is round with a diameter of 30mm and includes a ground plane over two-thirds of the area. The other third is the antenna of the microcontroller and should not be overlapped with any of the traces or ground signals to reduce interferences.

<center><img src="images/Dashbutton_round.png" width="80%"></center>
