#include "../code/service.h"
#include "gtest/gtest.h" // Google Test Framework, must be included in the test file.

// Test fixture for the Service class.
TEST(compare_IDTest, checkIDEqualityEqualToArgument) {
    Service a_service(000111, "test_service", 10.0);
    EXPECT_EQ(a_service.compare_ID(000111), 0) << "ID not equal.";
}

TEST(compare_IDTest, checkIDEqualityLessThanArgument) {
    Service a_service(000111, "test_service", 10.0);
    EXPECT_EQ(a_service.compare_ID(000112), -1) << "ID equal or greater than argument.";
}

TEST(compare_IDTest, checkIDEqualityGreaterThanArgument) {
    Service a_service(000111, "test_service", 10.0);
    EXPECT_EQ(a_service.compare_ID(000110), 1) << "ID equal or less than argument.";
}

// --------------------------------------------------------------------------------------------

TEST(display_serviceTest, checkDisplayServiceEmpty) {
    Service a_service;
    EXPECT_EQ(a_service.display_service(), 0) << "Service not displayed.";
}

TEST(display_serviceTest, checkDisplayServicePopulated) {
    Service a_service(000111, "test_service", 10.0);
    EXPECT_EQ(a_service.display_service(), 0) << "Service not displayed.";
}

// --------------------------------------------------------------------------------------------


TEST(displayTest, checkDisplayEmpty) {
    Service a_service;
    EXPECT_EQ(a_service.display(), 0) << "Service not displayed.";
}

TEST(displayTest, checkDisplayPopulated) {
    Service a_service(000111, "test_service", 10.0);
    EXPECT_EQ(a_service.display(), 0) << "Service not displayed.";
}

// --------------------------------------------------------------------------------------------

TEST(get_service_codeTest, checkGetServiceCodeEmpty) {
    Service a_service;
    int to_receive;
    a_service.get_service_code(to_receive);
    EXPECT_EQ(to_receive, 0) << "Service code not received.";
}

TEST(get_service_codeTest, checkGetServiceCodePopulated) {
    Service a_service(000111, "test_service", 10.0);
    int to_receive;
    a_service.get_service_code(to_receive);
    EXPECT_EQ(to_receive, 000111) << "Service code not received.";
}

// --------------------------------------------------------------------------------------------


TEST(create_service_stringTest, checkCreateServiceStringEmpty) {
    Service a_service;
    char buffer[100];
    a_service.create_service_string(buffer);
    // EXPECT_STREQ is used to compare C strings.
    EXPECT_STREQ(buffer, "|0.00") << "Service string not created.";
}

TEST(create_service_stringTest, checkCreateServiceStringPopulated) {
    Service a_service(000111, "test_service", 10.0);
    char buffer[100];
    a_service.create_service_string(buffer);
    // EXPECT_STREQ is used to compare C strings.
    EXPECT_STREQ(buffer, "test_service|10.00") << "Service string not created.";
}