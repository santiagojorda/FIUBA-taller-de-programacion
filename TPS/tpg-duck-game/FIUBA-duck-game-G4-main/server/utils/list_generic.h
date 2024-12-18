#ifndef LIST_GENERIC
#define LIST_GENERIC

#include <cstdint>
#include <list>
#include <memory>

template <typename T>
class ListGeneric {
private:
    std::list<std::shared_ptr<T>> items;

public:
    ListGeneric() {}

    void add(std::shared_ptr<T> item) { items.push_back(item); }

    bool remove(std::shared_ptr<T> item) {
        bool item_exist = false;
        items.remove_if([item, &item_exist](std::shared_ptr<T> item_list) {
            if (item == item_list) {
                item_exist = true;
                return true;
            }
            return false;
        });
        return item_exist;
    }

    // void remove_and_delete(std::shared_ptr<T> item) {
    //     bool item_exist = remove(item);
    //     if (item_exist) {
    //         delete item;
    //     }
    // };

    void transfer_item(std::shared_ptr<T> item, ListGeneric<T>& other_list) {
        add(item);
        other_list.remove(item);
    }

    void clear() {
        items.clear();
    }

    int size() { return items.size(); }

    const std::list<std::shared_ptr<T>>& get_items() const { return items; }

    ~ListGeneric() { clear(); }
};

#endif
