#include "person_vec.h"


int PersonVec::add_person(const long & id, const string & i_type, const string & first, const string & last
, const string & s_address, const string & i_city, const string & i_state, const int & zip) {
	Person to_add(id, A_STAT, i_type, first, last, s_address, i_city, i_state, zip);
	per_vec.push_back(to_add);

	return 0;
}

int PersonVec::update_person(const long & to_find, const Person & to_change) {
	int result = find_person(to_find);
	if (result == 1)
	{
		return 1;
	}

	hold->change_person_info(to_change);

	return 0;
}

int PersonVec::upload_person(const long & id, const string & i_status, const string & i_type, const string & first, const string & last
, const string & s_address, const string & i_city, const string & i_state, const int & zip) {

	Person to_upload(id, i_status, i_type, first, last, s_address, i_city, i_state, zip);
	per_vec.push_back(to_upload);

	return 0;	
}

int PersonVec::retrieve_person(const long to_find, Person & to_fill)
{
	int result = find_person(to_find);
	if (result == 1)
	{
		return 1;
	}
	
	hold->retrieve_info(to_fill);	
	return 0;
}

//Verifies the person or the ID passed in.
//Refer to the verify_person function in the person class for return 
//values.
int PersonVec::verify_person(const long to_compare) {
	int result = -1;
	vector<Person>::iterator it;
	
	for (it = per_vec.begin(); it < per_vec.end(); ++it)
	{
		if (it->compare_ID(to_compare) == 0)
		{
			result = it->verify_person(to_compare);
			return result;	
		}
	}

	return 1;
}

//Find the person, then holds the person object by pointing hold at it.
int PersonVec::find_person(const long to_compare) {
	unsigned int size = per_vec.size();
	
	for (unsigned int i = 0; i < size; ++i)
	{
		if (per_vec[i].compare_ID(to_compare) == 0)
		{
			hold = &per_vec[i];
			return 0;	
		}
	}
	return 1;	
}

int PersonVec::display_people(void) const {
	unsigned int size = per_vec.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		per_vec[i].display_person();		
	}
	
	return 0;
}

// This is not a method or PersonVec - Call this function to upload members, managers, and providers
long upload_people(PersonVec & members, PersonVec & providers, PersonVec & managers) {
    string filename = PEOPLE_FILE;
    ifstream fin;

    long highest_ID = 0;

    long ID = 0;
    string id_buf = "";
    string status = "";
    string type = "";
    string first_name = "";
    string last_name = "";
    string street_add = "";
    string city = "";
    string state = "";
    int zip_code = 0;

    fin.open(filename);
    
	if(!fin) {
		cerr << "\nFailed to open! Exitting!" << endl;
		exit(0);
	}
    else {
        while(!fin.eof()) {
            getline(fin, id_buf, '|');
            getline(fin, first_name, '|');
            getline(fin, last_name, '|');
            getline(fin, status, '|');
            getline(fin, type, '|');
            getline(fin, street_add, '|');
            getline(fin, city, '|');
            getline(fin, state, '|');

            fin >> zip_code;
            fin.ignore(20, '\n');

            ID = stol(id_buf);


            if (type.compare(MAN_TYPE) == 0)
            {
                managers.upload_person(ID, status, type, first_name, last_name, street_add, city, state, zip_code);
            }
            else if (type.compare(MEM_TYPE) == 0)
            {
                members.upload_person(ID, status, type, first_name, last_name, street_add, city, state, zip_code);
            }
            else
            {
                providers.upload_person(ID, status, type, first_name, last_name, street_add, city, state, zip_code);
            }
            if (ID > highest_ID)
            {
                highest_ID = ID;
            }

            fin.peek();
            }
        }

    fin.close();
    return highest_ID;
}
