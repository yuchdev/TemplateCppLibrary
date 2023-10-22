#include <pe/pe.h>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(GeneralHelpersFunctionalTests);

BOOST_AUTO_TEST_CASE(TestWindowsErrorStringThrow)
{
    std::string last_error {"Access is denied."};
    std::string error_description{ "Access is denied." };
    BOOST_CHECK_EQUAL(last_error, error_description);
}

BOOST_AUTO_TEST_SUITE_END()
