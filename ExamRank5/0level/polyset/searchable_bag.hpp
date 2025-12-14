#pragma once

#include "bag.hpp"

class searchable_bag : virtual public bag // virtual inheritance
{
 public:
 	virtual ~searchable_bag() {} //added to not have leaks
	virtual bool has(int) const = 0;
};
