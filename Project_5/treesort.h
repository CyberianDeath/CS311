// Malvika Shriwas
// Chaweinta Hale
// Started: 11/13/2019
// Finished: 11/17/2019
//
// For CS 311 Fall 2019
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <iterator> // For std::iterator_traits
#include <algorithm> // For std::move
#include <iterator> // For std::distance
#include <memory>   //For unique_ptr

template <typename ValType>
struct TreeNode{
    ValType _data;
	std::unique_ptr<TreeNode> _left;
    std::unique_ptr<TreeNode> _right;
	explicit TreeNode(const ValType& data)
		:_data(data), _left(nullptr), _right(nullptr){};
	~TreeNode() = default;
	TreeNode() = delete;
	TreeNode(const TreeNode& other) = delete;
	TreeNode& operator=(TreeNode&& other) = delete;
	TreeNode& operator=(const TreeNode& other) = delete;
	TreeNode(TreeNode&& other) = delete;
};


// treesort
// Sort a given range using treesort.
// Pre:
//     Two valid forward iterators
// Requirements on Types:
//     Forward iterator must have copy constructor
// Exception safety guarantee:
//     Strong guarantee
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    using ValType = typename std::iterator_traits<FDIter>::value_type;
    if (std::distance(first, last) == 0){
        return;
    }
    std::unique_ptr<TreeNode<ValType>> head = std::make_unique<TreeNode<ValType>>(*first);
    FDIter temp = first;
    while(std::distance(temp, last) != 1){
        std::advance(temp, 1);
        insertTN(head.get(), *temp);
    }
    traverseTN(head.get(), first);
}
// insertTN
// Insert Tree Node - Insert a new item into the binary tree at the end
// Pre:
//     Smart Head pointer for a binary tree and item to be inserted
// Requirements on Types:
//     ValType  must have copy constructor
//exception-neutral
//Strong guarantee
template <typename ValType>
void insertTN(TreeNode<ValType>* head, const ValType& item){
        while(head){
            if(item < (head->_data)){
                if((head->_left) == nullptr){
                    head->_left = std::make_unique<TreeNode<ValType>>(item);
                    break;
                }
            head = head->_left.get();
            } else{
                if((head->_right) == nullptr){
                    head->_right = std::make_unique<TreeNode<ValType>>(item);
                    break;
                }
            head = head->_right.get();
            }
        }
}
//TraverseTN
//Traverse Tree Node -inorder-traversal for a binary tree
//Pre:
//     Smart Head pointer for a binary tree and valid forward iterator pointing to first item in the list
// Requirements on Types:
//     ValType must have copy constructor, FDIter must have ++operator
//exception-neutral
//no-throw guarantee
template <typename ValType, typename FDIter>
void traverseTN(TreeNode<ValType>* head, FDIter &first){
        if(head){
            traverseTN(head->_left.get(), first);
            *first++ = std::move(head->_data);
            traverseTN(head->_right.get(), first);
        }
}
#endif //#ifndef FILE_TREESORT_H_INCLUDED
