#include "service.h"
using namespace std;

Service::Service() {
	ID = 0;
	service_name = "";
	service_fee = 0.0;
}

Service::Service(const int & id, const string & i_name, const float & i_cost) {
	ID = id;
	service_name = i_name;
	service_fee = i_cost;
}
		
int Service::compare_ID(const int & id) {
	if (ID == id) return 0;
	else if (ID < id) return -1;
	return 1;
}

//Testing display function
int Service::display_service(void) const {
	cout << "\tService Code : " << ID << endl;
	cout << "\tService Name : " << service_name << endl;
	cout << "\tService Fee  : " << service_fee << endl;
	return 0;
}

int Service::display(void) const {
	cout << setw(15) << left << ID;
	cout << setw(15) << left << service_name;
	cout << setw(15) << left << service_fee << endl;
	return 0;
}

int Service::get_service_code(int & to_receive)
{
	to_receive = ID;
	return 0;
}

int Service::create_service_string(char * buffer)
{
	sprintf(buffer, "%s|%.2f", service_name.c_str(), service_fee);

	return 0;
}

