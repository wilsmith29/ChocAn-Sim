#include "../code/utilities.h" // Include the header file of the code to be tested.
#include "gtest/gtest.h" // Google Test Framework, must be included in the test file.

// ------------------------------------ SAMPLE UNIT TEST ------------------------------------
// Test case for the add function
// TEST (TestSuiteName, TestName)
TEST(addFunctionTest, positiveNumbers) {
    // Test input
    int a = 3;
    int b = 4;

    // Expected result
    int expected_sum = 7;

    // Call the add function
    int actual_sum = add(a, b);

    // EXPECT_EQ is a macro that compares the actual result with the expected result
    // the test will pass if the actual result is equal to the expected result
    // If the test fails, the message will be printed.
    // Check if the actual result matches the expected result
    EXPECT_EQ(actual_sum, expected_sum) << "The actual sum is not equal to the expected sum, Expected vs. Actual:"
                    << expected_sum << " vs. " << actual_sum;
}

// ---------------------------------------------------------------------------------------
// void printServices(const string & filename)
TEST(printServicesTest, servicesFileOpeneableAndPrintable) {
    // Test input
    string filename = "../text-documents/services.txt";

    // EXPECT_TRUE is a macro that checks if the condition is true
    // the test will pass if the condition is true
    // If the test fails, the message will be printed.
    // Check if the file is open
    EXPECT_TRUE(fopen(filename.c_str(), "r")) << "The file is not open";
    printServices(filename);
}

TEST(printServicesTest, nonexistentFileUnopeneableAndUnprintable) {
    // Test input
    string filename = "../text-documents/empty.txt";

    // EXPECT_FALSE is a macro that checks if the condition is false
    // the test will pass if the condition is false
    // If the test fails, the message will be printed.
    // Check if the file is not open
    EXPECT_FALSE(fopen(filename.c_str(), "r")) << "The file is open";
}

// ---------------------------------------------------------------------------------------

TEST(removeWhitespaceTest, checkStrings) {
    // Test input
    string str = "  This is a string with whitespace  ";
    // Expected result
    string expected_str = "Thisisastringwithwhitespace";
    // Call the removeWhitespace function
    string actual_str = removeWhitespace(str);
    // Check if the actual result matches the expected result
    EXPECT_EQ(actual_str, expected_str) << "The actual string is not equal to the expected string, Expected vs. Actual:"
                    << expected_str << " vs. " << actual_str;
}

// ---------------------------------------------------------------------------------------

TEST(getCurrentDateMMDDYYYYTest, checkDate) {
    // Call the getCurrentDateMMDDYYYY function
    string actual_date = getCurrentDateMMDDYYYY();

    // Check if the actual result is not empty
    EXPECT_FALSE(actual_date.empty()) << "The actual date is empty";
    cout << "Actual date: " << actual_date << endl;
}

// ---------------------------------------------------------------------------------------

TEST(checkIfFileEmptyAndOpenable, nonexistentFile) {
    // Test input (nonexistent file)
    string filename = "../text-documents/empty.txt";

    // EXPECT_FALSE is a macro that checks if the condition is false
    // the test will pass if the condition is false
    // If the test fails, the message will be printed.
    // Check if the file is not open
    EXPECT_EQ(checkIfFileEmptyAndOpenable(filename), 0) << "The file is open";
}

TEST(checkIfFileEmptyAndOpenableTest, emptyFile) {
    // Test file name
    string filename = "../text-documents/empty_test.txt";
    // Create the file
    ofstream file(filename);

    // Test an empty file
    EXPECT_EQ(checkIfFileEmptyAndOpenable(filename), 1) << "The file is not empty";
    // Delete the file
    remove("../text-documents/empty_test.txt");
}

// ---------------------------------------------------------------------------------------

TEST(generateProviderReportTest, nonexistentFile) {
    // Test input
    map<string, vector<vector<string>>> providerRecords;
    const string filename = "../text-documents/empty.txt";

    // Test a nonexistent file
    EXPECT_EQ(generateProviderReport(providerRecords, filename), 0) << "The file is open";
}


TEST(generateProviderReportTest, emptyFile) {
    // Test input
    map<string, vector<vector<string>>> providerRecords;
    const string filename = "../text-documents/empty_test.txt";
    // Create the file
    ofstream file(filename);

    // Test an empty file
    EXPECT_EQ(generateProviderReport(providerRecords, filename), 1) << "The file is not empty";
    // Delete the file
    remove("../text-documents/empty_test.txt");
}

TEST(generateProviderReportTest, checkReport) {
    // Test input
    map<string, vector<vector<string>>> providerRecords;
    const string filename = "../text-documents/services_provided.txt";
    EXPECT_EQ(generateProviderReport(providerRecords, filename), 2) << "The provider records are empty or the file is not open";
    printProviderReport(providerRecords);
}

// ---------------------------------------------------------------------------------------

TEST(generateMemberReportTest, nonexistentFile) {
    // Test input
    map<string, vector<vector<string>>> memberRecords;
    const string filename = "../text-documents/empty.txt";

    // Test a nonexistent file
    EXPECT_EQ(generateMemberReport(memberRecords, filename), 0) << "The file is open";
}

TEST(generateMemberReportTest, emptyFile) {
    // Test input
    map<string, vector<vector<string>>> memberRecords;
    const string filename = "../text-documents/empty_test.txt";
    // Create the file
    ofstream file(filename);

    // Test an empty file
    EXPECT_EQ(generateMemberReport(memberRecords, filename), 1) << "The file is not empty";
    // Delete the file
    remove("../text-documents/empty_test.txt");
}

TEST(generateMemberReportTest, checkReport) {
    // Test input
    map<string, vector<vector<string>>> memberRecords;
    const string filename = "../text-documents/services_provided.txt";
    EXPECT_EQ(generateMemberReport(memberRecords, filename), 2) << "The member records are empty or the file is not open";
    printMemberReport(memberRecords);
}