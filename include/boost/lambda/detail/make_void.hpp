// -- Boost Lambda Library -- exceptions.hpp ----------------
//
// Copyright (C) 2000 Gary Powell (gwpowell@hotmail.com)
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

// -----------------------------------------------------

// make_void( x ) turns a lambda functor x with some return type y into
// another lambda functor, which has a void return type
// when called, the original return type is discarded

#if !defined(BOOST_LAMBDA_MAKE_VOID_HPP)
#define BOOST_LAMBDA_MAKE_VOID_HPP

namespace boost { 
namespace lambda {

template<> struct return_void_action<other_action<identity_action> > {
  template<class RET, class A>
  RET static apply(A& a) { a; }
};


template<class Arg1>
inline const 
lambda_functor<
  lambda_functor_args<
    action<1, return_void_action<other_action<identity_action> > >,
    tuple<lambda_functor<Arg1> >,
   combine_arities<Arg1>::value 
  > 
> 
make_void(const lambda_functor<Arg1>& a1) { 
return 
  lambda_functor<
    lambda_functor_args<
      action<1, return_void_action<other_action<identity_action> > >,
      tuple<lambda_functor<Arg1> >,
      combine_arities<Arg1>::value 
    > 
  > 
  (tuple<lambda_functor<Arg1> > (a1));
}


// if its already returning void don't add another layer.
template <class ActionType, class Args, int Code>
inline const lambda_functor<lambda_functor_args<action<1, return_void_action<ActionType> >,
	                 Args, Code > > 
make_void(const lambda_functor<lambda_functor_args<action<1, return_void_action<ActionType> >,
	                 Args, Code > >& a1) { 
  return lambda_functor<lambda_functor_args<action<1, return_void_action<ActionType> >,
	                 Args, Code > > 
    (a1);
}

template <class ActionType, class Args, int Code>
inline const lambda_functor<lambda_functor_args<action<2, return_void_action<ActionType> >,
	                 Args,
					 Code > > 
make_void(const lambda_functor<lambda_functor_args<action<2, return_void_action<ActionType> >,
	                 Args,
					 Code > >& a1) { 
  return lambda_functor<lambda_functor_args<action<2, return_void_action<ActionType> >,
	                 Args,
					 Code > > 
    (a1);
}

template <class ActionType, class Args, int Code>
inline const lambda_functor<lambda_functor_args<action<3, return_void_action<ActionType> >,
	                 Args, Code > > 
make_void(const lambda_functor<lambda_functor_args<action<3, return_void_action<ActionType> >,
	                 Args, Code > >& a1) { 
  return lambda_functor<lambda_functor_args<action<3, return_void_action<ActionType> >,
	                 Args, Code > > 
    (a1);
}

template <class ActionType, int N, class Args, int Code>
inline const lambda_functor<lambda_functor_args<action<N, return_void_action<ActionType> >,
	                 Args, Code > > 
make_void(const lambda_functor<lambda_functor_args<action<N, return_void_action<ActionType> >,
	                 Args,  Code > >& a1) { 
  return lambda_functor<lambda_functor_args<action<N, return_void_action<ActionType> >,
	                 Args, Code > > 
    (a1);
}

} // namespace lambda 
} // namespace boost


#endif
