#pragma once
#include "utilities.h"

#define A_STAT "Active"
#define I_STAT "Inactive"
#define S_STAT "Suspended"

class Person {
	public:
		Person();
		Person(const long & id, const string & i_status, const string & i_type, const string & first, const string & last
			, const string & s_address, const string & i_city, const string & i_state, const int & zip);
		~Person();

		int compare_ID(const long & id);
		int verify_person(const long & id);
		
		int display_member_provided_service(void);

		int display_person(void) const;
		int retrieve_info(Person & to_fill);
		int display_person_formatted() const;

		int create_person_string(char * buffer);


	//Azeezah - The function below achieves the same thing as the functions below the second comment.
	//It just does it in one function by passing in an instances of the Person class.
		int change_person_info(const Person & updated);
		
	// Azeezah - I will most likely change these later on. But for now they will remain this way.
		int change_first_name(const string & first);
		int change_last_name(const string & last);
		int change_status(const string & i_status);
		int change_street_add(const string & s_address);
		int change_city(const string & i_city);
		int change_state(const string & i_state);
		int change_zip(const int & zip);

	private:
		
		long ID;
		string status;
		string type;
		string first_name;
		string last_name;
		string street_add;
		string city;
		string state;
		int zip_code;
};
