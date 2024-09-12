#include "interface.h"
#include "service_vec.h"

void begin() {
    PersonVec memberList;
    PersonVec providerList;
    PersonVec managerList;

    SerVec serviceList;
    string fileName = "../text-documents/services.txt";
    serviceList.upload_services(fileName);

    //serviceList.display_services();



    upload_people(memberList, providerList, managerList);
    int userOption = 0;
    displayWelcomeMsg();

    do {
        displayMainMenu();
        cout << "\n=> Option: ";
        userOption = read_int();
        exeCmd(userOption, memberList, providerList, managerList, serviceList);
    } while(userOption != 3);

    displayExitMsg();
}


void exeCmd(int option, PersonVec & memberList, PersonVec & providerList, PersonVec & managerList, SerVec & serviceList) {

    int userOption = 0;
    long password  = 0;
    int check      = 0;
    long id        = 0;
    int zip        = 0;
    int i          = 0;
    string first  = "";
    string last   = "";
    string type   = "";
    string status = "";
    string street = "";
    string city   = "";
    string state  = "";
    string tempZ  = "";

    char save = '\0';
    string input = "";
    Person tempMember;
    Person tempProvider;
    Service tempService;
    map<string, vector<vector<string>>> providerRecords;
    map<string, vector<vector<string>>> memberRecords;
    int reportResult = 0;
    long memberNumber = 0;
    int check2 = 0;
    bool isNumber = false;

    string tempMemberNumber = "";
    string tempName = "";
    int serviceCode = 0;
    string tempS = "";
    string serviceName = "";
    float serviceFee = 0;
    string tempF = "";
    string serviceDate = "";
    //string comments = "";

    time_t raw_time;
    ServiceProvided tempServiceProvided;

    int count = 0;

    switch(option) {

        //-------------------------------------------MAIN MENU OPTION 1 - MANAGER STUFF -------------------------------------------------------------------------------------------------------------
        case 1:
            password = 0;
            cout << "\n\tMANAGER LOGIN" << endl;
            cout << "\t=> Enter Manager ID Number : ";
            password = read_long();
            check = managerList.verify_person(password);

            while(check != 0) {
                cout << "\tManager " << password << " is not found. Check the number and try again" << endl;
                cout << "\t=> Enter Manager Number : ";
                password = read_long();
                check = managerList.verify_person(password);
            }


            if(check == 0) {
                do {
                    managerMenu();
                    cout << "\n\t=> Option: ";
                    userOption = read_int();

                    switch(userOption) {

                        //--------------------------------MANAGER MENU OPTION 1 MANAGE MEMBERS------------------------------------------------------------
                        case 1:
                            do {
                                manageMembersMenu();
                                cout << "\n\t\t=> Option: ";
                                userOption = read_int();

                                switch(userOption) {

                                    //-----------------------------MANAGE MEMBERS MENU OPTION 1 - NEW MEMBER--------------------------
                                    case 1:

                                        for(i = 0; i < 6 && input != "EXIT"; i++) {
                                            cout << "\n\t\tNEW MEMBER DETAILS" << endl;
                                            printDetails(first, last, street, city, state, tempZ);

                                            if(i == 0) {
                                                cout << "\t\t=> Enter First Name : ";
                                                input = read_string();
                                                first = input;
                                            }
                                            else if(i == 1) {
                                                cout << "\t\t=> Enter Last Name : ";
                                                input = read_string();
                                                last = input;
                                            }
                                            else if(i == 2) {
                                                cout << "\t\t=> Enter Street Address : ";
                                                input = read_string();
                                                street = input;
                                            }
                                            else if(i == 3) {
                                                cout << "\t\t=> Enter City : ";
                                                input = read_string();
                                                city = input;
                                            }
                                            else if(i == 4) {
                                                cout << "\t\t=> Enter State : ";
                                                input = read_string();
                                                state = input;
                                            }
                                            else if(i == 5) {
                                                cout << "\t\t=> Enter Zipcode : ";
                                                zip = read_int();
                                                tempZ = to_string(zip);
                                            }
                                        }

                                        status = "Active";
                                        type = "MEMBER";

                                        if(input == "EXIT") {
                                            resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                            cout << "\n\t\tReturned to Manager Menu" << endl;
                                            break;
                                        }

                                        cout << "\n\t\tNEW MEMBER DETAILS" << endl;
                                        printDetails(first, last, street, city, state, tempZ);
                                        cout << "\t\t=> Save New Member Y/N : ";
                                        save = read_char();

                                        if(tolower(save == 'y')) {
                                            srand(time(0));
                                            id = 100'000'000 + rand() % 900'000'000;
                                            cout << "\n\t\tMember Number " << id << " is assigned to ";
                                            cout << first << " " << last << "." << endl;
                                            memberList.upload_person(id, status, type, first, last, street, city, state, zip);
                                        }

                                        //needs to get resetted
                                        resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                        break;

                                    //---------------------------MANAGE MEMBERS MENU OPTION 2 - Update/Deactivate----------------------
                                    case 2:
                                        memberList.display_people();
                                        cout << "\n\n\tRemove the display after done - for testing" << endl << endl;
                                        cout << "\n\t\tSEARCH MEMBER" << endl;
                                        cout << "\t\t=> Enter Member Number : ";
                                        id = read_long();
                                        check = memberList.retrieve_person(id, tempMember);
                                        while(check != 0) {
                                            cout << "\n\t\tMEMBER not found. Check the number and try again" << endl;
                                            cout << "\t\t=> Enter Member Number : ";
                                            cin  >> id;
                                            check = memberList.retrieve_person(id, tempMember);
                                        }

                                        for(i = 0; i < 7 && input != "EXIT"; i++) {
                                            cout << "\n\t\tMEMBER DETAILS" << endl;
                                            cout << "\n\t\tHIT ENTER TO LEAVE AS IS OR UPDATE WITH TEXT" << endl << endl;
                                            tempMember.display_person_formatted();

                                            if(i == 0) {
                                                cout << "\t\t=> Change First Name : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                first = input;
                                            }
                                            else if(i == 1) {
                                                cout << "\t\t=> Change Last Name : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                last = input;
                                            }
                                            else if(i == 2) {
                                                cout << "\t\t=> Change Address : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                street = input;
                                            }
                                            else if(i == 3) {
                                                cout << "\t\t=> Change City : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                city = input;
                                            }
                                            else if(i == 4) {
                                                cout << "\t\t=> Change State : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                state = input;
                                            }
                                            else if(i == 5) {
                                                cout << "\t\t=> Change Zipcode : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                tempZ = input;
                                                zip = stoi(input);
                                            }
                                            else if(i == 6) {
                                                cout << "\t\t=> Change Status : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                status = input;
                                            }
                                        }

                                        if(input == "EXIT") {
                                            resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                            cout << "\n\t\tReturned to Manager Menu" << endl;
                                            break;
                                        }

                                        cout << "\n\t\tMEMBER DETAILS" << endl;
                                        tempMember.display_person_formatted();
                                        cout << "\t\t=> Save Changes Y/N : ";
                                        cin  >> save;

                                        if(tolower(save == 'y')) {
                                            if(!first.empty()) {
                                                tempMember.change_first_name(first);
                                            }
                                            if(!last.empty()) {
                                                tempMember.change_last_name(last);
                                            }
                                            if(!street.empty()) {
                                                tempMember.change_street_add(street);
                                            }
                                            if(!city.empty()) {
                                                tempMember.change_city(city);
                                            }
                                            if(!state.empty()) {
                                                tempMember.change_state(state);
                                            }
                                            if(!tempZ.empty()) {
                                                tempMember.change_zip(zip);
                                            }
                                            if(!status.empty()) {
                                                tempMember.change_status(status);
                                            }
                                            memberList.update_person(id, tempMember);

                                            cout << "\n\t\tMember Details Updated as Follows" << endl;
                                            tempMember.display_person_formatted();
                                        }

                                        //needs to get resetted
                                        resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                        break;

                                    //------------------------------------MANAGE MEMBERS MENU OPTION 3--------------------------
                                    case 3:
                                        cout << "\n\t\tReturned to Manager Menu" << endl;
                                        break;
                                    default:
                                        cout << "\n\t\tInvalid Option! Please try again!" << endl;
                                }

                            } while(userOption != 3);
                            break;

                        //--------------------------------MANAGER MENU OPTION 2 - MANAGE PROVIDERS-------------------------------------------------------
                        case 2:
                            do {
                                manageProvidersMenu();
                                cout << "\n\t\t=> Option: ";
                                userOption = read_int();

                                switch(userOption) {

                                    //----------------------------------MANAGE PROVIDERS MENU 1 - CREATE NEW PROVIDER--------------------------------
                                    case 1:
                                        for(i = 0; i < 6 && input != "EXIT"; i++) {
                                            cout << "\n\t\tNEW PROVIDER DETAILS" << endl;
                                            printDetails(first, last, street, city, state, tempZ);

                                            if(i == 0) {
                                                cout << "\t\t=> Enter First Name : ";
                                                input = read_string();
                                                first = input;
                                            }
                                            else if(i == 1) {
                                                cout << "\t\t=> Enter Last Name : ";
                                                input = read_string();
                                                last = input;
                                            }
                                            else if(i == 2) {
                                                cout << "\t\t=> Enter Street Address : ";
                                                input = read_string();
                                                street = input;
                                            }
                                            else if(i == 3) {
                                                cout << "\t\t=> Enter City : ";
                                                input = read_string();
                                                city = input;
                                            }
                                            else if(i == 4) {
                                                cout << "\t\t=> Enter State : ";
                                                input = read_string();
                                                state = input;
                                            }
                                            else if(i == 5) {
                                                cout << "\t\t=> Enter Zipcode : ";
                                                zip = read_int();
                                                tempZ = to_string(zip);
                                            }
                                        }

                                        status = "Active";
                                        type = "PROVIDER";

                                        if(input == "EXIT") {
                                            resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                            cout << "\n\t\tReturned to Manager Menu" << endl;
                                            break;
                                        }

                                        cout << "\n\t\tNEW PROVIDER DETAILS" << endl;
                                        printDetails(first, last, street, city, state, tempZ);
                                        cout << "\t\t=> Save New Provider Y/N : ";
                                        cin  >> save;

                                        if(tolower(save == 'y')) {
                                            srand(time(0));
                                            id = 100'000'000 + rand() % 900'000'000;
                                            cout << "\n\t\tProvider Number " << id << " is assigned to ";
                                            cout << first << " " << last << "." << endl;
                                            providerList.upload_person(id, status, type, first, last, street, city, state, zip);
                                        }

                                        //needs to get resetted
                                        resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                        break;

                                    //----------------------------------MANAGE PROVIDERS MENU 2 - UPDATE/DEACTIVATE PROVIDER-------------------
                                    case 2:
                                        providerList.display_people();
                                        cout << "\n\n\tRemove the display after done - for testing" << endl << endl;
                                        cout << "\n\t\tSEARCH PROVIDER" << endl;
                                        cout << "\t\t=> Enter Provider Number : ";
                                        id = read_long();
                                        check = providerList.retrieve_person(id, tempProvider);
                                        while(check != 0) {
                                            cout << "\n\t\tPROVIDER not found. Check the number and try again" << endl;
                                            cout << "\t\t=> Enter Provider Number : ";
                                            id = read_long();
                                            check = providerList.retrieve_person(id, tempProvider);
                                        }

                                        for(i = 0; i < 7 && input != "EXIT"; i++) {
                                            cout << "\n\t\tPROVIDER DETAILS" << endl;
                                            cout << "\n\t\tHIT ENTER TO LEAVE AS IS OR UPDATE WITH TEXT" << endl << endl;
                                            tempProvider.display_person_formatted();

                                            if(i == 0) {
                                                cout << "\t\t=> Change First Name : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                first = input;
                                            }
                                            else if(i == 1) {
                                                cout << "\t\t=> Change Last Name : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                last = input;
                                            }
                                            else if(i == 2) {
                                                cout << "\t\t=> Change Address : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                street = input;
                                            }
                                            else if(i == 3) {
                                                cout << "\t\t=> Change City : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                city = input;
                                            }
                                            else if(i == 4) {
                                                cout << "\t\t=> Change State : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                state = input;
                                            }
                                            else if(i == 5) {
                                                cout << "\t\t=> Change Zipcode : ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                tempZ = input;
                                                zip = stoi(input);
                                            }
                                            else if(i == 6) {
                                                cout << "\t\tDelete after - but you its case sens" << endl;
                                                cout << "\t\t=> Change Status (Active, Inactive, Suspend): ";
                                                input = read_string();
                                                if (input.empty()) continue;
                                                status = input;
                                            }
                                        }

                                        if(input == "EXIT") {
                                            resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                            cout << "\n\t\tReturned to Manager Menu" << endl;
                                            break;
                                        }

                                        cout << "\n\t\tPROVIDER DETAILS" << endl;
                                        tempProvider.display_person_formatted();
                                        cout << "\t\t=> Save CHANGES Y/N : ";
                                        cin  >> save;

                                        if(tolower(save == 'y')) {
                                            if(!first.empty()) {
                                                tempProvider.change_first_name(first);
                                            }
                                            if(!last.empty()) {
                                                tempProvider.change_last_name(last);
                                            }
                                            if(!street.empty()) {
                                                tempProvider.change_street_add(street);
                                            }
                                            if(!city.empty()) {
                                                tempProvider.change_city(city);
                                            }
                                            if(!state.empty()) {
                                                tempProvider.change_state(state);
                                            }
                                            if(!tempZ.empty()) {
                                                tempProvider.change_zip(zip);
                                            }
                                            if(!status.empty()) {
                                                tempProvider.change_status(status);
                                            }
                                            providerList.update_person(id, tempProvider);

                                            cout << "\n\t\tProvider Details Updated as Follows" << endl;
                                            tempProvider.display_person_formatted();
                                        }

                                        //needs to get resetted
                                        resetVariables(first, last, type, status, street, city, state, tempZ, zip, id, i, save, input);
                                        break;

                                    //----------------------------------MANAGE PROVIDERS MENU 3 - RETURN TO MANAGER MENU-------------------------
                                    case 3:
                                        cout << "\n\t\tReturned to Manager Menu" << endl;
                                        break;
                                    default:
                                        cout << "\n\t\tInvalid Option! Please try again!" << endl;
                                }

                            } while(userOption != 3);
                            break;

                        //---------------------------------------MANAGER MENU OPTION 3 - Generate Provider Report------------------------------------
                        case 3:
                            cout << "\n\tGenerate Provider Report" << endl << endl;
                            reportResult = generateProviderReport(providerRecords, "../text-documents/services_provided.txt");
                            if(reportResult == 2) {
                                cout << "\n\t-- Provider Reports Emailed Sucessfully --" << endl;
                                cout << "\n\tAll providers emailed:" << endl << endl;
                                printProviderReport(providerRecords);
                            }
                            else {
                                cout << "\n\t-- Provider Reports Emailed Unsucessfully --" << endl;
                            }
                            reportResult = 0;
                            break;

                        //---------------------------------------MANAGER MENU OPTION 4 - Generate Member Report--------------------------------------
                        case 4:
                            cout << "\n\tGenerate Member Report" << endl << endl;
                            reportResult = generateMemberReport(memberRecords, "../text-documents/services_provided.txt");
                            if(reportResult == 2) {
                                cout << "\n\t-- Member Reports Emailed Sucessfully --" << endl;
                                cout << "\n\tAll members emailed: " << endl << endl;
                                printMemberReport(memberRecords);
                            }
                            else {
                                cout << "\n\t-- Member Reports Emailed Unsucessfully --" << endl;
                            }
                            reportResult = 0;
                            break;

                        //---------------------------------------MANAGER MENU OPTION 5 - Exit Manager Menu ------------------------------------------
                        case 5:
                            cout << "\n\tExiting Manager Menu, back to main menu" << endl;
                            break;

                        //------------------------------------------------DEFAULT--------------------------------------------------------------------
                        default:
                            cout << "\n\tInvalid Option! Please try again!" << endl;

                    }                                   //switch case for MANAGER MENU

                } while(userOption != 5);       //do while loop for continuous input

            }                       //if to check if check is valid
            break;

        //-------------------------------------------MAIN MENU OPTION 2 - PROVIDER STUFF ----------------------------------------------------------------------------
        case 2:

            password = 0;
            cout << "\n\tPROVIDER LOGIN" << endl;
            cout << "\t=> Enter Provider ID Number : ";
            password = read_long();
            check = providerList.verify_person(password);

            while(check != 0) {
                cout << "\tProvider " << password << " is not found. Check the number and try again" << endl;
                cout << "\t=> Enter Provider Number : ";
                password = read_long();
                check = providerList.verify_person(password);
            }

            providerList.retrieve_person(password, tempProvider);

            if(check == 0) {
                do {
                    providerMenu();
                    cout << "\n\t=> Option: ";
                    userOption = read_int();

                    switch(userOption) {

                        //---------------------------------------PROVIDER MENU OPTION 1 - Validate Members------------------------------------------
                        case 1:
                            do {
                                cout << "\n\tVALIDATE MEMBERS (TYPE EXIT TO QUIT)" << endl;
                                
                                memberNumber = 0;
                                cout << "\t=> Enter Member Number : ";
                                input = read_string();

                                //need to check if the string is number or not
                                //if so, need to break out or else it'll try to convert
                                //random string to long
                                isNumber = isNumeric(input); 
                                if(input == "EXIT" || !isNumber) {
                                    input = "";
                                    memberNumber = 0;
                                    check2 = 0;
                                    isNumber = false;
                                    break;
                                }

                                //memberNumber = read_long();
                                memberNumber = stol(input);
                                check2 = memberList.verify_person(memberNumber);

                                while(check2 == 1) {
                                    cout << "\tMember " << memberNumber << " is not found. Check the number and try again" << endl;
                                    cout << "\t=> Enter Member Number : ";
                                    input = read_string();
                                    isNumber = isNumeric(input); 
                                    if(input == "EXIT" || !isNumber) {
                                        input = "";
                                        memberNumber = 0;
                                        //check2 = 0;
                                        isNumber = false;
                                        break;
                                    }
                                    //memberNumber = read_long();
                                    memberNumber = stol(input);
                                    check2 = memberList.verify_person(memberNumber);
                                }

                                memberList.retrieve_person(memberNumber, tempMember);

                                if(check2 == 0) {
                                    cout << "\n\tMember " << memberNumber << " is VALID" << endl; 
                                }
                                else if(check2 == 2) {
                                    cout << "\n\tMember " << memberNumber << " is SUSPENDED" << endl; 
                                }
                                else if(check2 == 3) {
                                    cout << "\n\tMember " << memberNumber << " is INACTIVE" << endl; 
                                }
                                else {
                                    cout << "\n\tERROR" << endl; 
                                }
                                memberNumber = 0;
                                input = "";
                                isNumber = false;
                                check2 = 0;

                            } while(input != "EXIT");

                            break;

                        //---------------------------------------PROVIDER MENU OPTION 2 - Enter service deatils-------------------------------------
                        case 2:
                            for(i = 0; i < 3 && input != "EXIT"; i++) {
                                //cout << "\n\tENTER SERVICE DETAILS" << endl;
                                //printDetails2(tempMemberNumber, tempName, tempS, serviceName, tempF, serviceDate);
                                cout << "\tENTER SERVICE DETAILS" << endl;
                                if(count >= 1) {
                                    tempMember.display_member_provided_service();
                                }
                                else {
                                    cout << "\tMember Number : " << tempMemberNumber  << endl;
                                    cout << "\tMember Name   : " << tempName    << endl;
                                }
                                if(count >= 2) {
                                    tempService.display_service();
                                }
                                else {
                                    cout << "\tService Code  : " << tempS       << endl;
                                    cout << "\tService Name  : " << serviceName << endl;
                                    cout << "\tService Fee   : " << fixed << setprecision(2) << tempF << endl;
                                }

                                cout << "\tService Date  : " << serviceDate << endl;

                                if(i == 0) {
                                    //cout << "\t=> Enter Member Number : ";

                                    memberNumber = 0;
                                    cout << "\t=> Enter Member Number : ";
                                    input = read_string();

                                    //need to check if the string is number or not
                                    //if so, need to break out or else it'll try to convert
                                    //random string to long
                                    isNumber = isNumeric(input); 
                                    if(input == "EXIT" || !isNumber) {
                                        input = "";
                                        memberNumber = 0;
                                        check2 = 0;
                                        isNumber = false;
                                        break;
                                    }

                                    memberNumber = stol(input);
                                    check2 = memberList.verify_person(memberNumber);

                                    while(check2 != 0) {
                                        cout << "\n\tMEMBER INVALID - KEEP TRYING OR TYPE EXIT" << endl;
                                        cout << "\n\tENTER SERVICE DETAILS" << endl;
                                        printDetails2(tempMemberNumber, tempName, tempS, serviceName, tempF, serviceDate);
                                        //cout << "\t=> Enter Member Number : ";

                                        memberNumber = 0;
                                        cout << "\t=> Enter Member Number : ";
                                        input = read_string();

                                        //need to check if the string is number or not
                                        //if so, need to break out or else it'll try to convert
                                        //random string to long
                                        isNumber = isNumeric(input); 
                                        if(input == "EXIT" || !isNumber) {
                                            input = "";
                                            memberNumber = 0;
                                            check2 = 0;
                                            isNumber = false;
                                            break;
                                        }

                                        memberNumber = stol(input);
                                        check2 = memberList.verify_person(memberNumber);
                                    }

                                    count++;
                                    memberList.retrieve_person(memberNumber, tempMember);
                                    tempMember.display_member_provided_service();
                                    tempMemberNumber = to_string(memberNumber);
                                }
                                else if(i == 1) {
                                    cout << "\t=> Enter Service Code : ";
                                    serviceCode = read_int();
                                    check = serviceList.verify_service(serviceCode);

                                    while(check != 0) {
                                        cout << "\tENTER SERVICE DETAILS" << endl;
                                        tempMember.display_member_provided_service();
                                        cout << "\tService Code  : " << tempS       << endl;
                                        cout << "\tService Name  : " << serviceName << endl;
                                        cout << "\tService Fee   : " << fixed << setprecision(2) << tempF << endl;
                                        cout << "\tService Date  : " << serviceDate << endl;

                                        cout << "\t=> Enter Service Code : ";
                                        serviceCode = read_int();
                                        check = serviceList.verify_service(serviceCode);
                                    }

                                    serviceList.retrieve_service(serviceCode, tempService);
                                    count++;
                                }
                                else if(i == 2) {
                                    cout << "\t=> Enter Service Date (MM-DD-YYYY) : ";
                                    input = read_string();
                                    serviceDate = input;
                                    time(&raw_time);
                                }
                            }

                            if(input == "EXIT") {
                                resetVariables2(tempMemberNumber, tempName, tempS, serviceName, tempF, serviceDate, serviceFee, serviceCode, input, save); 
                                cout << "\n\tReturned to Provider Menu" << endl;
                                break;
                            }

                            cout << "\n\tSERVICE DETAILS" << endl;
                            cout << "\tENTER SERVICE DETAILS" << endl;
                            if(count >= 1) {
                                tempMember.display_member_provided_service();
                            }
                            else {
                                cout << "\tMember Number : " << tempMemberNumber  << endl;
                                cout << "\tMember Name   : " << tempName    << endl;
                            }
                            if(count >= 2) {
                                tempService.display_service();
                            }
                            else {
                                cout << "\tService Code  : " << tempS       << endl;
                                cout << "\tService Name  : " << serviceName << endl;
                                cout << "\tService Fee   : " << fixed << setprecision(2) << tempF << endl;
                            }

                            cout << "\tService Date  : " << serviceDate << endl;
                            cout << "\t=> Save New Service Y/N : ";
                            cin  >> save;

                            if(tolower(save == 'y')) {
                                tempServiceProvided.input_provider(tempProvider);
                                tempServiceProvided.input_member(tempMember);
                                tempServiceProvided.input_service(tempService);
                                tempServiceProvided.input_provider_date(serviceDate);
                                tempServiceProvided.input_received_date(raw_time);
                                tempServiceProvided.record_a_service();

                                tempServiceProvided.display();

                                count = 0;
                            }

                            //needs to get resetted
                            resetVariables2(tempMemberNumber, tempName, tempS, serviceName, tempF, serviceDate, serviceFee, serviceCode, input, save); 
                            break;

                        //---------------------------------------PROVIDER MENU OPTION 4 - View Service Directory-------------------------------------
                        case 3:
                            cout << "\n\tSERVICES DIRECTORY" << endl << endl;
                            printServices("../text-documents/services.txt");
                            break;

                        //---------------------------------------PROVIDER MENU OPTION 5 - Exit provider menu ----------------------------------------
                        case 4:
                            cout << "\n\tExiting Provider Menu, back to main menu" << endl;
                            break;

                        //---------------------------------------DEFAULT-----------------------------------------------------------------------------
                        default:
                            cout << "\n\tInvalid Option! Please try again! : " << endl;

                    }                           //switch case for PROVIDER MENU

                } while(userOption != 4);  //do while loop for continuous input

            }                       //if to check if check is valid
            break;

        //-------------------------------------------MAIN MENU OPTION 3-------------------------------------------------------------------------------------------------------------------------------------
        case 3:
            cout << "\nExiting Main Menu!" << endl;
            break;

        default:
            cout << "Invalid Option! Please try again!" << endl;

    } //MAIN MENU SWITCH CASE

} //exeCmd

//    cout << "\n**** Main Menu ****" << endl;                        //DONE
//    cout << "1- Manager Login"      << endl;                        //DONE
//    cout << "2- Provider Login"     << endl;                        //DONE
//    cout << "3- Quit"               << endl;                        //DONE

//    cout << "\n\t**** Manager Menu ****"    << endl;                //DONE
//    cout << "\t1- Manage Members"           << endl;                //DONE
//    cout << "\t2- Manage Providers"         << endl;                //DONE
//    cout << "\t3- Generate Provider Report" << endl;                //DONE
//    cout << "\t4- Generate Member Report"   << endl;                //DONE 
//    cout << "\t5- Return to Main Menu"      << endl;                //DONE

//    cout << "\n\t**** Provider Menu ****" << endl;                  //DONE
//    cout << "\t1- Validate Members"       << endl;                  //DONE
//    cout << "\t2- Enter Service Details"  << endl;                  //
//    cout << "\t3- View Service History"   << endl;                  //
//    cout << "\t4- View Service Directory" << endl;                  //DONE
//    cout << "\t5- Return to Main Menu"    << endl;                  //DONE

//    cout << "\n\t\t**** Manage Members Menu ****"    << endl;       //DONE
//    cout << "\t\t1- Create New Member Record"        << endl;       //DONE
//    cout << "\t\t2- Update/Inactivate Member Record" << endl;       //DONE
//    cout << "\t\t3- Return to Manager Menu"          << endl;       //DONE

//    cout << "\n\t\t**** Manage Providers Menu ****"    << endl;     //DONE
//    cout << "\t\t1- Create New Provider Record"        << endl;     //DONE
//    cout << "\t\t2- Update/Inactivate Provider Record" << endl;     //DONE
//    cout << "\t\t3- Return to Manager Menu"            << endl;     //DONE




void displayMainMenu() {
    cout << "\n**** Main Menu ****" << endl;
    cout << "1- Manager Login"      << endl;
    cout << "2- Provider Login"     << endl;
    cout << "3- Quit"               << endl;
}

void providerMenu() {
    cout << "\n\t**** Provider Menu ****" << endl;
    cout << "\t1- Validate Members"       << endl;
    cout << "\t2- Enter Service Details"  << endl;
    cout << "\t3- View Service Directory" << endl;
    cout << "\t4- Return to Main Menu"    << endl;
}

void managerMenu() {
    cout << "\n\t**** Manager Menu ****"    << endl;
    cout << "\t1- Manage Members"           << endl;
    cout << "\t2- Manage Providers"         << endl;
    cout << "\t3- Generate Provider Report" << endl;
    cout << "\t4- Generate Member Report"   << endl;
    cout << "\t5- Return to Main Menu"      << endl;
}

void manageMembersMenu() {
    cout << "\n\t\t**** Manage Members Menu ****"    << endl;
    cout << "\t\t1- Create New Member Record"        << endl;
    cout << "\t\t2- Update/Inactivate Member Record" << endl;
    cout << "\t\t3- Return to Manager Menu"          << endl;
}

void manageProvidersMenu() {
    cout << "\n\t\t**** Manage Providers Menu ****"    << endl;
    cout << "\t\t1- Create New Provider Record"        << endl;
    cout << "\t\t2- Update/Inactivate Provider Record" << endl;
    cout << "\t\t3- Return to Manager Menu"            << endl;
}

void printDetails(string first, string last, string street, string city, string state, string tempZ) {
    cout << "\t\tFirst Name    : " << first  << endl;
    cout << "\t\tLast Name     : " << last   << endl;
    cout << "\t\tStreet Address: " << street << endl;
    cout << "\t\tCity          : " << city   << endl;
    cout << "\t\tState         : " << state  << endl;
    cout << "\t\tZipcode       : " << tempZ  << endl;
}

void printDetails2(string tempMemberNumber, string tempName, string tempS, string serviceName, string tempF, string serviceDate) {
    cout << "\tMember Number : " << tempMemberNumber  << endl;
    cout << "\tMember Name   : " << tempName    << endl;
    cout << "\tService Code  : " << tempS       << endl;
    cout << "\tService Name  : " << serviceName << endl;
    cout << "\tService Fee   : " << fixed << setprecision(2) << tempF << endl;
    cout << "\tService Date  : " << serviceDate << endl;
   // cout << "\tComments      : " << comments    << endl;
}

void resetVariables(string & first, string & last, string & type, string & status,
                    string & street, string & city, string & state, string & tempZ,
                    int & zip, long & id, int & i, char & save, string & input)
{
    first  = "";
    last   = "";
    type   = "";
    status = "";
    street = "";
    city   = "";
    state  = "";
    tempZ  = "";
    zip = 0;
    id  = 0;
    i   = 0;
    save = '\0';
    input = "";
}

void resetVariables2(string & tempMemberNumber, string & tempName, string & tempS, string & serviceName, string & tempF, string & serviceDate,
                     float & serviceFee, int & serviceCode, string & input, char & save) 
{
    tempMemberNumber  = "";
    tempName    = "";
    tempS       = "";
    serviceName = "";
    tempF       = "";
    serviceDate = "";
    //comments    = "";
    serviceCode = 0;
    serviceFee =  0;
    save = '\0';
}

void displayWelcomeMsg() {
    cout << "\nWelcome to the ChocAn interface!\n";
}

void displayExitMsg() {
    cout << "\nThank you for using the ChocAn interface!\n";
}

