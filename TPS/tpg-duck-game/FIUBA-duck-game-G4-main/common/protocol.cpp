#include "protocol.h"

#include <stdexcept>
#include <utility>

#include <arpa/inet.h>

Protocol::Protocol(Socket& socket): skt(socket), was_closed(false) {}

void Protocol::check_is_closed() {
    if (was_closed) {
        throw std::runtime_error("Socket cerrado");
    }
}

void Protocol::send_byte(const uint8_t& byte) {
    skt.sendall(&byte, sizeof(byte), &was_closed);
    check_is_closed();
}

void Protocol::send_2_bytes(const uint16_t& bytes) {
    uint16_t serial_size = htons(bytes);
    skt.sendall(&serial_size, sizeof(serial_size), &was_closed);
    check_is_closed();
}

void Protocol::send_string(const std::string& string) {
    uint16_t name_size = string.length();
    send_2_bytes(name_size);
    skt.sendall(string.c_str(), name_size, &was_closed);

    check_is_closed();
}

void Protocol::receive_byte(uint8_t& byte) {
    skt.recvall(&byte, sizeof(byte), &was_closed);
    check_is_closed();
}


void Protocol::receive_2_bytes(uint16_t& bytes) {
    skt.recvall(&bytes, sizeof(bytes), &was_closed);
    bytes = ntohs(bytes);
    check_is_closed();
}

void Protocol::receive_string(std::string& string) {
    uint16_t string_size;
    receive_2_bytes(string_size);

    char buffer_name[MAX_LENGTH_BUFFER];
    skt.recvall(buffer_name, string_size, &was_closed);
    string = std::string(buffer_name, string_size);
    check_is_closed();
}

void Protocol::kill() {
    if (was_closed) {
        was_closed = false;
        skt.shutdown(2);
        skt.close();
    }
}
