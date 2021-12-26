// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/lambda/bind.hpp>
#include <functional>

void func()
{
}

int main()
{
    std::function<void()>( boost::lambda::bind( func ) );
}
