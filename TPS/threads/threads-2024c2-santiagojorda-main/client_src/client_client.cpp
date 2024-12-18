#include "client_client.h"

#include <iostream>
#include <string>
#include <vector>

#define WELCOME_MESSAGE "What is your name?"
#define TEXT_TOKEN_PICK_UP "Pickup"
#define TEXT_TOKEN_READ "Read"
#define TEXT_TOKEN_EXIT "Exit"

Client::Client(char* hostname, char* servname): protocol(hostname, servname) {}

void Client::run() {
    std::cout << WELCOME_MESSAGE << std::endl;
    std::string client_name;
    // std::cin >> client_name;

    std::getline(std::cin, client_name);


    try {
        std::string command;
        while (std::cin >> command) {
            if (command == TEXT_TOKEN_PICK_UP) {
                // std::cout << "LOG: Pickup" << std::endl;
                std::string box_id_str;
                std::cin >> box_id_str;
                uint8_t box_id = std::stoi(box_id_str);
                protocol.send_message_pickup(client_name, box_id);
            } else if (command == TEXT_TOKEN_READ) {
                // std::cout << "LOG: Read" << std::endl;
                std::string num_messages_str;
                std::cin >> num_messages_str;
                std::vector<std::string> messages_readed;
                uint8_t num_messages = std::stoi(num_messages_str);
                protocol.receive_n_messages(num_messages, messages_readed);
                for (const std::string& message: messages_readed) {
                    std::cout << message << std::endl;
                }
            } else if (command == TEXT_TOKEN_EXIT) {
                break;
            }
        }
        protocol.kill();

    } catch (std::exception& exp) {
        protocol.kill();
    }
}
