#pragma once
#include "person.h"

#define MEM_TYPE "MEMBER"
#define PRO_TYPE "PROVIDER"
#define MAN_TYPE "MANAGER"
#define PEOPLE_FILE "../text-documents/people.txt"

class PersonVec {
	public:
		//Azeezah - I might change this add function to be different than the upload
		//person function
		int add_person(const long & id, const string & i_type, const string & first, const string & last,
			const string & s_address, const string & i_city, const string & i_state, const int & zip);
	
		int update_person(const long & to_find, const Person & to_change);
		int retrieve_person(const long to_find, Person & to_fill);

		int upload_person(const long & id, const string & i_status, const string & i_type, const string & first, const string & last, 
			const string & s_address, const string & i_city, const string & i_state, const int & zip);
		
		int verify_person(const long to_compare);
		int find_person(const long to_compare);

		int display_people(void) const;

	private:
		vector<Person> per_vec;
		Person * hold;
		long starting_value;
};

//The prototype for the function that uploads all members, providers, and managers.
//Returns the largest ID. I was thinking that whenever we create a new member we just increment the
//largest value.
long upload_people(PersonVec & members, PersonVec & providers, PersonVec & managers);
