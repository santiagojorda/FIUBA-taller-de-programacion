#include "parsed_string.h"

#include <algorithm>

#include <arpa/inet.h>
#include <string.h>

const uint8_t MASKFIRSDBYTE = 0xFF;
const int SHIFSECONDBYTES = 8;

ParsedString::ParsedString(const std::string& _msg): msg(_msg) {}

void ParsedString::charge_vector(std::vector<uint8_t>& vector_data) {
    uint16_t lengtBig = htons(this->msg.size());
    vector_data.push_back(lengtBig & MASKFIRSDBYTE);
    vector_data.push_back(lengtBig >> SHIFSECONDBYTES);
    std::for_each(this->msg.begin(), this->msg.end(), [&](auto c) { vector_data.push_back(c); });
}


ParsedString::~ParsedString() {}
