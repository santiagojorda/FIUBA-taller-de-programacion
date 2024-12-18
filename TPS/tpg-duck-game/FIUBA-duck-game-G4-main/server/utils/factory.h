#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include <iostream>

template <typename TYPE, typename PRODUCT>
class Factory {
protected:
    // cppcheck-suppress unusedStructMember
    std::unordered_map<TYPE, std::shared_ptr<PRODUCT>> items;

public:
    Factory() {}

    // Prohibir copia
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    // Constructor por movimiento
    Factory(Factory&& other) noexcept
        : items(std::move(other.items)) {}

    // Operador de asignación por movimiento
    Factory& operator=(Factory&& other) noexcept {
        if (this != &other) {
            items = std::move(other.items);
        }
        return *this;
    }

    void add(const TYPE& type_id, std::shared_ptr<PRODUCT> new_item) {
        items[type_id] = std::move(new_item);
    }

    std::shared_ptr<PRODUCT> get(const TYPE& type_id) {
        auto it = items.find(type_id);
        if (it != items.end()) {
            return it->second;
        }
        throw std::runtime_error("Item no encontrado para el tipo proporcionado.");
    }

    virtual ~Factory() {
        // items.clear();
    }
};

#endif 
