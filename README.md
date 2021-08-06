# ESP8266-WiFi-control-DC-motor
control dc motor clockwise/counter-clockwise through WiFi server using ESP8266/NodeMCU and 2 channel relay module

**<h1>Wiring<h1/>**
  <h2>Relay Module<h2/>
    <h1>Wire NO1 to NO2, and NC1 and NC2
    COM1 and COM2 is for the DC motor
    power supply: NC1 for GND, NO1 for 5V<h1/>
    
  <h2>NodeMCU<h2/>
    <h1>D1 and D2 for IN1 and IN2 on relay module
    If you use external power supply, don't forget to also connect the GND to power supply's<h1/>
    
Note: before you upload and run the code, change the ssid and password first
