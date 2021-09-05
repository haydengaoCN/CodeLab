#pragma once

template <class T>
struct singleton_default {
 private:
  singleton_default() = delete;
  singleton_default(const singleton_default&) = delete;
  
 public:
  static T& Instance() {
    static T obj;
    return obj; 
  }
};