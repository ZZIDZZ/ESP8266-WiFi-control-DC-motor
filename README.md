# ESP8266-WiFi-control-DC-motor
control dc motor clockwise/counter-clockwise through WiFi web-server using ESP8266/NodeMCU and 2 channel relay module

**<h1>Wiring<h1/>**\n
  <h2>Relay Module<h2/>\n
    <h3>Wire NO1 to NO2, and NC1 and NC2\n
    COM1 and COM2 is for the DC motor\n
    power supply: NC1 for GND, NO1 for 5V<h3/>\n
    
  <h2>NodeMCU<h2/>\n
    <h3>D1 and D2 for IN1 and IN2 on relay module\n
    If you use external power supply, don't forget to also connect the GND to power supply's<h3/>\n
    
Note: before you upload and run the code, change the ssid and password first\n
Use the websocket for lower latency, and update to all client
