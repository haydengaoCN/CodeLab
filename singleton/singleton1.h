#pragma once

template <class T>
struct singleton_default {
 private:
  struct object_creator {
    object_creator() {
      singleton_default<T>::Instance();
    }
    inline void do_nothing() const {}
  };
  static object_creator create_object;

  singleton_default() = delete;
  singleton_default(const singleton_default&) = delete;
  
 public:
  static T& Instance() {
    static T obj;

    create_object.do_nothing();

    return obj; 
  }
};

template <class T>
typename singleton_default<T>::object_creator singleton_default<T>::create_object;
