#include "ip.h"
#include "port.h"
#include "string.h"
#include "input.h"
#include "generic-field.h"
#include <iostream>
#define RULE_DM "="
#define VALID_RULE_SPLIT 2
#define SIP "src-ip"
#define DIP "dst-ip"
#define SPORT "src-port"
#define DPORT "dst-port"

using namespace std;

enum { SUCCESS = 0 , FAIL = -1};

int main(int argc, char ** argv) {
	if(check_args(argc,argv)) {
		return FAIL;
	}
	size_t len;
	String rule(argv[1]);
	String * rule_type;
	(rule.trim()).split(RULE_DM, &rule_type, &len);

	if(len != VALID_RULE_SPLIT) {
		delete [] rule_type;
		return FAIL;
	}

	GenericField * field;
	//port
	if(rule_type[0].equals(DPORT) || rule_type[0].equals(SPORT)) {
		field = new Port(rule_type[0]);
	}

	//ip
	else if(rule_type[0].equals(SIP) || rule_type[0].equals(DIP)) {
		field = new Ip(rule_type[0]);
	}

	else {
		delete [] rule_type;
		return FAIL;
	}

	int check = field->set_value(rule_type[1]);
	if(check) {
		delete field;
		delete [] rule_type;
		return FAIL;
	}

	parse_input(*field);
	delete [] rule_type;
	delete field;
	return SUCCESS;
}
