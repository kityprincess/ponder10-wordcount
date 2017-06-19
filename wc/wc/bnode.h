
/***********************************************************************
* Header:
*    Bnode
* Summary:
*    This class contains a binary node for use in a binary tree.
* Author:
*    Bryan Lopez, Kimberly Stowe, Matthew Burr, Shayla Nelson
************************************************************************/

#ifndef	BNODE_H
#define	BNODE_H

#include <iostream>
#include <cassert>
using namespace std;

/************************************************
* BNODE
* A class that constructs a binary node.
***********************************************/
template <class T>
class BinaryNode
{
public:
   BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL), numElements(1) {}
   BinaryNode(T in_data): data(in_data), pRight(NULL), pParent(NULL), pLeft(NULL), numElements(1) {}

   void addLeft(const T & t);
   void addLeft(BinaryNode <T> * pAdd);
   void addRight(const T & t);
   void addRight(BinaryNode <T> * pAdd);
   int size();
   void verifyRedBlack(int depth) const;
   int findDepth() const;
   void verifyBTree() const;
   bool operator == (const BinaryNode & rhs);

public:
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
   int numElements;
   bool isRed;
};

/*****************************************
* BNODE :: ADDLEFT
* Adds data to the left branch
*****************************************/
template<class T>
void BinaryNode<T> :: addLeft(const T & in_data)
{
   BinaryNode<T> * leftNode = new BinaryNode<T>(in_data);
   leftNode->pParent = this;
   pLeft = leftNode;
}

/*****************************************
* BNODE :: ADDLEFT
* Adds data to the left branch - template
*****************************************/
template<class T>
void BinaryNode<T> :: addLeft(BinaryNode<T> * in_tree)
{
   pLeft = in_tree;
   if (pLeft)
      pLeft->pParent = this;
}

/*****************************************
* BNODE :: ADDRIGHT
* Adds data to the right branch
*****************************************/
template<class T>
void BinaryNode<T> :: addRight(const T & in_data)
{
   BinaryNode<T> * rightNode = new BinaryNode<T>(in_data);
   rightNode->pParent = this;
   pRight = rightNode;
}

/*****************************************
* BNODE :: ADDRIGHT
* Adds data to the right branch - template
*****************************************/
template<class T>
void BinaryNode<T> :: addRight(BinaryNode<T> * in_tree)
{
   pRight = in_tree;
   if (pRight)
      pRight->pParent = this;
}

/*****************************************
* BNODE :: SIZE
* Number of elements in tree
*****************************************/
template <class T>
int BinaryNode <T> :: size()
{
   int size = 1;

   if (pLeft)
      size += pLeft->size();

   if (pRight)
      size += pRight->size();

   return size;
}

/*******************************************
 * BNODE :: EQUALITY OPERATOR
 *******************************************/
template <class T>
bool BinaryNode<T> :: operator == (const BinaryNode & rhs)
{
   return this->data == rhs.data &&
         this->pLeft == rhs.pLeft &&
         this->pRight == rhs.pRight &&
         this->pParent == rhs.pParent &&
         this->numElements == rhs.numElements;
}

/*****************************************
* BNODE :: INSERTION OPERATOR
* Displays the contents of the list forwards
*****************************************/
template<class T>
ostream & operator<<(ostream & out, const BinaryNode<T>* element)
{
   if (element == NULL)
      return out;
   if (element->pLeft)
      out << element->pLeft;
   out << element->data;
   out << " ";
   if (element->pRight)
      out << element->pRight;
   return out;
}

/************************************************************
* Delete Binary Tree:
* Deletes all the elements in the tree
************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * in_tree)
{
   if (in_tree == NULL)
      return;
   deleteBinaryTree(in_tree->pLeft);
   deleteBinaryTree(in_tree->pRight);
   delete in_tree;
}

// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 * Author: Br. Helfrich
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 * Author: Br. Helfrich
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 * Author: Br. Helfrich
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}


#endif // BNODE_H
