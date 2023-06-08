#include "port.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define MAX 65535
#define MIN 0
#define VALID_PACKET_DEVIDE 8
#define PACKET_DM "=,"
#define PORT_RULE_DM "-"
#define VALID_PORT_DEVIDE 2

using namespace std;

enum { SUCCESS = 1 , FAIL = 0};


Port::Port(String relevent_port) {
	max_port = MAX;
	min_port = MIN;
	this->relevent_port = relevent_port;
}

Port::~Port() {

}

bool Port::set_value(String value) {
	size_t len;
	String * output;
	(value.trim()).split(PORT_RULE_DM, &output, &len);

	if(len != VALID_PORT_DEVIDE) {
		delete [] output;
		return SUCCESS;
	}

	int min_check = output[0].to_integer(), max_check = output[1].to_integer();

	if(min_check < MIN || min_check > MAX || min_check > max_check) {
		delete [] output;
		return FAIL;
	}

	if(max_check < MIN || max_check > MAX) {
		delete [] output;
		return FAIL;
	}

	min_port = min_check;
	max_port = max_check;
	delete [] output;

	return SUCCESS;
}

bool Port::check_in_range(int port_num) const {
	if(port_num < min_port || port_num > max_port) {
		return FAIL;
	}

	return SUCCESS;
}

bool Port::match(String packet) {
	packet = packet.trim();

	size_t len;
	String * devided_packet;
	packet.split(PACKET_DM, &devided_packet, &len);

	if(len != VALID_PACKET_DEVIDE) {
		delete [] devided_packet;
		return FAIL;
	}

	for(int i = 0; i < VALID_PACKET_DEVIDE ; i += 2) {
		if(this->relevent_port.equals(devided_packet[i].trim())) {
			String port_num = devided_packet[i+1];
			delete [] devided_packet;
			return check_in_range(port_num.trim().to_integer());
		}
	}

	delete [] devided_packet;
	return FAIL;
}
