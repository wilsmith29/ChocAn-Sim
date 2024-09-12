#include "../code/service_vec.h"
#include "gtest/gtest.h" // Google Test Framework

TEST(upload_servicesANDdisplay_servicesTest, testUploadToVec) {
    const string filename = "../text-documents/services.txt";
    SerVec servec;
    int result = servec.upload_services(filename);
    EXPECT_EQ(result, 0) << "Error with uploading services to vector";
    servec.display_services();
}

// -----------------------------------------------------------------------------------

TEST(verify_serviceTest, testVerifyServiceMatch) {
    SerVec servec;
    servec.upload_services("../text-documents/services.txt");
    int result = servec.verify_service(100002);
    EXPECT_EQ(result, 0) << "Error with verifying service";
}

TEST(verify_serviceTest, testVerifyServiceNoMatch) {
    SerVec servec;
    servec.upload_services("../text-documents/services.txt");
    int result = servec.verify_service(0);
    EXPECT_EQ(result, 1) << "Error with verifying service";
}

// -----------------------------------------------------------------------------------


TEST(add_serviceTest, testAddService) {
    SerVec servec;
    int result = servec.add_service(100002, "Test Service", 100.00);
    EXPECT_EQ(result, 1) << "Error with adding service";
    servec.display_services();
}

// -----------------------------------------------------------------------------------

TEST(display_found_serviceTest, testDisplayFoundService) {
    SerVec servec;
    servec.add_service(100002, "Test Service", 100.00);
    servec.display_found_service();
    EXPECT_EQ(0, 0) << "Error with displaying found service";
}

// -----------------------------------------------------------------------------------

TEST(retrieve_serviceTest, testRetrieveService) {
    SerVec servec;
    servec.add_service(100002, "Test Service", 100.00);
    Service to_fill;
    int result = servec.retrieve_service(100002, to_fill);
    EXPECT_EQ(result, 0) << "Error with retrieving service";
    to_fill.display();
}