# ESP32-DMX-To-Serial

This project reads DMX data using an ESP32 and a MAX485 module, then sends the data to a computer via the serial interface.

## Circuit Diagram

![Circuit diagram](./images/circuit.png)

## Data Format

Once a successful DMX connection is established, the DMX data is continuously sent to the serial control center. All DMX channels are output in the following format:

`*<data>,<data>,<data>,...,<data>%.`

### Example:

`*0,0,20,255,0,...,50%`

---

# new

# Serial communication

| Name            | Size                     |
| --------------- | ------------------------ |
| Start Indicator | 4 Byte                   |
| Channel 1-512   | 8 Byte each (4.096 Byte) |
| End Indicator   | 4 Byte                   |
