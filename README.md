# Shotty V2.0 (in progress)

# Shotty V1.0 (not working properly)
Shotty is an open-source shot dispencer


Un servomotor atasat de un brat mobil al unei jucarii care se duce deasupra unui pahar si toarna o cantitate de lichid avand 4 moduri de lucru (manual, aleatoriu, automat si curatate) si un mod de dimensionare a cantitatii de lichid

A servo motor is affixed to a mobile arm of a toy, adept at maneuvering above a glass and dispensing liquid with precision. It offers four distinct operating modes: manual, random, automatic and cleaning. Additionally, it includes a liquid quantity sizing mode for precise measurement adjustments.

<img src="https://raw.githubusercontent.com/eneadriancatalin/Shotty-dispenser/main/media/presentation/intro.png" width="720" />


<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/working_modes.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/working_modes_2.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/manufacturing_process.png?raw=truee" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/tinkercadv1.1.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/tinkercad_v1.png?raw=true" width="720" />

In the initial version on Tinkercad, I had a functional model. The only issue encountered was the limitation on the number of consumers for the Arduino:

- A maximum of 16 LEDs lit simultaneously
- Utilization of the LCD
- Servomotor control
- Integration of two 74hc595 Shift Register ICs
 

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/tinkercadv1.2.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/tinkercad_v2.png?raw=true" width="720" />

Changes made in the second version:

- Improved the arrangement of the breadboards slightly.
- Added a 10µF capacitor to the main button.
- Transitioned the red LEDs to the 9V battery.
- Implemented transistors for the red LEDs to control them with the voltage from the Arduino (that's coming thow the microswitch).

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/tinkercadv1.3.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/tinkercad_v3.png?raw=true" width="720" />

In the third version, I condensed the breadboards to transition to real-life prototyping.

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/3d_model.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/3d_spin.gif?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/timeline.gif?raw=true" width="720" />

[Fusion360 3D file](https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/fusion360_model.f3z)

In the above model, the following features are included:

- A simplified model of the crane (for calculation purposes only).
- Calculation of the glass holes to ensure the crane arm aligns precisely above them.
- Placement of the LCD, main button, and potentiometer for liquid volume adjustment.
- The Arduino, relay, and 9V battery.

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/drawing_top.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/top_view_printed.jpg?raw=true?raw=true" width="720" />

The Fusion 360 version of the design fit within an A2 page. I decided to divide the A2 page into 6 A4 pages for easier printing, and then glue them together to obtain the final model.

[The A2 PDF file can be found here](https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/drawings/top_view_A2.pdf)


<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/drawing_side.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/side_view_printed.jpg?raw=true" width="720" />

Pentru partea laterala am reusit sa o incadrez pe o foaie A4 (sau cel putin doar partea care imi trebuia mie)

[The A4 images file can be found here](https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/drawings/side_view_A4.pdf)

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/other_ideas.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/issues.png?raw=true" width="720" />

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/component_list.png?raw=true" width="720" />

- [green 16x02 I2C LCD](https://www.handsontec.com/dataspecs/module/I2C_1602_LCD.pdf)
- 8 resistors of 320Ω and 8 of 100Ω (connected in series to create a resistance of 420Ω for the red LEDs connected to 9V)
- 9 resistors of 220Ω (8 for each green LED, and 1 for the yellow LEDs, as only one is lit simultaneously)
- 8 [microswitches](https://www.farnell.com/datasheets/2340369.pdf) with one pin connected to Arduino's 5V and the NC pin linked to the transistor's base
- 8 transistors [BC337](https://www.farnell.com/datasheets/1789499.pdf) with voltage from microswitches at the base, and through the emitter and collector, 9V from the battery is supplied to the red LEDs
- wires coming from a CAT6 cable
- 8 red, yellow, and green LEDs
- Relay for pump control using Arduino <img src="https://components101.com/sites/default/files/component_pin/Single-Channel-Relay-Module-Pinout.jpg" width="300" />
- microswitches
- 2 IC Shift Registers [74HC595](https://www.diodes.com/assets/Datasheets/74HC595.pdf) or controlling yellow and green LEDs
- [12V water pump](https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/38/50200_Web.pdf) powered by a 9V battery <img src="https://i5.walmartimages.com/asr/76152e98-d946-4c7d-8047-65814b2c4661.a307ae81f101bfe51a1dacd3f6b567c4.jpeg?odnHeight=612&odnWidth=612&odnBg=FFFFFF" width="200" />
- [9G servomotor](http://www.ee.ic.ac.uk/pcheung/teaching/de1_ee/stores/sg90_datasheet.pdf)
- Transparent plexiglass: one plate of 30cm x 45cm, 2 plates of 45cm x 7.5cm, and 2 plates of 30cm x 7.5cm


<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/whatsnext.png?raw=true" width="720" />

- utilizing a more powerful servomotor
- opting for a different type of hose, as the current one is too rigid and does not rotate smoothly with the arm
- revising soldering to prevent short circuits
- choosing another type of toy; the current one had the arm's rotation point at the back, resulting in Shotty being excessively large
- <img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/components/future_combine.png?raw=true" width="300" />
- Completely redesigning the 3D model to fit the characteristics of the new toy
- Adding a power port for mains power supply, a button for selecting between mains power and battery power, and a female USB port for easier Arduino code updates


<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/presentation/media.png?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/breadboard.jpg?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/break_truck.jpg?raw=true" width="720" />

(sorry for bad quality)

<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/hole_plexiglass.jpg?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/soldering.jpg?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/soldering_2.jpg?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/soldering_3.jpg?raw=true"width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/project_1.jpg?raw=true" width="720" />
<img src="https://github.com/eneadriancatalin/Shotty-dispenser/blob/main/media/project_2.jpg?raw=true" width="720" />
