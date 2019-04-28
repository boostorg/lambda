# Copyright 2019 Sam Day
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.lambda is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)
project(BoostLambda LANGUAGES CXX)

add_library(boost_lambda INTERFACE)
add_library(Boost::lambda ALIAS boost_lambda)

target_include_directories(boost_lambda INTERFACE include)

target_link_libraries(boost_lambda
        INTERFACE
        Boost::bind
        Boost::config
        Boost::detail
        Boost::iterator
        Boost::mpl
        Boost::preprocessor
        Boost::tuple
        Boost::type_traits
        Boost::utility
        )
