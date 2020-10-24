#ifndef POOL_H
#define POOL_H

#include "Common.h"

class Poolable {
  public:
    //virtual void init();
    //virtual void deinit();

    void setNext(Poolable* next) { 
      _next = next; 
    }

    Poolable* getNext() { 
      return _next; 
    }

  private:
    Poolable* _next;
};

template <class T, int N>
class Pool {
  public:
    Pool() 
    {
      for (int i = 0; i < (N - 1); i++) {
        _pool[i].setNext(&_pool[i + 1]);
      }
      _head = &_pool[0];
      _pool[N - 1].setNext(NULL);
    }

    virtual ~Pool() {}

    T& newItem()
    {
      if (!_head) {
        while(1);
      }
      T& item = *_head;
      _head = static_cast<T*>(item.getNext());
      item.setNext(NULL);
      //item.init();
      return item;
    }

    void deleteItem(T& item)
    {
      //item.deinit();
      item.setNext(_head);
      _head = &item;
    }

    void clear() {}

  protected:
    T _pool[N];
    T* _head;
};

#endif
