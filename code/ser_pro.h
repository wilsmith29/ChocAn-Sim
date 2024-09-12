#include "person.h"
#include "service.h"

#define BUF_SIZE 450
#define FILENAME "../text-documents/services_provided.txt" 

class ServiceProvided
{
        public:
                ServiceProvided();
                ServiceProvided(const Person & i_member, const Person & i_provider, const Service & i_service, const string & i_date, const time_t & rawtime);

                int input_provider(const Person & i_provider);
                int input_member(const Person & i_member);
                int input_service(const Service & i_service);
                int input_provider_date(const string & i_date);
                int input_received_date(const time_t & rawtime);

                int display(void);
		int record_a_service(void);
		
        private:
                Person member;
                Person provider;
                Service service;
                string provider_date;
                char received_date[80]; //a string that has MM-DD-YYYY H:M:S
                tm * received_time;
};
