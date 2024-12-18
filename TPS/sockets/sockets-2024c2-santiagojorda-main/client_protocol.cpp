#include "client_protocol.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

#define LENGTH_MESSAGE 512
#define ERROR -1

ClientProtocol::ClientProtocol(char* hostname, char* servname): skt(hostname, servname) {}

void ClientProtocol::receive_message(std::string& message, bool& was_closed) {
    message.clear();
    // obtengo el tamaño del string
    uint16_t size_serial;
    int bytes_readed = skt.recvall(&size_serial, sizeof(size_serial), &was_closed);
    if (was_closed) {
        return;
    }
    if (bytes_readed < 0) {
        printf("Hubo un error al recibir el tamaño mensaje\n");
        return;
    }
    uint16_t size = ntohs(size_serial);

    // obtengo el string
    std::vector<char> buff(size);
    bytes_readed = skt.recvall(buff.data(), size, &was_closed);
    if (was_closed) {
        return;
    }
    if (bytes_readed < 0) {
        printf("Hubo un error al recibir el tamaño mensaje\n");
        return;
    }
    message = std::string(buff.data(), buff.size());
}

int ClientProtocol::receive_byte_message() {
    bool was_closed = false;
    uint8_t data;
    int bytes_readed = skt.recvall(&data, sizeof(data), &was_closed);
    if (bytes_readed < 0) {
        was_closed = true;
        printf("Hubo un error al recibir el tamaño mensaje\n");
        return -1;
    }
    return static_cast<int>(data);
}

void ClientProtocol::send_message(std::string& message) {
    bool was_closed = false;

    message.push_back('\0');

    char bytes_sent = skt.sendall(message.c_str(), message.length(), &was_closed);
    if (bytes_sent < 0) {
        printf("Hubo un error en el send\n");
    }
    return;
}
