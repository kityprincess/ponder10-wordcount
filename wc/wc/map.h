#ifndef MAP_H
#define MAP_H

#include "bnode.h"
#include "bst.h"
#include "pair.h"

/*************************************************************************
* CLASS: MAPITERATOR
* Iterator for a map
**************************************************************************/
template <class K, class V>
class MapIterator
{
public:
   MapIterator() {}
   ~MapIterator() {}
   MapIterator(const BSTIterator< Pair< K, V > > & in_source) { it = in_source; }
   MapIterator(const MapIterator <K, V> & in_source);
   MapIterator <K, V> & operator = (const MapIterator <K, V> & rhs);

   bool operator == (const MapIterator<K, V> & rhs);
   bool operator != (const MapIterator<K, V> & rhs);
   // TODO: Impelement the increment and decrement
   MapIterator <K, V> & operator --() { return *this; }
   MapIterator <K, V> & operator ++() { return *this; }
   
   V & operator *() { return (*it).second; }

private:
   BSTIterator<Pair< K, V > > it;
};

/*******************************************
* MAPITERATOR :: COPY CONSTRUCTOR
*******************************************/
template <class K, class V>
MapIterator <K, V> ::MapIterator(const MapIterator <K, V> & in_source)
{
   *this = in_source;
}

/*******************************************
* MAPITERATOR :: ASSIGNMENT OPERATOR
*******************************************/
template <class K, class V>
MapIterator <K, V> & MapIterator <K, V> :: operator = (const MapIterator <K, V> & rhs)
{
   //it.nodes = rhs.nodes;
   it = rhs.it;
   return *this;
}

/************************************************************************
* :: EQUAL (MAPITERATOR)
* Indicates whether two MapIterators point to the same node
*************************************************************************/
template <class K, class V>
bool MapIterator<K, V> :: operator == (const MapIterator<K, V> & rhs)
{
   return it == rhs.it; // nodes.top() == rhs.nodes.top();
}

/************************************************************************
* :: NOT EQUAL (MAPITERATOR)
* Indicates whether two MapIterators point to the same node
*************************************************************************/
template <class K, class V>
bool MapIterator<K, V> :: operator != (const MapIterator<K, V> & rhs)
{
   return it != rhs.it; // nodes.top() != rhs.nodes.top();
}

//operator ==	Bryan
//operator !=	Bryan

/*************************************************************************
* CLASS: MAP
* Defines the map class
**************************************************************************/
template <class K, class V>
class Map
{
public:
   Map() : numItems(0) {}
   ~Map() { clear(); }
   Map(const Map <K, V> & in_source) throw (const char *);
   Map <K, V> operator = (const Map <K, V> & rhs) throw (const char *);

   bool empty() const { return bst.empty(); }
   int size() const { return bst.size(); }
   void clear() { bst.clear(); }

   MapIterator<K, V> begin() const { return bst.begin(); }
   MapIterator<K, V> end() { return bst.end(); }
   MapIterator<K, V> rbegin() const { return bst.rbegin(); }
   MapIterator<K, V> rend() { return bst.rend(); }

   MapIterator<K, V> find(const K & key);
   V & operator [] (const K & key);

private:
   int numItems;
   BST < Pair < K, V > > bst;
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
template <class K, class V>
Map <K, V> Map <K, V> :: operator = (const Map <K, V> & rhs) throw (const char *)
{
   this->bst = rhs.bst;
   this->numItems = rhs.numItems;
   return *this;
}

/******************************************************************
* MAP :: FIND
*******************************************************************/
template<class K, class V>
inline MapIterator<K, V> Map<K, V>::find(const K & key)
{
   Pair<K, V> searchKey(key, V());
   BSTIterator< Pair < K, V > > found = bst.find(searchKey);
   if (found == bst.end()) // We didn't find the value...
   {
      bst.insert(searchKey); // Add this new node
      found = bst.find(searchKey); // Now we should find it and can return it
   }
   return found;
}

/*******************************************************************
* MAP :: INDEX OF
********************************************************************/
template<class K, class V>
inline V & Map<K, V>::operator[](const K & key)
{
   return *(find(key));
}

#endif //MAP_H
