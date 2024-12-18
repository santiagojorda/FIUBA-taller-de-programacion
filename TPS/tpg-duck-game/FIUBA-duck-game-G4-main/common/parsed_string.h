#ifndef PARSED_STRING_H
#define PARSED_STRING_H

#include <cstdint>
#include <string>
#include <vector>


class ParsedString {
private:
    const std::string msg;

public:
    explicit ParsedString(const std::string& _msg);

    // Carga el vector_data con el string parseado
    void charge_vector(std::vector<uint8_t>& vector_data);

    ~ParsedString();
};

#endif  // PARSED_STRING_H
