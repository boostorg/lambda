//  basic_test.cpp  --------------------------------

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#include "boost/lambda/bind.hpp"


#include <iostream>

int sum_of_args_0() { return 0; }
int sum_of_args_1(int a) { return a; }
int sum_of_args_2(int a, int b) { return a+b; }
int sum_of_args_3(int a, int b, int c) { return a+b+c; }
int sum_of_args_4(int a, int b, int c, int d) { return a+b+c+d; }
int sum_of_args_5(int a, int b, int c, int d, int e) { return a+b+c+d+e; }
int sum_of_args_6(int a, int b, int c, int d, int e, int f) { return a+b+c+d+e+f; }
int sum_of_args_7(int a, int b, int c, int d, int e, int f, int g) { return a+b+c+d+e+f+g; }
int sum_of_args_8(int a, int b, int c, int d, int e, int f, int g, int h) { return a+b+c+d+e+f+g+h; }
int sum_of_args_9(int a, int b, int c, int d, int e, int f, int g, int h, int i) { return a+b+c+d+e+f+g+h+i; }


int product_of_args_2(int a, int b) { return a*b; }

typedef int (*fptr_type)(int, int);
fptr_type sum_or_product(bool x) { 
  return x ? sum_of_args_2 : product_of_args_2; 
}

struct X {
  typedef fptr_type (*result_type)(bool x);
  result_type operator()() { return sum_or_product; }
};

// ----------------------------



struct test {
  
  typedef int result_type;
   
  template<class T1, class T2>
  int operator()(const T1& t1, const T2& t2) const {
     return t1(t2);
  }
};


int test_main(int, char *[]) {
 
  using namespace std;
  using namespace boost::tuples;
  using namespace boost::lambda;
   
  int i = 1; int j = 2; int k = 3;

// protect prevents the expansion of lambda functor
  BOOST_TEST(protect(bind(sum_of_args_1, 3))()()==3);   

  test t; 
  BOOST_TEST(bind(t, protect(bind(sum_of_args_1, _1)), 9)()==9);


// bind calls can be nested (the target function can be a lambda functor)
// The interpretation is, that the innermost lambda functor returns something
// that is bindable (another lambda functor, function pointer ...)
  bool condition;
  
  condition = true;
  BOOST_TEST(bind(bind(sum_or_product, _1), 1, 2)(condition)==3);
  BOOST_TEST(bind(bind(sum_or_product, _1), _2, _3)(condition, j, k)==5);

  condition = false;   
  BOOST_TEST(bind(bind(sum_or_product, _1), 1, 2)(condition)==2);
  BOOST_TEST(bind(bind(sum_or_product, _1), _2, _3)(condition, j, k)==6);
  X x; 
  BOOST_TEST(bind(bind(bind(boost::ref(x)), _1), _2, _3)(condition, j, k)==6);   

// lambda functor is a function object, and can therefore be used
// as an argument to another lambda functors function call object.
// However, bindable function objects must define the typdef result_type.
// ret<T> adds this to a lambda functor:

  BOOST_TEST(bind(_1)(ret<int>(bind(sum_of_args_1, 3)))==3);
   
   
  return 0;
}
