
#include "./D2S_DMX.h"

const int TRANSMIT_PIN = -1;
const int ENABLE_PIN = -1;
const dmx_port_t DMX_PORT = 1;

/**
 * @brief Install the DMX driver and set the pins.
 */
void d2s_dmx_install(int receivePin)
{
    dmx_config_t config = DMX_CONFIG_DEFAULT;
    dmx_driver_install(DMX_PORT, &config, DMX_INTR_FLAGS_DEFAULT);
    dmx_set_pin(DMX_PORT, TRANSMIT_PIN, receivePin, ENABLE_PIN);
}

/**
 * @brief Receive a DMX packet.
 * @param packet Pointer to the DMX packet to receive.
 * @param wait_ticks Number of ticks to wait for the packet.
 * @return true if the packet was received successfully, false otherwise.
 */
bool d2s_dmx_receive(dmx_packet_t *packet, TickType_t wait_ticks)
{
    return dmx_receive(DMX_PORT, packet, wait_ticks);
}

/**
 * @brief Read DMX data into the destination buffer.
 * @param destination Pointer to the destination buffer.
 * @param size Size of the data to read.
 */
void d2s_dmx_read(void *destination, size_t size)
{
    dmx_read(DMX_PORT, destination, size);
}

/**
 * @brief Delete the DMX driver.
 * This function should be called when the DMX driver is no longer needed.
 * It will free the resources used by the driver.
 * @note This function should be called before the program exits or when the
 * DMX driver is no longer needed.
 */
void d2s_dmx_driver_delete()
{
    dmx_driver_delete(DMX_PORT);
}