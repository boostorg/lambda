// Boost Lambda Library  lambda_functor_base.hpp -----------------------------
//
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
// For more information, see www.boost.org

// ------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_HPP
#define BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_HPP

namespace boost { 
namespace lambda {

namespace detail {   

// In a call make_rvalues_const<T>::exec(x)
// x should be of type T. If T is a non-reference type, exec
// returns x as const reference. 
// Otherwise the type doesn't change.
// The purpose of this class is to avoid 
// 'cannot bind temporaries to non-const references' errors.
template <class T> struct make_rvalues_const {
  template<class U>
  static const U& exec(const U& u) { return u; }
};

template <class T> struct make_rvalues_const<T&> {
  template<class U>
  static U& exec(U& u) { return u; }
};

template <int N, class Args, class A, class B, class C>
struct nth_return_type {
  typedef typename
     return_type<
       typename tuple_element_as_reference<N, Args>::type, 
       open_args<A, B, C>
     >::type type;
};
   
   
} // end detail
   
 // -- lambda_functor base ---------------------

// the explicit_return_type_action case -----------------------------------
template<class RET, class Args>
class lambda_functor_base<action<1, explicit_return_type_action<RET> >, Args> 
{
  Args args;
public:

  typedef RET result_type;

  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET_, class A, class B, class C>
  RET call(A& a, B& b, C& c) const 
  // TODO: RET and RET_ should be the same type, add a compile time assert?
  {
     return detail::make_rvalues_const<RET>::exec(
              detail::ret_selector<RET>::select(boost::tuples::get<0>(args), a, b, c));
  }
};

// the protect_action case -----------------------------------
template<class Args>
class lambda_functor_base<action<1, protect_action >, Args>
{
  Args args;
public:

  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const 
  {
     return boost::tuples::get<0>(args);
  }
};


#if defined BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART
#error "Multiple defines of BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART"
#endif

#define BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(ARITY) \
template<class Act, class Args>\
class lambda_functor_base<action<ARITY, Act>, Args> \
{\
  Args args;\
public:\
\
  explicit lambda_functor_base(const Args& a) : args(a) {}\
\
  template<class RET, class A, class B, class C>\
  RET call(A& a, B& b, C& c) const {\
\
   
BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(0)
    return Act::template apply<RET>(
    ); 
  }
};


BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(1)

     typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c))
    );
  }
};


BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(2)

    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1; 

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)),
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(3)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1; 
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2;

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(4)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0; 
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(5)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(6)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 
    typedef typename detail::nth_return_type<5, Args, A&, B&, C&>::type ret5;

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)),
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c)), 
      detail::make_rvalues_const<ret5>::exec(detail::ret_selector<ret5>::select(boost::tuples::get<5>(args), a, b, c)) 
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(7)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 
    typedef typename detail::nth_return_type<5, Args, A&, B&, C&>::type ret5;
    typedef typename detail::nth_return_type<6, Args, A&, B&, C&>::type ret6; 

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c)), 
      detail::make_rvalues_const<ret5>::exec(detail::ret_selector<ret5>::select(boost::tuples::get<5>(args), a, b, c)), 
      detail::make_rvalues_const<ret6>::exec(detail::ret_selector<ret6>::select(boost::tuples::get<6>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(8)
    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 
    typedef typename detail::nth_return_type<5, Args, A&, B&, C&>::type ret5;
    typedef typename detail::nth_return_type<6, Args, A&, B&, C&>::type ret6; 
    typedef typename detail::nth_return_type<7, Args, A&, B&, C&>::type ret7;

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c)), 
      detail::make_rvalues_const<ret5>::exec(detail::ret_selector<ret5>::select(boost::tuples::get<5>(args), a, b, c)),
      detail::make_rvalues_const<ret6>::exec(detail::ret_selector<ret6>::select(boost::tuples::get<6>(args), a, b, c)),
      detail::make_rvalues_const<ret7>::exec(detail::ret_selector<ret7>::select(boost::tuples::get<7>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(9)

    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 
    typedef typename detail::nth_return_type<5, Args, A&, B&, C&>::type ret5;
    typedef typename detail::nth_return_type<6, Args, A&, B&, C&>::type ret6; 
    typedef typename detail::nth_return_type<7, Args, A&, B&, C&>::type ret7;
    typedef typename detail::nth_return_type<8, Args, A&, B&, C&>::type ret8; 

    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c)), 
      detail::make_rvalues_const<ret5>::exec(detail::ret_selector<ret5>::select(boost::tuples::get<5>(args), a, b, c)), 
      detail::make_rvalues_const<ret6>::exec(detail::ret_selector<ret6>::select(boost::tuples::get<6>(args), a, b, c)),
      detail::make_rvalues_const<ret7>::exec(detail::ret_selector<ret7>::select(boost::tuples::get<7>(args), a, b, c)), 
      detail::make_rvalues_const<ret8>::exec(detail::ret_selector<ret8>::select(boost::tuples::get<8>(args), a, b, c))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(10) 

    typedef typename detail::nth_return_type<0, Args, A&, B&, C&>::type ret0;
    typedef typename detail::nth_return_type<1, Args, A&, B&, C&>::type ret1;
    typedef typename detail::nth_return_type<2, Args, A&, B&, C&>::type ret2; 
    typedef typename detail::nth_return_type<3, Args, A&, B&, C&>::type ret3;
    typedef typename detail::nth_return_type<4, Args, A&, B&, C&>::type ret4; 
    typedef typename detail::nth_return_type<5, Args, A&, B&, C&>::type ret5;
    typedef typename detail::nth_return_type<6, Args, A&, B&, C&>::type ret6; 
    typedef typename detail::nth_return_type<7, Args, A&, B&, C&>::type ret7;
    typedef typename detail::nth_return_type<8, Args, A&, B&, C&>::type ret8; 
    typedef typename detail::nth_return_type<9, Args, A&, B&, C&>::type ret9;


    return Act::template apply<RET>(
      detail::make_rvalues_const<ret0>::exec(detail::ret_selector<ret0>::select(boost::tuples::get<0>(args), a, b, c)), 
      detail::make_rvalues_const<ret1>::exec(detail::ret_selector<ret1>::select(boost::tuples::get<1>(args), a, b, c)), 
      detail::make_rvalues_const<ret2>::exec(detail::ret_selector<ret2>::select(boost::tuples::get<2>(args), a, b, c)), 
      detail::make_rvalues_const<ret3>::exec(detail::ret_selector<ret3>::select(boost::tuples::get<3>(args), a, b, c)), 
      detail::make_rvalues_const<ret4>::exec(detail::ret_selector<ret4>::select(boost::tuples::get<4>(args), a, b, c)), 
      detail::make_rvalues_const<ret5>::exec(detail::ret_selector<ret5>::select(boost::tuples::get<5>(args), a, b, c)), 
      detail::make_rvalues_const<ret6>::exec(detail::ret_selector<ret6>::select(boost::tuples::get<6>(args), a, b, c)),
      detail::make_rvalues_const<ret7>::exec(detail::ret_selector<ret7>::select(boost::tuples::get<7>(args), a, b, c)), 
      detail::make_rvalues_const<ret8>::exec(detail::ret_selector<ret8>::select(boost::tuples::get<8>(args), a, b, c)), 
      detail::make_rvalues_const<ret9>::exec(detail::ret_selector<ret9>::select(boost::tuples::get<9>(args), a, b, c)) 
    );
  }
};

#undef BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART


} // namespace lambda
} // namespace boost

#endif
