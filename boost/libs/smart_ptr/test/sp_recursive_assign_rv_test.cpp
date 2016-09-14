//
//  sp_recursive_assign_rv_test.cpp
//
//  Copyright 2009 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//


#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>

//

class X
{
public:

    static int instances;

    X()
    {
        ++instances;
    }

    ~X()
    {
        --instances;
    }

private:

    X( X const& );
};

int X::instances = 0;

class Y
{
public:

    static int instances;

    Y()
    {
        ++instances;
    }

    ~Y()
    {
        --instances;
    }

private:

    Y( Y const& );
};

int Y::instances = 0;

static boost::shared_ptr<void> s_pv;

class Z
{
public:

    static int instances;

    Z()
    {
        ++instances;
    }

    ~Z()
    {
        --instances;
        s_pv = boost::shared_ptr<void>( new Y );
    }

private:

    Z( Z const& );
};

int Z::instances = 0;

int main()
{
    BOOST_TEST( X::instances == 0 );
    BOOST_TEST( Y::instances == 0 );
    BOOST_TEST( Z::instances == 0 );

    s_pv = boost::shared_ptr<void>( new Z );

    BOOST_TEST( X::instances == 0 );
    BOOST_TEST( Y::instances == 0 );
    BOOST_TEST( Z::instances == 1 );

    s_pv = boost::shared_ptr<void>( new X );

    BOOST_TEST( X::instances == 0 );
    BOOST_TEST( Y::instances == 1 );
    BOOST_TEST( Z::instances == 0 );

    s_pv = boost::shared_ptr<void>();

    BOOST_TEST( X::instances == 0 );
    BOOST_TEST( Y::instances == 0 );
    BOOST_TEST( Z::instances == 0 );

    return boost::report_errors();
}
