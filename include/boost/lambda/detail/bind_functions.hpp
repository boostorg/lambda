// -- bind_functions.hpp -- Boost Lambda Library
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
// For more information, see http://www.boost.org

// ----------------------------------------------------------------

#ifndef BOOST_LAMBDA_BIND_FUNCTIONS_HPP
#define BOOST_LAMBDA_BIND_FUNCTIONS_HPP


namespace boost { 
namespace lambda {

#ifdef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING

  // gcc 2.96 instantiates bind functions it does not even call.
  // These instantiations lead to incorrect types in the return type, 
  // and a compilation error results. 
  // This tweaking is to prevent the formation of the erroneous type.
namespace detail {

template<class T> struct constify_non_funcs {
  typedef typename 
  detail::IF_type<boost::is_function<T>::value,
    boost::add_reference<T>,
    boost::add_const<T>
  >::type type;
};

}
#endif
// 1-argument bind functions --------------------------
template <class Result>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<Result(&)()>::type,
    combine_arities<>::value
  >
>
bind(Result(&a1)()) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1, Result> >,
        typename detail::bind_tuple_mapper<Result(&)()>::type,
        combine_arities<>::value
      >
    >
    ( typename detail::bind_tuple_mapper<Result(&)()>::type
      (a1)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1> >,
    typename detail::bind_tuple_mapper<const Arg1>::type,
    combine_arities<Arg1>::value
  >
>
bind(const Arg1& a1) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1> >,
        typename detail::bind_tuple_mapper<const Arg1>::type,
        combine_arities<Arg1>::value
      >
    >
    ( typename detail::bind_tuple_mapper<const Arg1>::type
      (a1)
    );
}

template <class Result, class Arg1>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<const Arg1>::type,
    combine_arities<Arg1>::value
  >
>
bind(const Arg1& a1) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1, Result> >,
        typename detail::bind_tuple_mapper<const Arg1>::type,
        combine_arities<Arg1>::value
      >
    >
    ( typename detail::bind_tuple_mapper<const Arg1>::type
      (a1)
    );
}


 #else 
template <class Arg1>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type
    >::type,
    combine_arities<Arg1>::value
  >
>
bind(const Arg1& a1) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type
        >::type,
        combine_arities<Arg1>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
      (a1)
    );
}

template <class Result, class Arg1>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type
    >::type,
    combine_arities<Arg1>::value
  >
>
bind(const Arg1& a1) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type
        >::type,
        combine_arities<Arg1>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
      (a1)
    );
}

template <class Result>
inline const
lambda_functor<
  lambda_functor_args<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<Result(*)()>::type,
    combine_arities<>::value
  >
>
bind(Result(* const & a1)()) {
  return
    lambda_functor<
      lambda_functor_args<
        action<1, function_action<1, Result> >,
        typename detail::bind_tuple_mapper<Result(*)()>::type,
        combine_arities<>::value
      >
    >
    ( typename detail::bind_tuple_mapper<Result(*)()>::type
      (a1)
    );
}


 #endif 

// 2-argument bind functions --------------------------
template <class Result, class Par1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type,
    combine_arities<Arg2>::value
  >
>
bind(Result(&a1)(Par1), const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2, Result> >,
        typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type,
        combine_arities<Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type
      (a1, a2)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2> >,
    typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type,
    combine_arities<Arg1, Arg2>::value
  >
>
bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2> >,
        typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type,
        combine_arities<Arg1, Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
      (a1, a2)
    );
}

template <class Result, class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type,
    combine_arities<Arg1, Arg2>::value
  >
>
bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2, Result> >,
        typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type,
        combine_arities<Arg1, Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
      (a1, a2)
    );
}


 #else 
template <class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2
    >::type,
    combine_arities<Arg1, Arg2>::value
  >
>
bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2
        >::type,
        combine_arities<Arg1, Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
      (a1, a2)
    );
}

template <class Result, class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2
    >::type,
    combine_arities<Arg1, Arg2>::value
  >
>
bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2
        >::type,
        combine_arities<Arg1, Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
      (a1, a2)
    );
}

template <class Result, class Par1, class Arg2>
inline const
lambda_functor<
  lambda_functor_args<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type,
    combine_arities<Arg2>::value
  >
>
bind(Result(* const & a1)(Par1), const Arg2& a2) {
  return
    lambda_functor<
      lambda_functor_args<
        action<2, function_action<2, Result> >,
        typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type,
        combine_arities<Arg2>::value
      >
    >
    ( typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type
      (a1, a2)
    );
}


 #endif 

// 3-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2), const Arg2, const Arg3
    >::type,
    combine_arities<Arg2, Arg3>::value
  >
>
bind(Result(&a1)(Par1, Par2), const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2), const Arg2, const Arg3
        >::type,
        combine_arities<Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2), const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3
    >::type,
    combine_arities<Arg1, Arg2, Arg3>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3
        >::type,
        combine_arities<Arg1, Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3
    >::type,
    combine_arities<Arg1, Arg2, Arg3>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3
        >::type,
        combine_arities<Arg1, Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3
    >::type,
    combine_arities<Arg1, Arg2, Arg3>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3
        >::type,
        combine_arities<Arg1, Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3
    >::type,
    combine_arities<Arg1, Arg2, Arg3>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3
        >::type,
        combine_arities<Arg1, Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Par1, class Par2, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_args<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2), const Arg2, const Arg3
    >::type,
    combine_arities<Arg2, Arg3>::value
  >
>
bind(Result(* const & a1)(Par1, Par2), const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor<
      lambda_functor_args<
        action<3, function_action<3, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2), const Arg2, const Arg3
        >::type,
        combine_arities<Arg2, Arg3>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2), const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}


 #endif 

// 4-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Arg2,
          class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
    >::type,
    combine_arities<Arg2, Arg3, Arg4>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3), const Arg2& a2, const Arg3& a3,
     const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
        >::type,
        combine_arities<Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Arg2,
          class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_args<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
    >::type,
    combine_arities<Arg2, Arg3, Arg4>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3), const Arg2& a2,
     const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor<
      lambda_functor_args<
        action<4, function_action<4, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
        >::type,
        combine_arities<Arg2, Arg3, Arg4>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}


 #endif 

// 5-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
      const Arg5
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4), const Arg2& a2, const Arg3& a3,
     const Arg4& a4, const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3,
          const Arg4, const Arg5
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_args<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
      const Arg5
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5) {
  return
    lambda_functor<
      lambda_functor_args<
        action<5, function_action<5, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3,
          const Arg4, const Arg5
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}


 #endif 

// 6-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
          const Arg4, const Arg5, const Arg6
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_args<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor<
      lambda_functor_args<
        action<6, function_action<6, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
          const Arg4, const Arg5, const Arg6
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}


 #endif 

// 7-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6,
     const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_args<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor<
      lambda_functor_args<
        action<7, function_action<7, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}


 #endif 

// 8-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Arg2, class Arg3,
          class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6,
     const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type,
    combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8
        >::type,
        combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Arg2, class Arg3,
          class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_args<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor<
      lambda_functor_args<
        action<8, function_action<8, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}


 #endif 

// 9-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Arg2,
          class Arg3, class Arg4, class Arg5, class Arg6, class Arg7,
          class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8,
      const Arg9
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
          const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
          const Arg7, const Arg8, const Arg9
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8, const Arg9
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8, const Arg9
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8, const Arg9
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8, const Arg9
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Arg2,
          class Arg3, class Arg4, class Arg5, class Arg6, class Arg7,
          class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_args<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8,
      const Arg9
    >::type,
    combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9) {
  return
    lambda_functor<
      lambda_functor_args<
        action<9, function_action<9, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
          const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
          const Arg7, const Arg8, const Arg9
        >::type,
        combine_arities<Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}


 #endif 

// 10-argument bind functions --------------------------
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Par9,
          class Arg2, class Arg3, class Arg4, class Arg5, class Arg6,
          class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
      const Arg2, const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
      const Arg8, const Arg9, const Arg10
    >::type,
    combine_arities<
      Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9,
     const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10, Result> >,
        typename detail::bind_tuple_mapper<
          Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
          const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
          const Arg7, const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}


 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9, const Arg10
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9,
          class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9, const Arg10
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10, Result> >,
        typename detail::bind_tuple_mapper<
          const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
          const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9,
      const Arg10
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9,
          class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9,
      const Arg10
    >::type,
    combine_arities<
      Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10, Result> >,
        typename detail::bind_tuple_mapper<
          typename detail::constify_non_funcs<Arg1>::type, const Arg2,
          const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
          const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Par9,
          class Arg2, class Arg3, class Arg4, class Arg5, class Arg6,
          class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_args<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
      const Arg2, const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
      const Arg8, const Arg9, const Arg10
    >::type,
    combine_arities<
      Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
    >::value
  >
>
bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8,
     Par9), const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9,
     const Arg10& a10) {
  return
    lambda_functor<
      lambda_functor_args<
        action<10, function_action<10, Result> >,
        typename detail::bind_tuple_mapper<
          Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
          const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
          const Arg7, const Arg8, const Arg9, const Arg10
        >::type,
        combine_arities<
          Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10
        >::value
      >
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}


 #endif 

} // namespace lambda 
} // namespace boost

#endif
