#ifndef searchable_array_bag_hpp
#define searchable_array_bag_hpp

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
    public:
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag& other);
        searchable_array_bag& operator=(const searchable_array_bag& other);
        ~searchable_array_bag();
        bool has(int value) const;
};

#endif