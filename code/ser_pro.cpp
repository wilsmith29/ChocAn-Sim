#include "ser_pro.h"


ServiceProvided::ServiceProvided()
{
        provider_date = "";
        memset(received_date, 0, sizeof(received_date));
        received_time = NULL;
}

ServiceProvided::ServiceProvided(const Person & i_member, const Person & i_provider, const Service & i_service, const string & i_date, const time_t & rawtime)
{
        member = i_member;
        provider = i_provider;
        service = i_service;
        provider_date = i_date;

        received_time = localtime(&rawtime);
        strftime(received_date, 80, "%m-%d-%Y %H:%M:%S", received_time);
}

int ServiceProvided::input_provider(const Person & i_provider)
{
        provider = i_provider;
        return 0;
}

int ServiceProvided::input_member(const Person & i_member)
{
        member = i_member;
        return 0;
}

int ServiceProvided::input_service(const Service & i_service)
{
        service = i_service;
        return 0;
}

int ServiceProvided::input_provider_date(const string & i_date)
{
        provider_date = i_date;
        return 0;
}

int ServiceProvided::input_received_date(const time_t & rawtime)
{
        received_time = localtime(&rawtime);
        strftime(received_date, 80, "%m-%d-%Y %H:%M:%S", received_time);

        return 0;
}

int ServiceProvided::display(void)
{
	member.display_member_provided_service();
	service.display_service();	
	cout << "Service Date : " << provider_date << endl;
	cout << "Received time: " << received_date << endl; 
        return 0;
}

int ServiceProvided::record_a_service(void)
{
	ofstream outf;
	fstream f;
	string hold;

	char buffer[BUF_SIZE] = {'\0'};
	char service_info[80] = {'\0'};
	char provider_info[100] = {'\0'};
	char member_info[100] = {'\0'};
	int ser_id = 0;

	service.get_service_code(ser_id);

	provider.create_person_string(provider_info);
	member.create_person_string(member_info);
	service.create_service_string(service_info);

	sprintf(buffer, "\n%d|%s|%s|%s|%s|%s", ser_id, provider_date.c_str(), service_info, received_date, provider_info, member_info);

	outf.open(FILENAME, ios::app);
	if (!outf)
	{
		fprintf(stderr, "The file \"%s\" was not found", FILENAME);
		return 1;
	}
	else
	{
		outf << buffer;
		outf.close();
	}

	return 0;
}
