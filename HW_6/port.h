#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "generic-field.h"

class Port : public GenericField {
	int min_port;
	int max_port;
public:
	String relevent_port;

	Port(String valid_values);

	~Port();

	bool match(String packet);

	bool set_value(String value);

	bool check_in_range(int port_num) const;
};
#endif
