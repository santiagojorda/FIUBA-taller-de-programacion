#include "server_protocol.h"

#include <cstdint>
#include <iostream>
#include <string>

#include <arpa/inet.h>

#include "common_shop_item.h"

#define TEXT_NOT_EQUIPPED "Not Equipped"
#define END_OF_MESSAGE 0x00
#define SOCKET_CLOSED -1

ServerProtocol::ServerProtocol(const char* servname): skt(servname), peer(skt.accept()) {}

void ServerProtocol::send_message(const std::string& message) {
    bool was_closed = false;
    uint16_t size_serial = htons(message.length());

    // solo deberia hacer htons en todo lo que no sea cadena de bytes
    int sent_bytes = peer.sendall(&size_serial, sizeof(size_serial), &was_closed);
    if (sent_bytes < 0) {
        // codigo de error
        return;
    }

    // un string es una cadena de bytes
    sent_bytes = peer.sendall(message.c_str(), message.length(), &was_closed);
    if (sent_bytes < 0) {
        return;
        // codigo de error
    }
}

void ServerProtocol::send_byte_message(uint8_t data) {
    bool was_closed = false;

    int sent_byte = peer.sendall(&data, sizeof(data), &was_closed);
    if (sent_byte < 0) {
        return;
        // codigo de error
    }
}

void ServerProtocol::receive_message(std::string& message, bool& was_closed) {
    message.clear();
    uint8_t byte_read;
    while (not was_closed) {
        // chequear si no es <0 bytes recibidos
        peer.recvall(&byte_read, sizeof(byte_read), &was_closed);
        if (was_closed || byte_read == END_OF_MESSAGE) {
            break;
        }
        message.push_back(char(byte_read));
    }
}
