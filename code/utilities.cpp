#include "utilities.h"

// Sample unit test function.
int add(int a, int b) {
  return a + b;
}

int read_int() {
  //temp integer to be inputted
  int temp = 0;
  cin >> temp;
  while(!cin || temp <= 0) {
    cin.clear();
    cin.ignore(MAX, '\n');
    cout << "\nInvalid input! Try again: ";
    cin  >> temp;
  }
  cin.ignore(MAX, '\n');
  return temp;
}

long read_long() {
  //temp integer to be inputted
  long temp = 0;
  cin >> temp;
  while(!cin || temp <= 0) {
    cin.clear();
    cin.ignore(MAX, '\n');
    cout << "\nInvalid input! Try again: ";
    cin  >> temp;
  }
  cin.ignore(MAX, '\n');
  return temp;
}

char read_char() {
  //temp char to be inputted
  char temp = '\0';
  cin >> temp;
  while(!cin) {
    cin.clear();
    cin.ignore(MAX, '\n');
    cout << "\nInvalid character! Try again: ";
    cin  >> temp;
  }
  cin.ignore(MAX, '\n');
  return temp;
}

double read_double() {
  //temp double to be inputted
  double temp = 0;
  cin >> temp;
  while(!cin || temp <= 0) {
    cin.clear();
    cin.ignore(MAX, '\n');
    cout << "\nInvalid input! Try again: ";
    cin  >> temp;
  }
  cin.ignore(MAX, '\n');
  return temp;
}

float read_float() {
  //temp double to be inputted
  float temp = 0;
  cin >> temp;
  while(!cin || temp <= 0) {
    cin.clear();
    cin.ignore(MAX, '\n');
    cout << "\nInvalid input! Try again: ";
    cin  >> temp;
  }
  cin.ignore(MAX, '\n');
  return temp;
}

string read_string() {
  //temp string to be inputted
  string input;
  getline(cin, input);
  //while(input.find_first_not_of(' ') == string::npos) {
  //  cout << "\nInvalid input! Try again: ";
  //  getline(cin, input);
  //}
  return input;
}

bool isNumeric(const string& str) {
  for (char c : str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

void printServices(const string & filename) {
  ifstream in;

  in.open(filename);
  if(!in) {
    cerr << "Failed to open file " << filename << endl;
    exit(0);
    return;
  }

  string serviceName = "";
  int serviceCode = 0;
  int serviceFee  = 0;

  cout << "\t" << left << setw(15) << "Service Code";
  cout << setw(34) << "Service Name";
  cout << setw(15) << "Service Fee" << endl;

  in >> serviceCode;
  in.ignore(1, '|');
  while(!in.eof()) {
    getline(in, serviceName, '|');
    in >> serviceFee;
    in.ignore(1, '\n');

    cout << "\t" << left << setw(15) << serviceCode;
    cout << setw(34) << serviceName;
    cout << setw(15) << serviceFee << endl;

    in >> serviceCode;
    in.ignore(1, '|');
  }

  in.close();
}

string removeWhitespace(const string & str) {
  string newStr = str;
  newStr.erase(remove(newStr.begin(), newStr.end(), ' '), newStr.end());
  return newStr;
}

string getCurrentDateMMDDYYYY() {
  char time_char[80];
  time_t t = time(0);
  strftime(time_char, 80, "%m%d%Y", localtime(&t));
  string time_str = time_char;
  return time_str;
}

int checkIfFileEmptyAndOpenable(const string & filename) {
  ifstream fileToTest(filename);
  if (!fileToTest.is_open()) return 0;
  fileToTest.seekg(0, ios::end);
  if (filesystem::file_size(filename) == 0) return 1;
  fileToTest.close();
  return 2;
}


int generateProviderReport(map<string, vector<vector<string>>> & providerRecords, const string & filename) {
  int result = checkIfFileEmptyAndOpenable(filename);
  if (result != 2) return result;
  ifstream inputFile(filename);
  string line, filename_to_write;

  //Ignoring the first line specifying each part
  getline(inputFile, line);

  //Read input file and parse the service records
  while(getline(inputFile, line)) {
    size_t pos = 0;
    string field;
    vector<string> recordFields;
    while((pos = line.find('|')) != string::npos) {
      field = line.substr(0, pos);
      recordFields.push_back(field);
      line.erase(0, pos + 1);
    }
    recordFields.push_back(line);
    providerRecords[recordFields[6]].push_back(recordFields);
  }

  //Generate reports for each provider
  for (const auto &[providerName, records]: providerRecords) {
    filename_to_write = "../text-documents/weekly-provider-reports/" + removeWhitespace(providerName) + "_" +
      getCurrentDateMMDDYYYY() + "." + records.front()[5] + ".txt";
    ofstream outputFile(filename_to_write);
    outputFile << "First Name     : " << providerName << endl;
    outputFile << "Street Address : " << records.front()[7] << endl;
    outputFile << "City           : " << records.front()[8] << endl;
    outputFile << "State          : " << records.front()[9] << endl;
    outputFile << "Zip Code       : " << records.front()[10] << endl;

    outputFile << endl;
    outputFile << left << setw(20) << "Service Date";
    outputFile << setw(23) << "Record Date";
    outputFile << setw(20) << "Member Name";
    outputFile << setw(15) << "Member #";
    outputFile << setw(15) << "Service Code";
    outputFile << setw(15) << "Service Fee" << endl;

    //Write service records
    double totalFee = 0;
    for (const auto& record : records) {
      totalFee += stod(record[3]);
      outputFile << left << setw(20) << record[1];
      outputFile << setw(23) << record[4];
      outputFile << setw(20) << record[12];
      outputFile << setw(15) << record[11];
      outputFile << setw(15) << record[0];
      outputFile << setw(15) << record[3] << endl;
    }
    outputFile << endl;
    outputFile << "Total number of consultations : " << records.size() << endl;
    outputFile << "Total fee for the week        : " << totalFee       << endl;
    result = checkIfFileEmptyAndOpenable(filename_to_write);
    outputFile.close();
  }
  return result;
}

void printProviderReport(const map<string, vector<vector<string>>> & providerRecords) {
  for (const auto &[providerName, records] : providerRecords) {
    cout << "\tName           : " << providerName << endl;
    cout << "\tStreet Address : " << records.front()[7] << endl;
    cout << "\tCity           : " << records.front()[8] << endl;
    cout << "\tState          : " << records.front()[9] << endl;
    cout << "\tZip Code       : " << records.front()[10] << endl;
    cout << endl;

    cout << "\t" << left << setw(20) << "Service Date";
    cout << setw(23) << "Record Date";
    cout << setw(20) << "Member Name";
    cout << setw(15) << "Member #";
    cout << setw(15) << "Service Code";
    cout << setw(15) << "Service Fee" << endl;

    //Write service records
    double totalFee = 0;
    for (const auto& record : records) {
      totalFee += stod(record[3]);
      cout << "\t" << left << setw(20) << record[1];
      cout << setw(23) << record[4];
      cout << setw(20) << record[12];
      cout << setw(15) << record[11];
      cout << setw(15) << record[0];
      cout << setw(15) << record[3] << endl;
    }
    cout << endl;
    cout << "\tTotal number of consultations : " << records.size() << endl;
    cout << "\tTotal fee for the week        : " << totalFee       << endl;
  }
}

int generateMemberReport(map<string, vector<vector<string>>> & memberRecords, const string & filename) {
  int result = checkIfFileEmptyAndOpenable(filename);
  if (result != 2) return result;
  ifstream inputFile(filename);
  string line, filename_to_write;

  //Ignoring the first line specifying each part
  getline(inputFile, line);

  //Read input file and parse the service records
  while(getline(inputFile, line)) {
    size_t pos = 0;
    string field;
    vector<string> recordFields;
    while((pos = line.find('|')) != string::npos) {
      field = line.substr(0, pos);
      recordFields.push_back(field);
      line.erase(0, pos + 1);
    }
    recordFields.push_back(line);
    memberRecords[recordFields[12]].push_back(recordFields);
  }

  //Generate reports for each member
  for (const auto &[memberName, records]: memberRecords) {
    filename_to_write = "../text-documents/weekly-member-reports/" + removeWhitespace(memberName) + "_" +
      getCurrentDateMMDDYYYY() + "." + records.front()[11] + ".txt";
    ofstream outputFile(filename_to_write);
    outputFile << "Member Name    : " << memberName << endl;
    outputFile << "Member Number  : " << records.front()[11] << endl;
    outputFile << "Street Address : " << records.front()[12] << endl;
    outputFile << "City           : " << records.front()[13] << endl;
    outputFile << "State          : " << records.front()[14] << endl;
    outputFile << "Zip Code       : " << records.front()[15] << endl;
    outputFile << endl;

    outputFile << left << setw(20) << "Service Date";
    outputFile << setw(20) << "Provider Name";
    outputFile << setw(20) << "Service Name";
    outputFile << setw(20) << "Service Code" << endl;

    //Write service records
    for (const auto& record : records) {
      outputFile << left << setw(20) << record[1];
      outputFile << setw(20) << record[6];
      outputFile << setw(20) << record[2];
      outputFile << setw(20) << record[0] << endl;
    }
    outputFile << endl;
    result = checkIfFileEmptyAndOpenable(filename_to_write);
    outputFile.close();
  }
  return result;
}

void printMemberReport(const map<string, vector<vector<string>>> & memberRecords) {
  for (const auto &[memberName, records]: memberRecords) {
    cout << "\tMember Name    : " << memberName << endl;
    cout << "\tMember Number  : " << records.front()[11] << endl;
    cout << "\tStreet Address : " << records.front()[12] << endl;
    cout << "\tCity           : " << records.front()[13] << endl;
    cout << "\tState          : " << records.front()[14] << endl;
    cout << "\tZip Code       : " << records.front()[15] << endl;
    cout << endl;

    cout << "\t" << left << setw(20) << "Service Date";
    cout << setw(20) << "Provider Name";
    cout << setw(20) << "Service Name";
    cout << setw(20) << "Service Code" << endl;

    //Write service records
    for (const auto& record : records) {
      cout << "\t" << left << setw(20) << record[1];
      cout << setw(20) << record[6];
      cout << setw(20) << record[2];
      cout << setw(20) << record[0] << endl;
    }

    cout << endl;
  }
}

void generateWeeklyEFTReport(const string& providerReportFilename) {
  ifstream inputFile(providerReportFilename);
  if(!inputFile.is_open()) {
    cerr << "Failed to open the provider report file." << endl;
    return;
  }

  // Map to store total payments for each provider
  map<string, double> providerPayments;

  string line;
  while (getline(inputFile, line)) {
    istringstream iss(line);
    string providerNumber, serviceName;
    double serviceFee;
    if (getline(iss, providerNumber, '|') && getline(iss, serviceName, '|') &&
        (iss >> serviceFee)) {

      providerPayments[providerNumber] += serviceFee;
    }
  }

  inputFile.close();

  // Open the output file for writing the EFT report
  ofstream outputFile("../text-documents/weekly_EFT.txt");
  if (!outputFile.is_open()) {
    cerr << "Failed to create the output file." << endl;
    return;
  }

  // Write the EFT report header
  outputFile << "Provider Name" << setw(25) << "| Provider Number" << setw(25) << "| Payment" << endl;

  // Write the EFT report data
  double totalFees = 0.0;
  for (const auto& [providerNumber, payment] : providerPayments) {
    outputFile << setw(15) << "Provider " << setw(7) << "| " << setw(10) << providerNumber << setw(20) << "| "<< setw(7) << payment << endl;
    totalFees += payment;
  }

  // Write total fees at the bottom
  outputFile << endl << "Total Fees: " << totalFees << endl;

  // Close the output file
  outputFile.close();

  cout << "Weekly EFT report has been generated successfully." << endl;
}


