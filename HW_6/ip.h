#ifndef IP_H
#define IP_H

#include "string.h"
#include "generic-field.h"
#define DWORD 32

class Ip : public GenericField {
	int bin_ip [DWORD];
	int mask;
public:
	String relevent_ip;

	Ip(String relevent_ip);

	~Ip();

	bool match(String packet);

	bool set_value(String value);

	bool check_ip_rule(String ** ip_addr) const;
	
	void ip_dec_to_bin(int * ip_packet, String * packet);
};
#endif
