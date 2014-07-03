/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "int.hpp"

int
main()
{
    using spirit_test::test;
    using spirit_test::test_attr;
    ///////////////////////////////////////////////////////////////////////////
    //  signed tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::qi::uint_parser;
        int i;

        BOOST_TEST(test("123456", uint_parser<int>()));
        BOOST_TEST(test_attr("123456", uint_parser<int>(), i));
        BOOST_TEST(i == 123456);

        BOOST_TEST(test(max_int, uint_parser<int>()));
        BOOST_TEST(test_attr(max_int, uint_parser<int>(), i));
        BOOST_TEST(i == INT_MAX);

        BOOST_TEST(!test(int_overflow, uint_parser<int>()));
        BOOST_TEST(!test_attr(int_overflow, uint_parser<int>(), i));
        
        BOOST_TEST(!test("-1", uint_parser<int>()));
        BOOST_TEST(!test_attr("-1", uint_parser<int>(), i));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  action tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::phoenix::ref;
        using boost::spirit::ascii::space;
        using boost::spirit::qi::uint_parser;
        using boost::spirit::qi::_1;
        int i, j;

        BOOST_TEST(test("123", uint_parser<int>()[ref(i) = _1]));
        BOOST_TEST(i == 123);

        BOOST_TEST(test_attr("789", uint_parser<int>()[ref(i) = _1], j));
        BOOST_TEST(i == 789 && j == 789);;

        BOOST_TEST(test("   456", uint_parser<int>()[ref(i) = _1], space));
        BOOST_TEST(i == 456);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Check overflow is parse error
    ///////////////////////////////////////////////////////////////////////////
    {
        boost::spirit::qi::uint_parser<boost::int8_t> int8_;
        boost::int8_t i8;

        BOOST_TEST(!test_attr("999", int8_, i8));
        BOOST_TEST(!test_attr("256", int8_, i8));
        BOOST_TEST(!test_attr("255", int8_, i8));
        BOOST_TEST(!test_attr("128", int8_, i8));
        BOOST_TEST(test_attr("127", int8_, i8));

        boost::spirit::qi::uint_parser<boost::int16_t> int16_;
        boost::int16_t i16;

        BOOST_TEST(!test_attr("99999", int16_, i16));
        BOOST_TEST(!test_attr("65536", int16_, i16));
        BOOST_TEST(!test_attr("65535", int16_, i16));
        BOOST_TEST(!test_attr("32768", int16_, i16));
        BOOST_TEST(test_attr("32767", int16_, i16));

        boost::spirit::qi::uint_parser<boost::int32_t> int32_;
        boost::int32_t i32;

        BOOST_TEST(!test_attr("9999999999", int32_, i32));
        BOOST_TEST(!test_attr("4294967296", int32_, i32));
        BOOST_TEST(!test_attr("4294967295", int32_, i32));
        BOOST_TEST(!test_attr("2147483648", int32_, i32));
        BOOST_TEST(test_attr("2147483647", int32_, i32));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  custom uint tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::qi::uint_parser;
        custom_int i;

        BOOST_TEST(test_attr("123456", uint_parser<int>(), i));
        uint_parser<custom_int, 10, 1, 2> uint2;
        BOOST_TEST(test_attr("12", uint2, i));
    }    

    return boost::report_errors();
}
