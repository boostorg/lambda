// -- algorithms.hpp -- Boost Lambda Library -----------------------------------
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

#ifndef BOOST_LAMBDA_ALGORITHMS_HPP
#define BOOST_LAMBDA_ALGORITHMS_HPP

#include "boost/lambda/core.hpp"

#include <algorithm>

namespace boost {
  namespace lambda {

namespace ll {

// for_each ---------------------------------

struct for_each : public has_sig {
  
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
  operator()(A a, B b, C c) const
  { return ::std::for_each(a, b, c);}
};

// transform --------------------------------

struct transform : public has_sig {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
      typename boost::remove_reference<
        typename boost::tuples::element<
          boost::tuples::length<Args>::value - 1, 
          Args
        >::type 
      >::type
     >::type type; 
  };

  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return std::transform(a, b, c, d);}

  template <class A, class B, class C, class D, class E>
  D
  operator()(A a,  B b,  C c,  D d,  E e)
  { return std::transform(a, b, c, d, e);}

};


} // end of ll namespace

} // end of lambda namespace
} // end of boost namespace



#endif
