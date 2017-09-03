# FilamentFuser
Arduino Shield and Sketch for a 3D Printer Filament Fuser

The shield is stacked between an Arduino UNO R3 and the Adafruit LCD Shield Kit w/ 16x2 Character Display (https://www.adafruit.com/product/772) 

## Shield Hardware

Parts List:
- Arduino Prototype Shield
- MP1584EN Step-Down Power Regulator Board
- N-MOSFET IRLZ34N
- LED 3mm, red
- Resistor 100kOhm / 1% (2*)
- Resistor 680Ohm / 1%
- Resistor 10Ohm / 1%
- Power connector, matching the 12V power supply
- Pinheader 1x2 and jumper
- Pinheader 1x2, 90°, (3*), for fan, heater and temp sensor
- Power supply, 12V, 7.5A   

## Design
Requirements:
- Control temperature [R1]
- Show set and current temperature [R2]
- Provide power to the cooling fan [R3]
- Secure operation [R4]

Features:
- Display [F1] -> [R2]
- PID controller [F2] -> [R1]
- Arduino based [F3] -> [F2]
- Input Voltage 12V DC [F4] -> [R3]
- 5V DC Voltage Regulator [F5] -> [R1], [R2], [F3]
- Auto cooldown after configured time [F6] -> [R4]
- Cooling fan is hard-wired, no software control [F7] -> [R4]
- MOSFET driver for heater [F8] -> [R1]

Software Functions:
- Show set and current temperature
- Set temperature
- Start fusing procedure (heat up)
- Stop fusing procedure after given time (cool down)
- Select from presets (Temperature and Fusing time) 
