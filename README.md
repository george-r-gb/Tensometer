# Tensometer

This project uses Arduino IDE 2.1.0

Programme to read the load in a uniaxial tensile testing machine

Load measurements are displayed in plain text in the serial monitor for export and analysis
'start' 'end' and 'reset' commands are used to start and stop recording and to reset the programme to zero
After recording is stopped, the maximum load from that session is displayed
Adjust the calibration factor to change the relationship between input and output

## Equipment used
1. Arduino Uno R3
2. HX711 Load Cell Amplifier
3. Strain gauge attached to spring beam from a 'Hounsfield' Tensometer
