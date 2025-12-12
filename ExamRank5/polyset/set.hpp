#ifndef set_hpp
#define set_hpp

#include "searchable_bag.hpp"

class set {
    private:
        searchable_bag* bag; // subject mention wrap the searchable bag
    public:
        set(searchable_bag& bag);
        set(const set& other);
        set& operator=(const set& other);
        ~set();

        searchable_bag& get_bag() const;
        void insert (int);
        void insert (int *, int);
	    void print() const;
	    void clear();
        bool has(int) const;

};

#endif