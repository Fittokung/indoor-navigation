# **Indoor Navigation using Ultra-Wideband**

A navigation app for large buildings, such as universities, enabling fast and accurate room or service point location using Ultra-Wideband (UWB) technology.

## **Key Features**
- Real-time navigation with live location tracking on a map
- Distance calculation
- Authentication system allowing room owners to grant access with user confirmation

## **Technology Stack**
- ESP32 + DW1000 modules implement from Makerfabs ESP32 UWB
- Wi-Fi WebSocket & BLE GATT
- Android Studio

## **Testing Phase**
- Initial test site: 5th floor, 30th Anniversary Building, Faculty of Engineering
- Limited testing in 3 rooms before expanding further

## **UWB Distance Calculation**
The system calculates the distance between devices using the Time of Flight (ToF) method. The Ultra-Wideband (UWB) signal travels from the transmitter to the receiver, and the time taken is used to compute the distance with the following equation:
d = c⋅t / 2
Where:
- d = Distance between devices (meters)
- c = Speed of light (3.0 × 10⁸ m/s)
- t = Time taken for the signal to travel (seconds)

​Since the signal travels to the receiver and back, the time is divided by 2 to get the one-way distance. This method ensures high accuracy in positioning within the system.

## **First draft System Architecture Diagram**
![](picture/System%20Architecture%20Diagram.jpg)