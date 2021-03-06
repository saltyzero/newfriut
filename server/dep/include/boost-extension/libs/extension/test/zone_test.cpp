/* (C) Copyright Jeremy Pack 2007
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/extension/factory_map.hpp>
#include <boost/extension/factory.hpp>
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "fruit.hpp"
using namespace boost::extensions;

BOOST_AUTO_TEST_CASE(add_one)
{
  factory_map z;
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(0));
  z.add<apple, fruit, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(1));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(0));

}
BOOST_AUTO_TEST_CASE(add_multiple)
{
  factory_map z;
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(0));
  z.add<apple, fruit, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(1));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(0));
  z.add<banana, fruit, std::string, int, int>("A fruit that is not round");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(2));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(0));
  z.add<apple, apple, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(2));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(1));
}
BOOST_AUTO_TEST_CASE(readd)
{
  factory_map z;
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(0));
  z.add<apple, fruit, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(1));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(0));
  z.add<apple, fruit, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(2));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(0));
  z.add<apple, apple, std::string, int, int>("A round fruit");
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(2));
  BOOST_CHECK_EQUAL((z.get<apple, std::string, int, int>().size()), size_t(1));
  
}
BOOST_AUTO_TEST_CASE(different_base)
{
  factory_map z;
  BOOST_CHECK_EQUAL((z.get<vegetable, vegetable_info, float>().size()), size_t(0));
  z.add<apple, fruit, std::string, int, int>("A round fruit");
  z.add<tomato, fruit, std::string, int, int>("A round fruit that isn't very sweet");
  z.add<tomato, vegetable, vegetable_info, float>(vegetable_info("Tomato", 112));
  BOOST_CHECK_EQUAL((z.get<fruit, std::string, int, int>().size()), size_t(2));
  BOOST_CHECK_EQUAL((z.get<vegetable, vegetable_info, float>().size()), size_t(1));
  BOOST_CHECK_EQUAL((z.get<vegetable, vegetable_info, float>().begin()->get_info().get_calories()),
                    112);
}

