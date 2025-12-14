#pragma once

class bag
{
 public:
	virtual ~bag() {} // added to not have leaks in main
	virtual void insert (int) = 0;
	virtual void insert (int *, int) = 0;
	virtual void print() const = 0;
	virtual void clear() = 0;
};
