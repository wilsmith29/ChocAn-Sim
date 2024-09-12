#include "../code/ser_pro.h"
#include "gtest/gtest.h" // Google Test Framework, must be included in the test file.


TEST(serviceProvided, defaultConstructor)
{
        ServiceProvided sp;
        ASSERT_EQ(sp.display(), 0) << "Default constructor failed";
}

TEST(serviceProvided, constructorWithArgs) {
        Person member(123456789, "Active", "MEMBER", "John", "Doe", "9343 Main St", "Anytown", "OR", 54321);
        Person provider(987654321, "Active", "PROVIDER", "Jane", "Doe", "3439 Main St", "Anytown", "CA", 12345);
        Service service(111222, "A Service", 100.00);
        time_t rawtime;
        time(&rawtime);
        ServiceProvided sp(member, provider, service, "02-28-2024", rawtime);
        ASSERT_EQ(sp.display(), 0) << "Constructor failed";
}

// --------------------------------------------------------------------------------------------


TEST(serviceProvidedInput, allInputsAndDisplay) {
    ServiceProvided sp;
    int final_result = 1, result0 = 1, result1 = 1, result2 = 1, result3 = 1, result4 = 1;
    Person member(123456789, "Active", "MEMBER", "John", "Doe", "9343 Main St", "Anytown", "OR", 54321);
    Person provider(987654321, "Active", "PROVIDER", "Jane", "Doe", "3439 Main St", "Anytown", "CA", 12345);
    Service service(111222, "A Service", 100.00);
    time_t rawtime;
    time(&rawtime);
    result0 = sp.input_provider(provider);
    result1 = sp.input_member(member);
    result2 = sp.input_service(service);
    result3 = sp.input_provider_date("02-28-2024");
    result4 = sp.input_received_date(rawtime);
    final_result = result0 + result1 + result2 + result3 + result4;
    ASSERT_EQ(final_result, 0) << "All inputs failed";
    sp.display();
}

// --------------------------------------------------------------------------------------------

TEST(record_a_serviceTest, record_a_service) {
    Person member(123456789, "Active", "MEMBER", "John", "Doe", "9343 Main St", "Anytown", "OR", 54321);
    Person provider(987654321, "Active", "PROVIDER", "Jane", "Doe", "3439 Main St", "Anytown", "CA", 12345);
    Service service(111222, "A Service", 100.00);
    time_t rawtime;
    time(&rawtime);
    ServiceProvided sp(member, provider, service, "02-28-2024", rawtime);
    int final_result = sp.record_a_service();
    ASSERT_EQ(final_result, 0) << "Record a service failed";
}