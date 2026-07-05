#include "meshtastic_handler.h"
#include "ui.h"
#include "config.h"

// Note: This requires the Meshtastic-protobufs-arduino library
// and Nanopb to be correctly configured in PlatformIO.

void meshtastic_init() {
    // Meshtastic defaults to 115200
    Serial2.begin(115200, SERIAL_8N1, MESH_RX, MESH_TX);
    Serial.println("Meshtastic Handler Initialized");
}

void meshtastic_loop() {
    if (Serial2.available()) {
        // Read header (0x94 0xC3 + length)
        // This is a simplified version of the framing protocol
        // Real implementation should handle the ToRadio/FromRadio framing
        
        uint8_t header[2];
        if (Serial2.read() == 0x94 && Serial2.read() == 0xC3) {
            uint16_t len = (Serial2.read() << 8) | Serial2.read();
            uint8_t buffer[len];
            Serial2.readBytes(buffer, len);
            
            // Decode FromRadio packet using Nanopb
            // meshtastic_FromRadio fromRadio = meshtastic_FromRadio_init_default;
            // pb_istream_t stream = pb_istream_from_buffer(buffer, len);
            // if (pb_decode(&stream, meshtastic_FromRadio_fields, &fromRadio)) {
            //     // Process packet (NodeInfo, MeshPacket, etc.)
            //     if (fromRadio.has_node_info) {
            //         ui_add_node(fromRadio.node_info.user.long_name, ...);
            //     }
            // }
        }
    }
}

void meshtastic_send_text(const char* text, uint32_t dest) {
    // Encode ToRadio packet with MeshPacket containing text
    Serial.print("Sending message: ");
    Serial.println(text);
    
    // Serial2.write(...framed proto packet...);
}
