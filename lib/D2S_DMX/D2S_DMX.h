#include <Arduino.h>
#include <esp_dmx.h>

#ifndef DMX_H
#define DMX_H

void d2s_dmx_install(int receivePin);
bool d2s_dmx_receive(dmx_packet_t *packet, TickType_t wait_ticks);
void d2s_dmx_read(void *destination, size_t size);
void d2s_dmx_driver_delete();

#endif // DMX_H
