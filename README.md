# ESP32-S3-nRF24L01-RF-Hopper
ESP32-S3 nRF24L01 RF Hopper: A high-performance, automated 2.4GHz signal generator and frequency-hopping tool built on an ESP32-S3 microcontroller and a single nRF24L01 module. It utilizes low-level radio register configurations and custom SPI routing to continuously broadcast unmodulated carrier waves across Bluetooth spectrum channels.
# ESP32-S3 & nRF24L01 Automated RF Transmitter / Hopper

> **⚠️ LEGAL DISCLAIMER:** 
> This software and hardware setup is provided strictly for **educational, academic, and research purposes** (such as studying wireless spectrum utilization, frequency hopping spread spectrum protocols, and electromagnetic interference). Transmitting radio frequency signals across unauthorized bands or deliberately disrupting communication channels (jamming) is **illegal** in most jurisdictions and violates local telecommunications laws (such as FCC, ETSI, or national regulatory bodies). The author and contributors assume **no liability** for any misuse, damage, or legal consequences arising from the use of this material. Use this code only in controlled, isolated lab environments or Faraday cages.

---

## 📌 Overview
This project transforms an **ESP32-S3** microcontroller paired with a single **nRF24L01** 2.4GHz transceiver module into an automated, high-speed frequency-hopping constant-carrier signal generator. It cycles continuously through Bluetooth frequency bands using custom SPI routing and low-level radio configuration parameters.

---

## 🛠️ Hardware Setup & Pinout Diagram

### Connections Table
| nRF24L01 Pin | ESP32-S3 GPIO Pin | Function Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Power Supply (Ensure stable 3.3V, use a filter capacitor if possible) |
| **GND** | GND | Common Ground |
| **CE** | GPIO 47 | Chip Enable (Controls TX/RX modes) |
| **CSN** | GPIO 21 | Chip Select Not (SPI Slave Select) |
| **SCK** | GPIO 18 | SPI Clock |
| **MISO** | GPIO 13 | Master In Slave Out |
| **MOSI** | GPIO 11 | Master Out Slave In |
| **IRQ** | *Left Empty* | Interrupt Request (Not used in carrier mode) |

### Visual Pin Layout
```text
      ESP32-S3                         nRF24L01 Module
+-------------------+               +-------------------+
|            GPIO 47| ------------> | CE                |
|            GPIO 21| ------------> | CSN               |
|            GPIO 18| ------------> | SCK               |
|            GPIO 13| <------------ | MISO              |
|            GPIO 11| ------------> | MOSI              |
|               3.3V| ------------> | VCC               |
|                GND| ------------> | GND               |
+-------------------+               +-------------------+
