#pragma once
#include "utilities.h"

class Service {
	public:
		Service();
		Service(const int & id, const string & i_name, const float & i_cost);
		
		int compare_ID(const int & id);
		int display_service(void) const;
		int display(void) const;

		int get_service_code(int & to_receive);
		int create_service_string(char * buffer);
		
	private:
		int ID;
		string service_name;
		float service_fee;
};
