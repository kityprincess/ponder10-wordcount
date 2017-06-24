/***********************************************************************
* Component:
*    Week 09, Binary Search Tree (BST)
*    Brother Helfrich, CS 235
* Author:
*    Shayla Nelson, Matthew Burr, Kimberly Stowe, Bryan Lopez
* Summary:
*    The BST class creates a binary search tree and the BSTIterator
*        class gives a way to iterator or move through it.
************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>
#include <stack>
#include "bnode.h"

template <class T>
class BST; // fwd declaration

/*************************************************************************
* CLASS: BSTITERATOR
* Iterator for a BST
**************************************************************************/
template <class T>
class BSTIterator
{
public:
   friend class BST<T>;

   // The nodes stack should always have a NULL pointer at its head
   // This helps us easily tell when we've emptied the stack and it helps
   // in comparing the top() to the NULL (end) iterator
   BSTIterator() { nodes.push(NULL); }
   BSTIterator(BinaryNode<T> * in_node)
   {
      nodes.push(NULL);
      nodes.push(in_node);
   }
   // We assume that the source has a well-formed stack that has a NULL
   // at its head
   BSTIterator(std::stack<BinaryNode<T> * > in_stack) { nodes = in_stack; }
   BSTIterator(const BSTIterator <T> & in_source);
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs);
   BSTIterator <T> & operator -- ();
   BSTIterator <T> & operator ++ ();
   bool operator == (const BSTIterator<T> & rhs);
   bool operator != (const BSTIterator<T> & rhs);
   T & operator * () const { return nodes.top()->data; }

private:
   std::stack<BinaryNode<T> * > nodes;
};

/*******************************************
* BSTITERATOR :: COPY CONSTRUCTOR
*******************************************/
template <class T>
BSTIterator <T> ::BSTIterator(const BSTIterator <T> & in_source)
{
   *this = in_source;
}

/*******************************************
* BSTITERATOR :: ASSIGNMENT OPERATOR
*******************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator = (const BSTIterator <T> & rhs)
{
   this->nodes = rhs.nodes;
   return *this;
}

/**************************************************
* BST ITERATOR :: DECREMENT PREFIX
*     advance by one. Note that this implementation uses
*     a stack of nodes to remember where we are. This stack
*     is called "nodes".
* Author:      Br. Helfrich
* Performance: O(log n) though O(1) in the common case
*************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
* BST ITERATOR :: INCREMENT PREFIX
*     advance by one. This implementation closely
* follows Bro. Helfrich's but also the guidance
* from the assignment
*************************************************/
template<class T>
inline BSTIterator <T> & BSTIterator <T> :: operator ++()
{
   if (NULL == nodes.top())
      return *this;

   if (NULL != nodes.top()->pRight)
   {
      nodes.push(nodes.top()->pRight);

      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);

      return *this;
   }

   BinaryNode<T> * pSave = nodes.top();
   nodes.pop();

   if (NULL == nodes.top())
      return *this;

   if (pSave == nodes.top()->pLeft)
      return *this;

   while (nodes.top() != NULL && nodes.top()->pRight == pSave)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/************************************************************************
* :: EQUAL (BSTITERATOR)
* Indicates whether two BSTIterators point to the same node
*************************************************************************/
template <class T>
bool BSTIterator<T> :: operator == (const BSTIterator<T> & rhs)
{
   return nodes.top() == rhs.nodes.top();
}

/************************************************************************
* :: NOT EQUAL (BSTITERATOR)
* Indicates whether two BSTIterators point to the same node
*************************************************************************/
template <class T>
bool BSTIterator<T> :: operator != (const BSTIterator<T> & rhs)
{
   return nodes.top() != rhs.nodes.top();
}

/***************************************************************************
* CLASS: BST
* A Binary Search Tree
****************************************************************************/
template <class T>
class BST
{
public:
   BST() : root(NULL) { }
   ~BST() { clear(); }
   BST(const BST <T> & in_source) throw (const char *);
   BST & operator = (const BST & in_source);

   int size() const;
   bool empty() const { return root == NULL; }
   void clear() { deleteBinaryTree(root); root = NULL; }
   void insert(const T & in_value);
   void remove(const BSTIterator<T> & in_pItem);

   BSTIterator<T> find(const T & in_value) const;
   BSTIterator<T> begin() const;
   // end is simply an iterator with a NULL pointer at the top of its stack
   BSTIterator<T> end() { return BSTIterator <T>(NULL); }
   BSTIterator<T> rbegin() const;
   // rend is an iterator with a NULL pointer at the top of its stack
   BSTIterator<T> rend() { return BSTIterator <T>(NULL); }

   BinaryNode <T> * getRoot() const { return root; }

   void redBlack(BinaryNode<T> * & in_node);

private:
   void insertInternal(const T & in_value, BinaryNode<T> * & in_subtree, BinaryNode<T> * parent);
   BinaryNode <T> * findLeft(BinaryNode <T> * pElement) const;
   BinaryNode <T> * findRight(BinaryNode <T> * pElement) const;
   BinaryNode <T> * copy(BinaryNode <T> * pElement);
   BinaryNode <T> * root;
};

/*******************************************
* BST :: COPY CONSTRUCTOR
*******************************************/
template <class T>
BST <T> :: BST(const BST <T> & in_source) throw (const char *)
{
   this->root = copy(in_source.root);
}

/*******************************************
* BST :: ASSIGNMENT OPERATOR
*******************************************/
template <class T>
BST<T> & BST<T> :: operator = (const BST & in_source)
{
   this->root = copy(in_source.root);
   return *this;
}

/*****************************************
* BST:: SIZE
* Number of elements in binary search tree.
*****************************************/
template <class T>
int BST<T> :: size() const
{
   // no elements in tree
   if (root == NULL)
      return 0;

   // add root and any subtrees
   int size = 1;

   if (root->pLeft)
      size += root->pLeft->size();

   if (root->pRight)
      size += root->pRight->size();

   return size;
}

/**************************************************
* BST :: INSERT
* Adds a new value to the BST in the appropriate
* spot.
* Note: DOES NOT ATTEMPT TO BALANCE THE TREE
*************************************************/
template<class T>
void BST<T> :: insert(const T & in_value)
{
   insertInternal(in_value, root, NULL);
}

/**************************************************
* BST :: REMOVE
* Remove a value from the BST and adjust tree.
*************************************************/
template<class T>
void BST<T> :: remove(const BSTIterator<T> & in_pItem)
{
   BinaryNode <T> * node = in_pItem.nodes.top();

   // No item to remove
   if (!node)
   {
      return;
   }

   //Case where there are 2 children
   if (node->pLeft != NULL && node->pRight != NULL)
   {
      // find the in-order successor
      BinaryNode <T> * successor = node->pRight;
      while (successor->pLeft != NULL)
      {
         successor = successor->pLeft;
      }
      node->data = successor->data;
      node = successor;
   }

   // Case where there are no children or 1 child
   BinaryNode <T> * subtree = node->pLeft;
   if (subtree == NULL)
      subtree = node->pRight;
   if (node->pParent == NULL)
      root = subtree;
   else if (node->pParent->pLeft == node)
      node->pParent->pLeft = subtree;
   else
      node->pParent->pRight = subtree;

   delete node;
}

/**************************************************
* BST :: FIND
* Finds the data by going through the tree
*************************************************/
template <class T>
BSTIterator<T> BST<T> :: find(const T & in_value) const
{
   BinaryNode<T> * result = root;
   while (result != NULL && in_value != result->data)
   {
      if (in_value < result->data)
      {
         result = result->pLeft;
      }
      else
         result = result->pRight;
   }

   return BSTIterator<T>(result);
}

/**************************************************
* BST :: BEGIN
* Returns an iterator to the leftmost element in the list
*************************************************/
template <class T>
BSTIterator<T> BST<T> :: begin() const
{
   // Per the guidance in the assignment, it is best
   // if the iterator already has a stack with the nodes
   // from the left-most element to the root of the tree
   std::stack<BinaryNode<T> *> temp;

   // We push a NULL at the head of the stack so that
   // we know when we've reached the end
   temp.push(NULL);

   // Now, we push all the nodes from the root down
   // to the left-most node
   BinaryNode<T> * node = root;
   while (NULL != node)
   {
      temp.push(node);
      node = node->pLeft;
   }

   // We now have a stack where the top() is the left-most
   // node of our tree and the nodes below it proceed up
   // to the root. We build an iterator from this stack
   return BSTIterator<T>(temp);
}

/**************************************************
* BST :: RBEGIN
* Returns an iterator to the rightmost element in the list
*************************************************/
template <class T>
BSTIterator<T> BST<T> :: rbegin() const
{
   // This works the same as the BEGIN function
   // except that here we want to build the stack
   // from the root to the rightmost node
   std::stack<BinaryNode<T> *> temp;
   temp.push(NULL);

   BinaryNode<T> * node = root;
   while (NULL != node)
   {
      temp.push(node);
      node = node->pRight;
   }

   return BSTIterator<T>(temp);
}

/**************************************************
* BST :: INSERTINTERNAL
* Implements a recursive algorithm to insert a
* binary node in the right spot
* Note: DOES NOT ATTEMPT TO BALANCE THE TREE
*************************************************/
template<class T>
void BST<T> :: insertInternal(const T & in_value, BinaryNode<T> * & in_subtree, BinaryNode<T> * parent)
{
   if (NULL == in_subtree)
   {
      try
      {
         in_subtree = new BinaryNode <T>(in_value);
         in_subtree->pParent = parent;
         redBlack(in_subtree);
      }
      catch (std::bad_alloc ex)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   else if (in_value <= in_subtree->data)
      insertInternal(in_value, in_subtree->pLeft, in_subtree);
   else if (in_value > in_subtree->data)
      insertInternal(in_value, in_subtree->pRight, in_subtree);
   else
      return;
}

/**************************************************
* BST :: REDBLACK
* Implements a recursive algorithm to insert a
* binary node in the right spot
* Note: DOES NOT ATTEMPT TO BALANCE THE TREE
*************************************************/
template<class T>
void BST<T> :: redBlack(BinaryNode<T> * & in_node)
{
   // create pointers to make coding simpler
   // pointer for new node's parent
   BinaryNode <T> * parent = in_node->pParent;

   // pointer for new node's grandparent
   BinaryNode <T> * granny = NULL;
   if (parent != NULL)
      granny = parent->pParent;

   BinaryNode <T> * greatGrandpa = NULL;
   if (granny != NULL)
      greatGrandpa = granny->pParent;

   // pointer for new node's aunt
   BinaryNode <T> * aunt = NULL;
   if (granny != NULL && granny->isLeftChild(parent))
      aunt = granny->pRight;
   else if (granny != NULL && granny->isRightChild(parent))
      aunt = granny->pLeft;

   // pointer for new node's sibling
   BinaryNode <T> * sibling = NULL;
   if (parent != NULL && parent->isLeftChild(in_node))
      sibling = parent->pRight;
   else if (parent != NULL && parent->isRightChild(in_node))
      sibling = parent->pLeft;

   // pg 219
   // case 1 - no parent, in_node is root
   // set in_node to black
   if (parent == NULL) {
      in_node->isRed = false;
      return;
   }
   // case 2 - parent is black
   // do nothing
   if (!parent->isRed) {
      return;
   }

   assert(granny != NULL);
   assert(!granny->isRed);  // if granny is red, we violate red-red!

   // case 3 - parent is red, aunt is red or na, gp is black
   // change gp to red, parent & aunt to black
   if (aunt != NULL && aunt->isRed)
   {
      granny->isRed = true;
      parent->isRed = false;
      aunt->isRed = false;
      redBlack(granny);
      return;
   }

   assert(parent->isRed && !granny->isRed && (aunt == NULL || !aunt->isRed));

   // case 4.1
   if (parent->isLeftChild(in_node) && granny->isLeftChild(parent))
   {
      assert(granny->isRightChild(aunt));
      assert(in_node->isRed);

      granny->isRed = true;
      parent->isRed = false;

      // rotate right
      granny->addLeft(sibling);
      parent->addRight(granny);

      // replace grandparent
      if (greatGrandpa == NULL)
      {
         root = parent;
      }
      else if (greatGrandpa->isLeftChild(granny))
      {
         greatGrandpa->pLeft = parent;
      }
      else if (greatGrandpa->isRightChild(granny))
      {
         greatGrandpa->pRight = parent;
      }
   }

   // case 4.2
   else if (parent->isRightChild(in_node) && granny->isRightChild(parent))
   {
      assert(!granny->isRed);
      assert(granny->isLeftChild(aunt));

      // rotate left
      granny->addRight(sibling);
      parent->addLeft(granny);

      // replace grandparent
      if (greatGrandpa == NULL)
      {
         parent->pParent = NULL;
         root = parent;
      }
      else if (greatGrandpa->isLeftChild(granny))
      {
         greatGrandpa->addLeft(parent);
      }
      else if (greatGrandpa->isRightChild(granny))
      {
         greatGrandpa->addRight(parent);
      }

      granny->isRed = true;
      parent->isRed = false;
   }

   // case 4.4
   else if (parent->isLeftChild(in_node) && granny->isRightChild(parent))
   {
      assert(granny->isLeftChild(aunt));
      assert(parent->isRightChild(sibling));

      BinaryNode<T> * temp = new BinaryNode <T>(in_node->data);
      granny->addRight(in_node->pLeft);
      parent->addLeft(in_node->pRight);
      temp->addLeft(granny);
      temp->addRight(parent);
      in_node = temp;

      // replace grandparent
      if (greatGrandpa == NULL)
      {
         in_node->pParent = NULL;
         root = in_node;
      }
      else if (greatGrandpa->isLeftChild(granny))
      {
         greatGrandpa->addLeft(in_node);
      }
      else if (greatGrandpa->isRightChild(granny))
      {
         greatGrandpa->addRight(in_node);
      }

      in_node->isRed = false;
      granny->isRed = true;
   }

   // case 4.3
   else if (parent->isRightChild(in_node) && granny->isLeftChild(parent))
   {
      assert(granny->isRightChild(aunt));
      assert(parent->isLeftChild(sibling));
      assert(parent->isRed);

      BinaryNode<T> * temp = new BinaryNode <T>(in_node->data);
      granny->addLeft(in_node->pRight);
      parent->addRight(in_node->pLeft);
      temp->addLeft(parent);
      temp->addRight(granny);
      in_node = temp;

      // replace grandparent
      if (greatGrandpa == NULL)
      {
         in_node->pParent = NULL;
         root = in_node;
      }
      else if (greatGrandpa->isLeftChild(granny))
      {
         greatGrandpa->addLeft(in_node);
      }
      else if (greatGrandpa->isRightChild(granny))
      {
         greatGrandpa->addRight(in_node);
      }

      in_node->isRed = false;
      granny->isRed = true;
   }
}

/**************************************************
* BST :: FINDLEFT
* Finds the leftmost data element.
*************************************************/
template <class T>
BinaryNode <T> * BST <T> ::findLeft(BinaryNode <T> * pElement) const
{
   BinaryNode <T> * tempLeft = NULL;

   if (pElement != 0)
   {
      findLeft(pElement->pLeft);
      tempLeft = pElement;
   }

   return tempLeft;
}

/**************************************************
* BST :: FINDRIGHT
* Finds the rightmost data element.
*************************************************/
template <class T>
BinaryNode <T> * BST<T> :: findRight(BinaryNode <T> * pElement) const
{
   BinaryNode <T> * tempRight = NULL;

   if (pElement != 0)
   {
      findRight(pElement->pRight);
      tempRight = pElement;
   }

   return tempRight;
}

/***********************************************************************
* BST :: COPY
* Copies over the elements in a tree
***********************************************************************/
template <class T>
BinaryNode<T> * BST<T> :: copy(BinaryNode <T> * pElement)
{
   if (pElement == NULL)
   {
      return pElement;
   }

   BinaryNode <T> * newNode;
   try
   {
      newNode = new BinaryNode <T>(pElement->data);

      newNode->pLeft = copy(pElement->pLeft);
      newNode->pRight = copy(pElement->pRight);

   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   return newNode;
}

#endif // BST_H
