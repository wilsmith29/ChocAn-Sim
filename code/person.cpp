#include "person.h"

//Default Contructor
Person::Person() {	
	ID = 0;
	status = "";
	type = "";
	first_name = "";
	last_name = "";
	street_add = "";
	city = "";
	state = "";
	zip_code = 0;
}

//Contructor with Arguments
Person::Person(const long & id, const string & i_status, const string & i_type, const string & first, const string & last
, const string & s_address, const string & i_city, const string & i_state, const int & zip) {
	ID = id;
	status = i_status;
	type = i_type;
	first_name = first;
	last_name = last;
	street_add = s_address;
	city = i_city;
	state = i_state;
	zip_code = zip;
}

//Destructor - Sets everything to 0 or empty string
Person::~Person() {
	ID = 0;
	status = "";
	type = "";
	first_name = "";
	last_name = "";
	street_add = "";
	city = "";
	state = "";
	zip_code = 0;
}

//Compares only the person's ID to the inputted ID
int Person::compare_ID(const long & id) {
	if (ID == id) return 0;
	else if (ID < id) return -1;

	return 1;
}

//Verifies if there is a member, if no match return 1. If ID matches but the member is suspended return 2
//if ID matches but member is inactive, return 3. If member is active returns 0
int Person::verify_person(const long & id) {
	if (compare_ID(id) == 0)
	{
		if (status.compare(S_STAT) == 0) return 2;
		else if (status.compare(I_STAT) == 0) return 3;
		return 0;
	}
	return 1;
}

int Person::display_member_provided_service(void)
{
	cout << "\tMember Number : " << ID << endl;
	cout << "\tMember Name   : " << first_name << " " << last_name << endl;
	
	return 0;
}

int Person::display_person(void) const {
	cout << "Person:\t" << first_name << " " << last_name << endl;
	cout << "ID:\t" << ID << endl;
	cout << "Status:\t" << status << endl;
	cout << "Type:\t" << type << endl;

	cout << "Street:\t" << street_add << endl;
	cout << "City:\t" << city << endl;
	cout << "State:\t" << state << endl;
	cout << "Zip:\t" << zip_code << endl << endl;

	return 0;
}

//KP - need it for the update/deactivate function
//for some reason the status display is weird weird
int Person::display_person_formatted() const {
	cout << "\t\tMember Number : " << ID << endl;
	cout << "\t\tFirst Name    : " << first_name  << endl;
    cout << "\t\tLast Name     : " << last_name   << endl;
    cout << "\t\tStreet Address: " << street_add << endl;
    cout << "\t\tCity          : " << city   << endl;
    cout << "\t\tState         : " << state  << endl;
    cout << "\t\tZipcode       : " << zip_code  << endl;
	cout << "\t\tStatus	      : " << status << endl;
	return 0;
}

int Person::create_person_string(char * buffer)
{

	sprintf(buffer, "%ld|%s %s|%s|%s|%s|%d", ID, first_name.c_str(), last_name.c_str(), street_add.c_str(), city.c_str(), state.c_str(), zip_code);
	return 0;
}

int Person::retrieve_info(Person & to_fill) {
	to_fill.ID = ID;
	to_fill.status = status;
	to_fill.type = type;
	to_fill.first_name = first_name;
	to_fill.last_name = last_name;
	to_fill.street_add = street_add;
	to_fill.city = city;
	to_fill.state = state;
	to_fill.zip_code = zip_code;
	
	return 0;
}

//Azeezah - This function is called to change the information of a person.
//The information that will be changed is initially loaded into another Person object.
//This object is then passed into the vector object which then finds the person to be updated. It then calles
//this function on the found object, passing in the Person object with new information.
int Person::change_person_info(const Person & updated)
{
	int to_return = 0;
	
//	int comp_result = first_name.compare(updated.first_name);
	bool result = updated.first_name.empty();
	if (result == false)
	{
		first_name = updated.first_name;
	}

	result = updated.last_name.empty();
	if (result == false)
	{
		last_name = updated.last_name;
	}
	
	result = updated.status.empty();
	if (result == false)
	{
		if (status.compare(S_STAT) == 0) 
		{
			to_return = 2;	
		}
		else if (updated.status.compare(S_STAT) == 0) 
		{
			to_return = 3;
		}
		status = updated.status;
	}
	
	result = updated.street_add.empty();
	if (result == false)
	{
		street_add = updated.street_add;
	}
	
	result = updated.city.empty();
	if (result == false)
	{
		city = updated.city;
	}

	result = updated.state.empty();
	if (result == false)
	{
		state = updated.state;
	}

	if (updated.zip_code != 0)
	{
		zip_code = updated.zip_code;
	}
	
	return to_return;
}

int Person::change_first_name(const string & first)
{
	bool result = first.empty();
	if (result == false)
	{
		first_name = first;
		return 0;
	}
	return 1;
}

int Person::change_last_name(const string & last)
{
	bool result = last.empty();
	if (result == false)
	{
		last_name = last;
		return 0;
	}
	return 1;
}

int Person::change_status(const string & i_status)
{
	bool result = i_status.empty();
	if (result == false)
	{
		//if (status.compare(S_STAT) == 0) return 2;
		//else if (i_status.compare(S_STAT) == 0) return 3;
		status = i_status;
	}
	return 1;
}

int Person::change_street_add(const string & s_address)
{
	bool result = s_address.empty();
	if (result == false)
	{
		street_add = s_address;
		return 0;
	}
	return 1;
}

int Person::change_city(const string & i_city)
{
	bool result = i_city.empty();
	if (result == false)
	{
		city = i_city;
		return 0;
	}
	return 1;
}

int Person::change_state(const string & i_state)
{
	bool result = i_state.empty();
	if (result == false)
	{
		state = i_state;
		return 0;
	}
	return 1;
}

int Person::change_zip(const int & zip)
{
	if (zip != 0)
	{
		zip_code = zip;
		return 0;
	}
	return 1;
}

