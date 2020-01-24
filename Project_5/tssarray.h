// TSSArray.h
// Malvika Shriwas
// Chaweinta Hale
// Started: 2019-10-29
// Updated: 2019-10-31

// For CS 311 Fall 2019
// Header for class TSSArray

#ifndef FILE_TSSArray_H_INCLUDED
#define FILE_TSSArray_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max, std::rotate, std::swap, std::copy

// *********************************************************************
// class TSSArray - Class definition
// *********************************************************************


// class TSSArray
// Templated Seriously Smart Array of value_type.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of value_type, allocated with new[], owned by
//      *this, holding _size value_type-- UNLESS _capacity == 0, which case
//      _data may be nullptr.
//      Type Requirements:
//           T must have copy constructor, copy assignment, destructor, usable with std::copy
//           size_type must be non negative

template <typename T>
class TSSArray {

// ***** TSSArray: types *****
public:

    // value_type: type of data items
    using value_type = T;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** TSSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 16 };

// ***** TSSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Pre: A non-negative integer  giving the number of elements in the TSSArray or
    // if none is given, TSSArray _size is set to zero.
    // Exception-neutral
    // Strong Guarantee
    explicit TSSArray(size_type size = 0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Pre: begin and end must be defined for passed TSSArray
    // Exception-neutral
    // Strong Guarantee
    TSSArray(const TSSArray & other):
            _capacity(other._capacity),
            _size(other._size),
            _data(new value_type[other._capacity])
    {
        try{
            std::copy(other.begin(), other.end(), this->begin());
        } catch(...)
        {
            delete [] _data;
            throw;
        }
    }

    // Move ctor
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    TSSArray(TSSArray&& other) noexcept
		:_capacity(other._capacity),
		_size(other._size),
		_data(other._data)
{
		other._capacity = 0;
		other._size = 0;
		other._data = nullptr;
}

    // Dctor
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    ~TSSArray()
    {
        delete [] _data;
    }
    // Copy assignment
    // Pre: Swap must be defined for passed TSSArray
    // Exception-neutral
	// Strong Guarantee
	TSSArray& operator=(const TSSArray& rhs)
	{
		TSSArray copyRhs(rhs);
		swap(copyRhs);
		return *this;
	}
    // Move assignment
    // Pre: Swap must be defined for passed TSSArray
    // Exception-neutral
    // No-Throw Guarantee
    TSSArray & operator=(TSSArray && rhs) noexcept{
        swap(rhs);
		return *this;
    }

// ***** TSSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // Pre: Integer subscript from zero to _size-1
    // Exception-neutral
    // No-Throw Guarantee
    value_type & operator[](size_type index) noexcept
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const noexcept
    {
        return _data[index];
    }

// ***** TSSArray: general public functions *****
public:

    // size
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // Pre: N/a
    // Exception-neutral
    // No-Throw Guarantee
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

    // resize
    // Pre: non-negative new size
    // Exception-neutral
    // Strong Guarantee
    void resize(size_type newsize){
        if(newsize <= _capacity){
             _size = newsize;
        }
        else{
            size_type max = std::max(newsize, (_capacity * 2));
			value_type* testArray = new value_type[max];
			try
			{
				std::copy(begin(), end(), testArray);
			}
			catch (...)
			{
				delete[] testArray;
				throw;
			}
            delete [] _data;
            _capacity = max;
            _data = testArray;
			_size = newsize;
        }
    }

    // insert
    // Pre: An iterator and a data item. Iterator points to location for data
    // item to be inserted before. Unless iterator is to end, in which case data
    // item will be inserted at end.
    // Exception-neutral
    // Basic Guarantee
    iterator insert(iterator pos,
                    const value_type & item)
    {
        size_type index = pos - begin();
        resize(_size+1);
        _data[_size-1] = item;
        std::rotate(begin() + index, end() - 1, end());
        return begin()+ index;
    }

    // erase
    // Pre: An iterator to item to be removed
    // Exception-neutral
    // Basic Guarantee
    iterator erase(iterator pos){
        std::rotate(pos, pos+1, end());
        resize(_size-1);
        return pos;
    }

    // push_back
    // Pre: Item of value_type , which will be added
    // to end of array.
    // Exception-neutral
    // Basic Guarantee
    void push_back(value_type item)
    {
        insert(end(), item);
    }

    // pop_back
    // Pre: Current _size of TSSArray should be greater than zero or else pop_back does nothing
    // Exception-neutral
    // Basic Guarantee
    void pop_back()
    {
        if(_size > 0){
            resize(_size-1);
        }
    }

    // swap
    // Pre: TSArray of same value type
    // Exception-neutral
    // No-Throw Guarantee
    void swap(TSSArray & other) noexcept{
        std::swap(_capacity, other._capacity);
        std::swap(_size,other._size);
        std::swap(_data,other._data);
    }

// ***** TSSArray: data members *****
private:

    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class TSSArray

#endif //#ifndef FILE_TSSArray_H_INCLUDED
