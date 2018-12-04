# Smarthome-dashbutton

Here is something for the smart home lovers which want to control their whole lights, thermostats or any other smart devices from the sofa or with the help of an assistant like Siri.

The goal of this project is to build an electronic device which occupies following aspects:
- one control button
- as small as possible
- as fast as possible
- portable (battery powered)
- wifi ability

The result in general consists out of a small pcb, an ESP8285-M3 microcontroller which has wifi on board and a small 100mAh lipo battery. Especially because the dashbutton should be as small as possible there are only the most necessary parts onto the pcb. Therefore the ESP has to be flashed by contacting the four wire pads (Rx, Tx, 3.3v, GND) to an external FTDI adapter and a shorten jumper pad (GPIO0). Of course that is not the easiest way, but it does not have to be flashed that often and it reduces the amount of parts needed.

## Requirements

In total the parts four each dashbutton amount to a considerable sum of just 5€.

- PCB
- ESP8285-M3
- Two smd capacitors (1 microfarads with the dimensions of 1206)
- MCP1700 3.3V LDO
- 3x6mm smd button
- JST-PH 2mm 90° smd connector
- Lipo battery (with dimensions of 25x12mm)

## Schematics and PCB


<a href="images/schematics.png"><img src="images/schematics.png" width="80%" align="center"></a>

Revision 1.3 was my first final version which has some things to optimize. Maybe I will update it in the future but it is working already.
<a href="images/Dashbutton.png"><img src="images/Dashbutton.png" width="80%" align="center"></a>

Revision 2.2 consists of another outer shape of the pcb. It is round with a diameter of 30mm and includes a ground plane over two-thirds of the area. The other third is the antenna of the microcontroller and should not be overlapped with any of the traces or ground signals to reduce interferences.
<a href="images/Dashbutton_round.png"><img src="images/Dashbutton_round.png" width="80%" align="center"></a>
