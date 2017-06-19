#ifndef MAP_H
#define MAP_H

#include "bnode.h"
#include "bst.h"
#include "pair.h"

template <class K, class V>
class Map
{
public:
   Map() : numItems(0) {}
   ~Map() { bst.clear(); }
   Map(const Map <K, V> & in_source) throw (const char *);
   bool empty() const { bst.empty(); }
   int size() const { bst.size(); }
   
private:
   int numItems;
   BST < Pair < K, V > > bst;
};

class MapIterator
{
public:
   bool operator == (const MapIterator<K, V> & rhs);
   bool operator != (const MapIterator<K, V> & rhs);
};

/******************************************************************
* MAP :: COPY CONSTRUCTOR
******************************************************************/
template <class K, class V>
Map <K, V> :: Map(const Map <K, V> & in_source) throw (const char *)
{
   bst = in_source.bst;
   numItems = in_source.numItems;
}

/******************************************************************
* MAP :: ASSIGNMENT OPERATOR
*******************************************************************/
template <class K, V>
Map <K, V> Map <K, V> :: operator = (const Map <K, V> & rhs)
{
   this->bst = in_source.bst;
   this->numItems = in_source.numItems;
   return *this;
}

/************************************************************************
* :: EQUAL (MAPITERATOR)
* Indicates whether two MapIterators point to the same node
*************************************************************************/
template <class K, class V>
bool MapIterator<K, V> :: operator == (const MapIterator<K, V> & rhs)
{
   return; // nodes.top() == rhs.nodes.top();
}

/************************************************************************
* :: NOT EQUAL (MAPITERATOR)
* Indicates whether two MapIterators point to the same node
*************************************************************************/
template <class K, class V>
bool MapIterator<K, V> :: operator != (const MapIterator<K, V> & rhs)
{
   return; // nodes.top() != rhs.nodes.top();
}
//operator ==	Bryan
//operator !=	Bryan


#endif //MAP_H
