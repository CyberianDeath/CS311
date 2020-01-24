// dp6.h
// Malvika Shriwas
// Chaweinta Hale
// Started: 11/4/2019
// Updated: 11/07/2019
// For CS311 Project6

#ifndef FILE_DP6_H_INCLUDED
#define FILE_DP6_H_INCLUDED

#include "llnode2.h"
#include <memory>   //for std::unique_ptr
#include <cstddef>  //for std::size_t
#include <utility>  //for std::pair
#include <algorithm>    //for std::swap


// Exercise A

template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>>& head) {
    unique_ptr<LLNode2<ValType>> newhead = nullptr;
    while (head){
        std::swap(head,newhead);
        std::swap(head,newhead->_next);
    }
    std::swap(head,newhead);
}

//Exercise B

// class LLMap
// class template that uses a Linked List to hold an associative dataset
// Invariants:
//      Either _next is nullptr, or _next points to an LLNode,
//      Type Requirements:
//           KType must have =,==operators
//           DType must have a copy ctor and a (non-throwing) dctor.
//           size_type must be non negative
template<class KType, class DType>
class LLMap
{
// ***** LLMap: types *****
public:
    // value_type: single key value pair
	using KVTYPE = std::pair <KType, DType>;
	// size_type: type of sizes
	using size_type = std::size_t;
private:
    // data member
	std::unique_ptr<LLNode2<KVTYPE>> _node;
// ***** LLMap: ctors, op=, dctor
public:
    //Default constructor
	// Strong Guarantee
	// Exception-neutral
	LLMap():_node(nullptr){}

	//Copy Ctor
	LLMap(const LLMap& other) = delete;

	//Copy Assignment
	LLMap& operator =(const LLMap& other) = delete;

	//Move Ctor
	LLMap(LLMap&& other) = delete;

	//Move Assignment
	LLMap& operator =(LLMap&& other) = delete;

	//Destructor
    // Pre: N/a
    // No-Throw Guarantee
    // Exception-neutral
	~LLMap() = default;

// ***** LLMap: general public functions *****
    // size
    // Pre: N/a
    //Returns an integer of an appropriate type giving the number of key-value pairs in the dataset.
    // Strong Guarantee
    // Exception-neutral
    size_type size() const {
		size_type counter = 0;
        LLNode2<KVTYPE>* current = _node.get();
            while(current)
            {
                ++counter;
                current = current->_next.get();
            }
        return counter;
	}

	// empty
	// Pre: N/a
	// Returns a bool indicating whether there are no key-value pairs in the dataset
	// No Throw Guarantee
    // Exception-Neutral
	bool empty()const {
		return !_node;
	}

	// find - non-const & const
	// Pre: A KType key that is comparable to node's other keys.
	// If the key lies in the dataset, then the returned pointer points to the associated value.
	//Otherwise, the returned pointer is nullptr.
	// No-Throw Guarantee
	// exception-neutral
	DType* find(const KType& key){
		LLNode2<KVTYPE>* current = _node.get();
        while (current){
            if (current->_data.first == key){
                return &current->_data.second;
            }
            current = current->_next.get();
			}
        return nullptr;
	}
	const DType* find(const KType& key) const {
		LLNode2<KVTYPE>* current = _node.get();
        while (current){
            if (current->_data.first == key){
                return &current->_data.second;
            }
            current = current->_next.get();
			}
        return nullptr;
	}

	// insert
	// Pre: A KType key and an associated DType value.
	// If an equal key does not lie in the dataset, then the key-value pair is inserted.
	//If an equal key does lie in the dataset, then the existing key-value pair is replaced with that given.
	// Basic Guarantee
	// exception-neutral
    void insert(const KType& key, const DType& value){
        DType* ptr = find(key);
        if(ptr){
            *ptr = value;
        }else {
            push_front(_node, {key, value});
        }
    }
	// erase
	// Pre: KType key
	//  If an equal key lies in the dataset, then that key-value pair is removed.
	//If an equal key does not lie in the dataset, then the function does nothing.
	// Basic Guarantee
	// exception-neutral
    void erase(const KType& key){
        auto current = _node.get();
		auto current2 = _node.get();
		while (current){
			if (current->_data.first == key) {
					std::swap(current2->_next, current->_next);
					current->_next= nullptr;
					current = nullptr;
			}else {
				current2 = current;
				current = current->_next.get();
			}
		}
    }
    // traverse
    // Pre: A function object
    // The passed function is called on each key-value pair in the parameter function's dataset.
    // Basic Guarantee
    // exception-neutral
	template<typename function>
	void traverse(function f){
		LLNode2<KVTYPE>* current = _node.get();
		while (current){
			f(current->_data.first, current->_data.second);
			current = current->_next.get();
		}
	}

};  // End class LLMap

#endif //#ifndef FILE_DP6_H_INCLUDED
