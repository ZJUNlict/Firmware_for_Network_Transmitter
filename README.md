# Firmware_for_Network_Transmitter

ZJUNlict Network Transmitter's Firmware for the Robocup Soccer Small-Size League https://zjunlict.cn/

The firmwares for TX and RX [network transmitter](https://github.com/ZJUNlict/Network_Transmitter) are designed using [Keil uVision 5](http://www2.keil.com/mdk5/uvision/). 

The features are:

* UDP package communication with PC.
* Use MicroC/OS-II as real time os for STM32F407 in RX network transmitter recieves packages from nRF24L01P then send them to PC. 
* Support config package described in [communication protocol](https://github.com/ZJUNlict/Wireless_Communication_Protocol)
