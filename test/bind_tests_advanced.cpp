//  basic_test.cpp  --------------------------------

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#include "boost/lambda/bind.hpp"
#include "boost/lambda/lambda.hpp"

#include "boost/any.hpp"

#include <iostream>

#include <functional>

#include <algorithm>

using namespace boost::lambda; 

int sum_0() { return 0; }
int sum_1(int a) { return a; }
int sum_2(int a, int b) { return a+b; }

int product_2(int a, int b) { return a*b; }

// unary function that returns a pointer to a binary function
typedef int (*fptr_type)(int, int);
fptr_type sum_or_product(bool x) { 
  return x ? sum_2 : product_2; 
}

// a nullary functor that returns a pointer to a unary function that
// returns a pointer to a binary function.
struct which_one {
  typedef fptr_type (*result_type)(bool x);
  result_type operator()() const { return sum_or_product; }
};

void test_nested_binds()
{
  int j = 2; int k = 3;

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

  which_one wo; 
  BOOST_TEST(bind(bind(bind(wo), _1), _2, _3)(condition, j, k)==6);   

  return;
}


// unlambda -------------------------------------------------

  // Sometimes it may be necessary to prevent the argument substitution of
  // taking place. For example, we may end up with a nested bind expression 
  // inadvertently when using the target function is received as a parameter

template<class F>
int call_with_100(const F& f) {



  //  bind(f, _1)(make_const(100));
  // This would result in;
  // bind(_1 + 1, _1)(make_const(100)) , which would be a compile time error

  return bind(unlambda(f), _1)(make_const(100));

  // for other functors than lambda functors, unlambda has no effect
  // (except for making them const)
}

template<class F>
int call_with_101(const F& f) {

  return bind(unlambda(ret<int>(f)), _1)(make_const(101));

  // the ret must be inside of unlambda, since unlambda requires its argument
  // to define result_type.
  // if F is not a lambda functor ret<int>(f) fails at compile time!
}

void test_unlambda() {

  BOOST_TEST(call_with_100(ret<int>(_1 + 1)) == 101);
  // note, that the functor must define the result_type typedef, as the bind
  // int the called function does not do that.

  BOOST_TEST(call_with_101(_1 + 1) == 102);
  // This one leaves the return type to be specified by the bind in the
  // called function, and that makes things kind of hard in the called 
  // function
  
  BOOST_TEST(call_with_100(std::bind1st(std::plus<int>(), 1)) == 101);

  //  BOOST_TEST(call_with_101(std::bind1st(std::plus<int>(), 1)) == 102);
  // this would fail, as it would lead to ret being called with other than
  // a lambda functor	
}

// protect ------------------------------------------------------------

// protect protects a lambda functor from argument substitution. 
// protect is useful e.g. with nested stl algorithm calls.

namespace ll {

struct for_each : public has_sig {
  
  // note, std::for_each returns it's last argument
  // We want the same behaviour from our ll::for_each.
  // However, the functor can be called with any arguments, and
  // the return type thus depends on the argument types.
  // The basic mechanism (provide a result_type typedef) does not 
  // work.
  
  // There is an alternative for this kind of situations, which LL 
  // borrows from FC++ (by Yannis Smaragdakis and Brian McNamara).

  // If you want to use this mechanism, your function object class needs to 
  // 1. inhertit publicly from has_sig
  // 2. Provide a sig class member template:
 
  // The return type deduction system instantiate this class as:
  // sig<Args>::type, where Args is a boost::tuples::cons-list
  // The head type is the function object type itself 
  // cv-qualified (so it is possilbe to provide different return types
  // for differently cv-qualified operator()'s.

  // The tail type is the list of the types of the actual arguments the 
  // function was called with.
  // So sig should contain a typedef type, which defines a mapping from 
  // the operator() arguments to its return type.
  // Note, that it is possible to provide different sigs for the same functor
  // if the functor has several operator()'s, even if they have different 
  // number of arguments.

  // Note, that the argument types in Args can be arbitrary types, particularly
  // they can be reference types and can have qualifiers or both. 
  // So some care will be needed in this respect.
 
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<3, Args>::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C>
  C
  operator()(const A& a, const B& b, const C& c) const
  { return std::for_each(a, b, c);}
};

} // end of ll namespace

void test_protect() 
{
  int i = 0;
  int b[3][5];
  int* a[3];
  
  for(int j=0; j<3; ++j) a[j] = b[j];

  std::for_each(a, a+3, 
	   bind(ll::for_each(), _1, _1 + 5, protect(_1 = ++var(i))));

  // This is how you could output the values (it is uncommented, no output
  // from a regression test file):
  //  std::for_each(a, a+3, 
  //                bind(ll::for_each(), _1, _1 + 5,
  //                     std::cout << constant("\nLine ") << (&_1 - a) << " : "
  //		     << protect(_1)
  //		     )
  //               );

  int sum = 0;
  std::for_each(a, a+3, 
	   bind(ll::for_each(), _1, _1 + 5, 
                protect(sum += _1))
               );
  BOOST_TEST(sum = 16*16-1);

  sum = 0;
  std::for_each(a, a+3, 
	   bind(ll::for_each(), _1, _1 + 5, 
                sum += 1 + protect(_1)) // add element count 
               );
  BOOST_TEST(sum = 16*16-1 + 15);


  int k = 0; 
  ((k += constant(1)) += protect(constant(2)))();
  BOOST_TEST(k==1);

  k = 0; 
  ((k += constant(1)) += protect(constant(2)))()();
  BOOST_TEST(k==3);

  // note, the following doesn't work:

  //  ((var(k) = constant(1)) = protect(constant(2)))();

  // (var(k) = constant(1))() returns int& and thus the
  // second assignment fails.

  // We should have something like:
  // bind(var, var(k) = constant(1)) = protect(constant(2)))();
  // But currently var is not bindable.

  // The same goes with ret. A bindable ret could be handy sometimes as well
  // (protect(std::cout << _1), std::cout << _1)(i)(j); does not work
  // because the comma operator tries to store the result of the evaluation
  // of std::cout << _1 as a copy (and you can't copy std::ostream).
  // something like this:
  // (protect(std::cout << _1), bind(ref, std::cout << _1))(i)(j); 

  // But for now, ref is not bindable. There are other ways around this:

  //  int x = 1, y = 2;
  //  (protect(std::cout << _1), (std::cout << _1, 0))(x)(y);

  // added one dummy value to make the argument to comma an int 
  // instead of ostream& 

  // Note, the same problem is more apparent without protect
  //   (std::cout << 1, std::cout << constant(2))(); // does not work

  //  (boost::ref(std::cout << 1), std::cout << constant(2))(); // this does
}


void test_lambda_functors_as_arguments_to_lambda_functors() {

// lambda functor is a function object, and can therefore be used
// as an argument to another lambda functors function call object.

  // Note however, that the argument/type substitution is not entered again.
  // This means, that something like this will not work:
  (_1 + _2)(bind(sum_0), make_const(7)); 
    // or it does work, but the effect is not to call
    // sum_0() + 7, but rather
    // bind(sum_0) + 7, which results in another lambda functor
    // (lambda functor + int) and can be called again
  BOOST_TEST((_1 + _2)(bind(sum_0), make_const(7))() == 7); 
   

  // also, note that lambda functor are no special case for bind if received
  // as a parameter. In oder to be bindable, the functor must
  // either define the result_type typedef, have the sig template, or then
  // the return type must be defined within the bind call. Lambda functors
  // do define the sig template, so if the return type deduction system
  // covers the case, there is no need to specify the return type 
  // explicitly.

  int a = 5, b = 6, c = 7;

  // Let type deduction take find out the return type
  BOOST_TEST(bind(_1, _2, _3)(_1 + _2, a, b) == 11);

  //specify it yourself:
  BOOST_TEST(bind(_1, _2, _3)(ret<int>(_1 + _2), a, b) == 11);
  BOOST_TEST(ret<int>(bind(_1, _2, _3))(_1 + _2, a, b) == 11);
  BOOST_TEST(bind<int>(_1, _2, _3)(_1 + _2, a, b) == 11);


  return; 

}

void test_currying() {

  int a = 1, b = 2, c = 3;

  // lambda functors support currying:
  // binary functor can be called with just one argument, the result is
  // a unary lambda functor. 
  // 3-ary functor can be called with one or two arguments (and with 3 
  // of course)

  BOOST_TEST((_1 + _2)(a)(b) == 3);

  BOOST_TEST((_1 + _2 + _3)(a, b)(c) == 6);
  BOOST_TEST((_1 + _2 + _3)(a)(b, c) == 6);
  BOOST_TEST((_1 + _2 + _3)(a)(b)(c) == 6);

  // Also, lambda functors passed as arguments end up being curryable

  BOOST_TEST(bind(_1, _2, _3)(_1 + _2 + _3, a, b)(c) == 6);
  BOOST_TEST(bind(_1, _2)(_1 + _2 + _3, a)(b, c) == 6);
  BOOST_TEST(bind(_1, _2)(_1 + _2 + _3, a)(b)(c) == 6);

  bind(_1, _2)(_1 += (_2 + _3), a)(b)(c);
  BOOST_TEST(a == 6);

  bind(_1, _2)(a += (_1 + _2 + _3), c)(c)(c);
  BOOST_TEST(a == 6+3*c);

  a = 1, b = 2, c = 3;
  // and protecting should work as well
  BOOST_TEST(bind(_1, _2)(_1 + _2 + _3 + protect(_1), a)(b)(c)(a) == 7);
  

  return;

}

int test_main(int, char *[]) {

  test_nested_binds();
  test_unlambda();
  test_protect();
  test_lambda_functors_as_arguments_to_lambda_functors();
  test_currying(); 
  return 0;
}












