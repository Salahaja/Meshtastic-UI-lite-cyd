#ifndef MESHTASTIC_HANDLER_H
#define MESHTASTIC_HANDLER_H

#include <Arduino.h>
#include "mesh/mesh.pb.h" // Requires Meshtastic-protobufs-arduino
#include "pb_decode.h"
#include "pb_encode.h"

void meshtastic_init();
void meshtastic_loop();
void meshtastic_send_text(const char* text, uint32_t dest = 0xFFFFFFFF);

#endif
