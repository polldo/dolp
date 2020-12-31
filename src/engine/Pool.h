#ifndef POOL_H
#define POOL_H

#include "Common.h"

class Poolable {
  public:
    //virtual void init();
    //virtual void deinit();

    void setNext(Poolable* next) 
    { 
      _next = next; 
    }

    Poolable* getNext() 
    { 
      return _next; 
    }

    void setAllocated(bool isAllocated)
    {
      _isAllocated = isAllocated;
    }

    bool isAllocated() 
    {
      return _isAllocated;
    }

  private:
    Poolable* _next;
    bool _isAllocated;

#if defined (POOL_DOUBLE_LINK)
  public:
    void setPrev(Poolable* prev) 
    { 
      _prev = prev; 
    }

    Poolable* getPrev() 
    { 
      return _prev; 
    }

  private:
    Poolable* _prev;
#endif
};

template <class T, int N>
class Pool {
  public:

    Pool() 
    {
      // Put all the items in the free list
      for (int i = 0; i < (N - 1); i++) {
        _pool[i].setNext(&_pool[i + 1]);
        _pool[i].setAllocated(false);
      }
      _headFree = &_pool[0];
      _pool[N - 1].setNext(NULL);
#if defined (POOL_DOUBLE_LINK)
      // Allocated list is empty
      _headAllocated = NULL;
#endif
    }

    virtual ~Pool() {}

    T& newItem()
    {
      // TODO: check if the pool is full
      //if (!_headFree) {
        //while(1);
      //}

      // Remove from the free list
      T& item = *_headFree;
      _headFree = static_cast<T*>(item.getNext());
      //item.setNext(NULL);
#if defined (POOL_DOUBLE_LINK)
      // Add to the allocated list
      item.setNext(_headAllocated);
      item.setPrev(NULL);
      if (_headAllocated) _headAllocated->setPrev(&item);
      _headAllocated = &item;
#endif
      item.setAllocated(true);
      //item.init()
      return item;
    }

    void deleteItem(T& item)
    {
      // TODO: check if the item is already in the free list
      //if (!item.isAllocated()) return;
      item.setAllocated(false);
      // Remove from the allocated list
#if defined (POOL_DOUBLE_LINK)
      if (item.getPrev()) {
        item.getPrev()->setNext(item.getNext());
      } else {
        _headAllocated = static_cast<T*>(item.getNext());
      }
      if (item.getNext()) {
        item.getNext()->setPrev(item.getPrev());
      }
#endif
      // Add to the free list
      item.setNext(_headFree);
      _headFree = &item;
    }

    void clear() {}

#if defined (POOL_DOUBLE_LINK)
    T* getItems()
    {
      return _headAllocated;
    }
#endif

  protected:
    T _pool[N];
    T* _headFree;
#if defined (POOL_DOUBLE_LINK)
    T* _headAllocated;
#endif
};

#endif
