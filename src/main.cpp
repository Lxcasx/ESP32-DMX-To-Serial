/*
  ESP32 DMX to Serial (D2S)

  This projects reads DMX data with an MAX485 module
  and sends it to the Serial Monitor in order to proccess it with a computer.
  The data is sent in the following format:
  DMX-SERIAL<data>

  Code is based on: https://github.com/someweisguy/esp_dmx
*/

#include <Arduino.h>
#include <D2S_DMX.h>
#include <DS2_UART.h>

int receivePin = 15;

byte data[DMX_PACKET_SIZE];

bool dmxIsConnected = false;
unsigned long lastUpdate = millis();

byte startBytes[10] = {'D', 'M', 'X', '-', 'S', 'E', 'R', 'I', 'A', 'L'};

void sendStartBytes();

// ToDo: Maybe use booth cores: One for DMX Reading, one for Serial Writing

void setup()
{
  d2s_uart_init(230400);
  // Serial.begin(230400);
  
  d2s_dmx_install(receivePin);
}

void loop()
{
  dmx_packet_t packet;

  /* The DMX standard defines the amount of time until DMX
    officially times out. That amount of time is converted into ESP32 clock
    ticks using the constant `DMX_TIMEOUT_TICK`. If it takes longer than that
    amount of time to receive data, this if statement will evaluate to false. */
  if (d2s_dmx_receive(&packet, DMX_TIMEOUT_TICK))
  {
    unsigned long now = millis();

    // make sure we have a valid packet
    if (!packet.err)
    {
      if (!dmxIsConnected)
      {
        d2s_uart_write("DMX is connected!");
        dmxIsConnected = true;
      }

      // read dmx data into the data buffer
      d2s_dmx_read(data, packet.size);

      if (now - lastUpdate > 50)
      {
        sendStartBytes();

        for (int i = 1; i < 512; i++)
        {
          d2s_uart_write((char *)&data[i]);
        }

        lastUpdate = now;
      }
    }
    else
    {
      /* this can happen when you first
        connect or disconnect your DMX devices. If you are consistently getting
        DMX errors, then something may have gone wrong with your code or
        something is seriously wrong with your DMX transmitter. */
      d2s_uart_write("DMX error occurred.");
    }
  }
  else if (dmxIsConnected)
  {
    d2s_uart_write("DMX was disconnected.");
    d2s_dmx_driver_delete();

    /* Stop the program. */
    while (true)
      yield();
  }
}

void sendStartBytes()
{
  Serial.write(startBytes, sizeof(startBytes));
}