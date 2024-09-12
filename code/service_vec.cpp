#include "service_vec.h"

//#define DELIM 

using namespace std;

int SerVec::upload_services(const string & filename) 
{
	ifstream fin;
	int ser_id;
	string id_buf;
	string name;
	float fee;

	
	fin.open(filename.c_str());
	if (!fin) return 1;
	else
	{
		while(!fin.eof())
		{
			getline(fin, id_buf, '|');	
			getline(fin, name, '|');
			fin >> fee;
			fin.ignore(20, '\n');

			ser_id = stoi(id_buf);

			add_service(ser_id, name, fee);

			fin.peek();
		}
	}

	fin.close();
	return 0;
}

int SerVec::display_services(void) const 
{
	unsigned int size = ser_vec.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		ser_vec[i].display_service();	
	}

	return 0;
}

int SerVec::verify_service(const int to_find)
{
	unsigned int size = ser_vec.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		if (ser_vec[i].compare_ID(to_find) == 0)
		{
		//	ser_vec[i].display_service();
			hold = &ser_vec[i];
			return 0;
		}
	}

	return 1;
}

int SerVec::add_service(const int & id, const string & name, const float & cost) {
	Service to_add(id, name, cost);

	ser_vec.push_back(to_add);
	
	return 1;
}

int SerVec::display_found_service(void) const {
	hold->display_service();
	return 0;
}

int SerVec::retrieve_service(const int to_find, Service & to_fill)
{
	int result = verify_service(to_find);
	if (result == 1)
	{
		return 1;
	}

	to_fill = *hold;
	return 0;
}
