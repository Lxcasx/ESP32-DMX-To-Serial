/*
  ESP32 DMX to Serial

  This projects reads DMX data with an MAX485 module
  and sends it to the Serial Monitor in order to proccess it with a computer.
  The data is sent in the following format:
  *<data>,<data>,<data>,...,<data>%

  Code is based on: https://github.com/someweisguy/esp_dmx
*/

#include <Arduino.h>
#include <esp_dmx.h>

// define hardware pins
int transmitPin = -1;
int receivePin = 3;
int enablePin = -1;

dmx_port_t dmxPort = 1;
byte data[DMX_PACKET_SIZE];

bool dmxIsConnected = false;
unsigned long lastUpdate = millis();

void setup()
{
  Serial.begin(230400);

  dmx_config_t config = DMX_CONFIG_DEFAULT;
  dmx_driver_install(dmxPort, &config, DMX_INTR_FLAGS_DEFAULT);

  dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);
}

void loop()
{
  dmx_packet_t packet;

  /* The DMX standard defines the amount of time until DMX
    officially times out. That amount of time is converted into ESP32 clock
    ticks using the constant `DMX_TIMEOUT_TICK`. If it takes longer than that
    amount of time to receive data, this if statement will evaluate to false. */
  if (dmx_receive(dmxPort, &packet, DMX_TIMEOUT_TICK))
  {
    unsigned long now = millis();

    // make sure we have a valid packet
    if (!packet.err)
    {
      if (!dmxIsConnected)
      {
        Serial.println("DMX is connected!");
        dmxIsConnected = true;
      }

      // read dmx data into the data buffer
      dmx_read(dmxPort, data, packet.size);

      if (now - lastUpdate > 50)
      {
        Serial.print('*');
        for (int i = 1; i < 512; i++)
        {
          if (i == 511)
          {
            Serial.printf("%d", data[i]);
          }
          else
          {
            Serial.printf("%d,", data[i]);
          }
        }

        Serial.print("%");

        lastUpdate = now;
      }
    }
    else
    {
      /* this can happen when you first
        connect or disconnect your DMX devices. If you are consistently getting
        DMX errors, then something may have gone wrong with your code or
        something is seriously wrong with your DMX transmitter. */
      Serial.println("A DMX error occurred.");
    }
  }
  else if (dmxIsConnected)
  {
    Serial.println("DMX was disconnected.");
    dmx_driver_delete(dmxPort);

    /* Stop the program. */
    while (true)
      yield();
  }
}