#include "../code/person_vec.h" // this is the file that contains the class we are testing
#include "gtest/gtest.h" // include the google test framework

TEST(personVecTest, add_person) {
    PersonVec pv;
    int result = pv.add_person(1, "Active", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "add_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------


TEST(update_personTest, member) {
    PersonVec pv;
    int result = pv.add_person(123456789, "Active", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "add_person failed";
    Person a_person(123456789, "Active", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    result = pv.update_person(123456789, a_person);
    EXPECT_EQ(result, 0) << "update_person failed";
    pv.display_people();
}

TEST(update_personTest, provider) {
    PersonVec pv;
    int result = pv.add_person(123456789, "Active", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "add_person failed";
    Person a_person(123456789, "Active", "PROVIDER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    result = pv.update_person(123456789, a_person);
    EXPECT_EQ(result, 0) << "update_person failed";
    pv.display_people();
}

TEST(update_personTest, manager) {
    PersonVec pv;
    int result = pv.add_person(123456789, "Active", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "add_person failed";
    Person a_person(123456789, "Active", "MANAGER", "John", "Doe", "1234 Main St", "Anytown", "NY", 54321);
    result = pv.update_person(123456789, a_person);
    EXPECT_EQ(result, 0) << "update_person failed";
    pv.display_people();
}

TEST(update_personTest, notFound) {
    PersonVec pv;
    Person a_person(123456789, "Active", "MANAGER", "John", "Doe", "1234 Main St", "Anytown", "NY", 54321);
    int result = pv.update_person(987654321, a_person);
    EXPECT_EQ(result, 1) << "update_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------

TEST(upload_personTest, member) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    pv.display_people();
}

TEST(upload_personTest, provider) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "PROVIDER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    pv.display_people();
}

TEST(upload_personTest, manager) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "MANAGER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------


TEST(retrieve_personTest, found) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    Person a_person;
    result = pv.retrieve_person(123456789, a_person);
    EXPECT_EQ(result, 0) << "retrieve_person failed";
    pv.display_people();
}

TEST(retrieve_personTest, notFound) {
    PersonVec pv;
    Person a_person;
    int result = pv.retrieve_person(123456789, a_person);
    EXPECT_EQ(result, 1) << "retrieve_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------

TEST(verify_personTest, foundActive) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    result = pv.verify_person(123456789);
    EXPECT_EQ(result, 0) << "verify_person failed";
    pv.display_people();
}

TEST(verify_personTest, foundSuspended) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Suspended", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    result = pv.verify_person(123456789);
    EXPECT_EQ(result, 2) << "verify_person failed";
    pv.display_people();
}

TEST(verify_personTest, foundInactive) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Inactive", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    result = pv.verify_person(123456789);
    EXPECT_EQ(result, 3) << "verify_person failed";
    pv.display_people();
}

TEST(verify_personTest, notFound) {
    PersonVec pv;
    int result = pv.verify_person(123456789);
    EXPECT_EQ(result, 1) << "verify_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------

TEST(find_personTest, found) {
    PersonVec pv;
    int result = pv.upload_person(123456789, "Active", "MEMBER", "John", "Doe", "1234 Main St", "Anytown", "NY", 12345);
    EXPECT_EQ(result, 0) << "upload_person failed";
    result = pv.find_person(123456789);
    EXPECT_EQ(result, 0) << "find_person failed";
    pv.display_people();
}

TEST(find_personTest, notFound) {
    PersonVec pv;
    int result = pv.find_person(123456789);
    EXPECT_EQ(result, 1) << "find_person failed";
    pv.display_people();
}

// --------------------------------------------------------------------------------------------

// 345678997 = highest ID in the people.txt file
TEST(upload_peopleTest, upload_people) {
    PersonVec members;
    PersonVec providers;
    PersonVec managers;

    long result = upload_people(members, providers, managers);
    EXPECT_EQ(result, 345678997) << "upload_people failed";
    members.display_people();
    providers.display_people();
    managers.display_people();
}