#include "../code/person.h"
#include "gtest/gtest.h"

#define FIRST "John"
#define LAST "Doe"
#define ZIP 90394
#define STREET "12395 Whatever St"
#define CITY "Beaverton"
#define STATE "OR"
#define TYPE "PROVIDER"
#define ID 983385903

// ---------------------------------------------------------------------------------------
// compare_ID(const long & id) 
TEST(compare_IDTest, checkIDLessThanInput) {
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	EXPECT_EQ(person_test.compare_ID(149385903), 1) << "ID not equal.";
}

TEST(compare_IDTest, checkIDGreaterThanInput) {
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	EXPECT_EQ(person_test.compare_ID(983385904), -1) << "ID less than argument."; 
}

TEST(compareIDTest, checkIDEqualToArguement)
{
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	EXPECT_EQ(person_test.compare_ID(983385903), 0) << "ID is equal to argument.";
}

// ---------------------------------------------------------------------------------------
// verify_person(const long & id)
TEST(verify_IDTest, CheckSuspendedStatus)
{
	Person person_test(ID, S_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	int actual = person_test.verify_person(983385903);
	
	EXPECT_EQ(actual, 2) << "The person is suspended but actual result was " << actual << endl;;
}

TEST(verify_IDTest, CheckInactiveStatus)
{
	Person person_test(ID, I_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	int actual = person_test.verify_person(983385903);

	EXPECT_EQ(actual, 3) << "The person is inactive but actual result was " << actual << endl;
}

TEST(verify_IDTest, CheckActiveStatus)
{
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	int actual = person_test.verify_person(983385903);
	
	EXPECT_EQ(actual, 0) << "The person is active but actual result was " << actual << endl;
}

TEST(verify_IDTest, CheckIfIDNOMatch)
{
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	int actual = person_test.verify_person(983385904);
	
	EXPECT_EQ(actual, 1) << "The ID does not match but actual result was " << actual << endl;
}

// ---------------------------------------------------------------------------------------
// int create_person_string(char * buffer)
TEST(CreatePersonString, CheckIfStringsEqual)
{
	char to_test[] = "983385903|John Doe|12395 Whatever St|Beaverton|OR|90394";
	char result[100] = {'\0'};
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	person_test.create_person_string(result);
	EXPECT_EQ(strcmp(to_test, result), 0) << "The cstrings are not equal, invalid generated string" << endl;
}
// ---------------------------------------------------------------------------------------
// int change_person_info(const Person & updated)
TEST(UpdatePersonInfo, PersonSuspended)
{
	Person person_test(ID, S_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	Person updated_info(ID, I_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);

	int actual = person_test.change_person_info(updated_info);
	EXPECT_EQ(actual, 2) << "The person is suspended, expected result was 2 actual was " << actual << endl;
}
//You cannot update a person's status to suspended
TEST(UpdatePersonInfo, UpdatetoSuspended)
{
	Person person_test(ID, I_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	Person updated_info(ID, S_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);

	int actual = person_test.change_person_info(updated_info);
	EXPECT_EQ(actual, 3) << "The person is not suspended, expected result was 3 actual was " << actual << endl;
}

TEST(UpdatePersonInfo, UpdatePersonValid)
{
	Person person_test(ID, I_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	Person updated_info(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);

	int actual = person_test.change_person_info(updated_info);
	EXPECT_EQ(actual, 0) << "The person was updated, expected result was 0 actual was " << actual << endl;
}

// ---------------------------------------------------------------------------------------
// int change_first_name(const string & first)
TEST(UpdatePersonSectionInfo, ExceptedInputs)
{
	int sum_result, result0, result1, result2, result3, result4, result5;
	sum_result = result0 = result1 = result2 = result3 = result4 = result5 = 0;
	string i_type = "Member";
	string i_first = "Jane";
	string i_last = "Dawn";
	string i_street = "18495 Cheeseburger St";
	string i_city = "Cotton Candy";
	string i_state = "WA";
	int zip = 73950;
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	
	result0 = person_test.change_first_name(i_first);
	result1 = person_test.change_last_name(i_last);
	result2 = person_test.change_street_add(i_street);
	result3 = person_test.change_city(i_city);
	result4 = person_test.change_state(i_state);
	result5 = person_test.change_zip(zip);

	sum_result = result0 + result1 + result2 + result3 + result4 + result5;

	EXPECT_EQ(sum_result, 0) << "There were empty string inputs. The expected result was 0 but the actual result was" << sum_result << endl;
}

TEST(UpdatePersonSectionInfo, EmptyStrings)
{
	int sum_result, result0, result1, result2, result3, result4, result5;
	sum_result = result0 = result1 = result2 = result3 = result4 = result5 = 0;
	string i_type = "";
	string i_first = "";
	string i_last = "";
	string i_street = "";
	string i_city = "";
	string i_state = "";
	int zip = 0;
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	
	result0 = person_test.change_first_name(i_first);
	result1 = person_test.change_last_name(i_last);
	result2 = person_test.change_street_add(i_street);
	result3 = person_test.change_city(i_city);
	result4 = person_test.change_state(i_state);
	result5 = person_test.change_zip(zip);

	sum_result = result0 + result1 + result2 + result3 + result4 + result5;

	EXPECT_EQ(sum_result, 6) << "Some strings were not empty. The expected result was 6 but the actual result was" << sum_result << endl;
}

TEST(UpdatePersonStatus, ExpectedInput)
{
	string to_update = S_STAT;
	Person person_test(ID, A_STAT, TYPE, FIRST, LAST, STREET, CITY, STATE, ZIP);
	int actual = person_test.change_status(to_update);
	EXPECT_EQ(actual, 1) << "Something is wrong with return. The expected was 1 the actual was " << actual << endl;
}


