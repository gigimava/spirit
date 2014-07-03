/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "uint.hpp"

int
main()
{
    using spirit_test::test;
    using spirit_test::test_attr;

    ///////////////////////////////////////////////////////////////////////////
    //  unsigned integer tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::qi::int_parser;
        unsigned n;

        BOOST_TEST(test("123456", int_parser<unsigned>()));
        BOOST_TEST(test_attr("123456", int_parser<unsigned>(), n));
        BOOST_TEST(n == 123456);

        BOOST_TEST(test("+123456", int_parser<unsigned>()));
        BOOST_TEST(test_attr("+123456", int_parser<unsigned>(), n));
        BOOST_TEST(n == 123456);

        BOOST_TEST(!test("-123456", int_parser<unsigned>()));
        BOOST_TEST(!test_attr("-123456", int_parser<unsigned>(), n));

        BOOST_TEST(test(max_int, int_parser<unsigned>()));
        BOOST_TEST(test_attr(max_int, int_parser<unsigned>(), n));
        BOOST_TEST(n == INT_MAX);

        BOOST_TEST(test(int_overflow, int_parser<unsigned>()));
        BOOST_TEST(test_attr(int_overflow, int_parser<unsigned>(), n));
        BOOST_TEST(n == INT_MAX + 1);

        BOOST_TEST(test(max_unsigned, int_parser<unsigned>()));
        BOOST_TEST(test_attr(max_unsigned, int_parser<unsigned>(), n));
        BOOST_TEST(n == UINT_MAX);
				
				BOOST_TEST(!test(unsigned_overflow, int_parser<unsigned>()));
        BOOST_TEST(!test_attr(unsigned_overflow, int_parser<unsigned>(), n));

        BOOST_TEST(!test("-", int_parser<unsigned>()));
        BOOST_TEST(!test_attr("-", int_parser<unsigned>(), n));

        BOOST_TEST(!test("+", int_parser<unsigned>()));
        BOOST_TEST(!test_attr("+", int_parser<unsigned>(), n));
        
        BOOST_TEST(test("-0", int_parser<unsigned>()));
        BOOST_TEST(test_attr("-0", int_parser<unsigned>(), n));
        BOOST_TEST(n == 0);

        // Bug report from Steve Nutt
        BOOST_TEST(!test_attr("5368709120", int_parser<unsigned>(), n));

        // with leading zeros
        BOOST_TEST(test("0000000000123456", int_parser<unsigned>()));
        BOOST_TEST(test_attr("0000000000123456", int_parser<unsigned>(), n));
        BOOST_TEST(n == 123456);
    }

    ///////////////////////////////////////////////////////////////////////////
    //  short_ and long_ tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::qi::int_parser;
        unsigned n;

        BOOST_TEST(test("12345", int_parser<unsigned short>()));
        BOOST_TEST(test_attr("12345", int_parser<unsigned short>(), n));
        BOOST_TEST(n == 12345);

        BOOST_TEST(test("1234567890", int_parser<unsigned long>()));
        BOOST_TEST(test_attr("1234567890", int_parser<unsigned long>(), n));
        BOOST_TEST(n == 1234567890);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Check overflow is parse error
    ///////////////////////////////////////////////////////////////////////////
    {
        boost::spirit::qi::int_parser<boost::uint8_t> uint8_;
        boost::uint8_t n;

        BOOST_TEST(!test_attr("999", uint8_, n));

				using boost::spirit::qi::int_parser;
        unsigned i;
        BOOST_TEST(!test_attr("65536", int_parser<unsigned short>(), i, false));
        BOOST_TEST(!test_attr("80000", int_parser<unsigned short>(), i, false));
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //  action tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::phoenix::ref;
        using boost::spirit::_1;
        using boost::spirit::ascii::space;
        using boost::spirit::qi::int_parser;
        int n, m;

        BOOST_TEST(test("123", int_parser<unsigned>()[ref(n) = _1]));
        BOOST_TEST(n == 123);
        BOOST_TEST(test_attr("789", int_parser<unsigned>()[ref(n) = _1], m));
        BOOST_TEST(n == 789 && m == 789);
        BOOST_TEST(test("   456", int_parser<unsigned>()[ref(n) = _1], space));
        BOOST_TEST(n == 456);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //  custom uint tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::qi::int_parser;
        custom_uint i;

        BOOST_TEST(test_attr("123456", int_parser<unsigned>(), i));
        BOOST_TEST(!test_attr("-123456", int_parser<unsigned>(), i));
        int_parser<custom_uint, 10, 1, 2> int2;
        BOOST_TEST(test_attr("12", int2, i));
    }

    return boost::report_errors();
}
