// - construct.hpp -- Lambda Library -------------
//
// Copyright (C) 2000 Gary Powell (gary.powell@sierra.com)
// Copyright (C) 1999, 2000 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//
// For more information, see http://www.boost.org
//
// -----------------------------------------------

#if !defined(BOOST_LAMBDA_CONSTRUCT_HPP)
#define BOOST_LAMBDA_CONSTRUCT_HPP

namespace boost { 
namespace lambda {

  // constructor is used together with bind. constructor<A> creates a bindable
  // function object that passes its arguments forward to a constructor call
  // of type A

template<class T> struct constructor {

  typedef T result_type;

  T operator()() const {
    return T();
  }

  template<class A1>
  T operator()(A1& a1) const {
    return T(a1);
  }

  template<class A1, class A2>
  T operator()(A1& a1, A2& a2) const {
    return T(a1, a2);
  }

  template<class A1, class A2, class A3>
  T operator()(A1& a1, A2& a2, A3& a3) const {
    return T(a1, a2, a3);
  }

  template<class A1, class A2, class A3, class A4>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return T(a1, a2, a3, a4);
  }

  template<class A1, class A2, class A3, class A4, class A5>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return T(a1, a2, a3, a4, a5);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return T(a1, a2, a3, a4, a5, a6);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return T(a1, a2, a3, a4, a5, a6, a7);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }

};


// destructor funtion object
struct destructor {  

   typedef void result_type;
  
  template<class A1>
  void operator()(A1& a1) const {
     a1.operator~();
  }

  template<class A1>
  void operator()(A1* a1) const {
     a1->~A1();
  }
};



// new_ptr is used together with bind.

  // note: placement new is not supported

template<class T> struct new_ptr {

  typedef T* result_type;

  T* operator()() const {
    return new T();
  }

  template<class A1>
  T* operator()(A1& a1) const {
    return new T(a1);
  }

  template<class A1, class A2>
  T* operator()(A1& a1, A2& a2) const {
    return new T(a1, a2);
  }

  template<class A1, class A2, class A3>
  T* operator()(A1& a1, A2& a2, A3& a3) const {
    return new T(a1, a2, a3);
  }

  template<class A1, class A2, class A3, class A4>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return new T(a1, a2, a3, a4);
  }

  template<class A1, class A2, class A3, class A4, class A5>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return new T(a1, a2, a3, a4, a5);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return new T(a1, a2, a3, a4, a5, a6);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return new T(a1, a2, a3, a4, a5, a6, a7);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }

};

// delete_ptr return void

struct delete_ptr {

  typedef void result_type;

  template <class A1>
  void operator()(A1& a1) const {
    delete a1;
  }

};


// new_array is used together with bind.W

template<class T> struct new_array {

  typedef T* result_type;

  T* operator()(int size) const {
    return new T[size];
  }
};


// delete_ptr return void

struct delete_array {

  typedef void result_type;

  template <class A1>
  void operator()(A1& a1) const {
    delete[] a1;
  }

};



} // namespace lambda 
} // namespace boost

#endif
