//  constructor_tests.cpp  --------------------------------

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"


#include "boost/lambda/lambda.hpp"

#include "boost/lambda/casts.hpp"

#include <string>

using namespace boost::lambda;
using namespace std;

class base {
  int x;
public:
  virtual std::string class_name() const { return "const base"; }
  virtual std::string class_name() { return "base"; }

};

class derived : public base {
public:
  virtual std::string class_name() const { return "const derived"; }
  virtual std::string class_name() { return "derived"; }
};




int do_test() {

  derived *p_derived = new derived;
  base *p_base = new base;

  base *b = 0;
  derived *d = 0;

  (var(b) = ll_static_cast<base *>(p_derived))();
  (var(d) = ll_static_cast<derived *>(b))();
  
  BOOST_TEST(b->class_name() == "derived");
  BOOST_TEST(d->class_name() == "derived");

  (var(b) = ll_dynamic_cast<derived *>(b))();
  BOOST_TEST(b != 0);
  BOOST_TEST(b->class_name() == "derived");

  (var(d) = ll_dynamic_cast<derived *>(p_base))();
  BOOST_TEST(d == 0);

  

  const derived* p_const_derived = p_derived;

  BOOST_TEST(p_const_derived->class_name() == "const derived");
  (var(d) = ll_const_cast<derived *>(p_const_derived))();
  BOOST_TEST(d->class_name() == "derived");

  int i = 10;
  char* cp = reinterpret_cast<char*>(&i);

  int* ip;
  (var(ip) = ll_reinterpret_cast<int *>(cp))();
  BOOST_TEST(*ip == 10);

  BOOST_TEST(string(ll_typeid(d)().name()) == string(typeid(d).name()));

 
  delete p_derived;
  delete p_base;

}

int test_main(int, char *[]) {

  do_test();
  return 0;
}
