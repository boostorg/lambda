//  lambda_fwd.hpp - Boost Lambda Library -------------------------------

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

// -------------------------------------------------------

#ifndef BOOST_LAMBDA_FWD_HPP
#define BOOST_LAMBDA_FWD_HPP

namespace boost { 
namespace lambda { 

namespace detail {

template<class T> struct generate_error;

}   
// -- placeholders --------------------------------------------

template <int I> class placeholder;

// function_adaptors
template <class Func> 
struct function_adaptor;

// The return_type traits class:
template <class Action, class Open> 
class return_type;

template <int I, class Act> class action;

  //template <int I> class function_action;


template <class BinderArgs> 
struct lambda_functor;

template <class Action, 
          class Args, 
          int ArityCode>
class lambda_functor_args;

template <class Act, class Args> 
class lambda_functor_base;

} // namespace lambda
} // namespace boost


#endif
