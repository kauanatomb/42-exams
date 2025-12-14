#include "set.hpp"
#include "searchable_array_bag.hpp"

set::set(searchable_bag& sb) : bag(&sb) {} // dont copy its a wrapper class
set::set(const set& other) : bag(other.bag) {}
set& set::operator=(const set& other) {
    if (this != &other)
        bag = other.bag;
    return *this;
}
set::~set() {}

searchable_bag& set::get_bag() const {
    return *bag;
}

//set definition: data type that can store unique values, without any particular order. Magic happens in the function down:

void set::insert (int value) {
    if (!bag->has(value))
        bag->insert(value);
}

// Use the function above!
void set::insert (int *data, int size) {
    for(int i = 0; i < size; i++) {
        this->insert(data[i]);
    }
}
void set::print() const {
    bag->print();
}
void set::clear() {
    bag->clear();
}
bool set::has(int value) const {
    return bag->has(value);
}