#include "ip.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define MAX 255
#define MIN 0
#define VALID_PACKET_DEVIDE 8
#define BYTE 8
#define PACKET_DM "=,"
#define IP_RULE_DM "./"
#define IP_DM "."
#define MASK_DM "/"
#define VALID_IP_RULE_DEVIDE 5
#define IP_MAX 4

using namespace std;

enum { SUCCESS = 1 , FAIL = 0};


Ip::Ip(String relevent_ip) {
	mask = MIN;
	this->relevent_ip = relevent_ip;
	//bin_ip = {};
}

Ip::~Ip() {

}

/* checks the rule applied for a certain ip, 4 ip addresses between
 * 0 and 255 , and ip mask between 0 and 32
*/
bool Ip::check_ip_rule(String ** ip_addr) const {
	for(int i = 0 ; i < IP_MAX-1; i++) {
		int num = ip_addr[i]->to_integer();
		if(num < MIN || num > MAX) {
			return FAIL;
		}
	}

	int mask_check = ip_addr[IP_MAX]->to_integer();
	if(mask_check < 0 || mask_check > DWORD ) {
		return FAIL;
	}

	return SUCCESS;
}

void Ip::ip_dec_to_bin(int * ip_packet, String * packet) {
	for(int i = 0; i < IP_MAX-1 ; i++) {
		int ip_decimal = packet[i].to_integer();
		for(int j = BYTE -1 ; j >= 0 ;j--) {
			ip_packet[i*BYTE + j] = ip_decimal % 2;
			ip_decimal /= 2;
		}
	}
}

bool Ip::set_value(String value) {
	String* output;
	size_t len;
	(value.trim()).split(IP_RULE_DM, &output, &len);

	if(len != VALID_IP_RULE_DEVIDE) {
		delete [] output;
		return FAIL;
	}

	if(check_ip_rule(&output)) {
		delete [] output;
		return FAIL;
	}

	mask = output[IP_MAX].to_integer();

	ip_dec_to_bin(bin_ip, output);
	delete [] output;
	return SUCCESS;
}

bool Ip::match(String packet) {
	size_t len;
	String * devided_packet;
	(packet.trim()).split(PACKET_DM, &devided_packet, &len);

	if(len != VALID_PACKET_DEVIDE) {
		if(len) {
			delete [] devided_packet;
		}
		return FAIL;
	}

	for(int i = 0; i < VALID_PACKET_DEVIDE ; i += 2) {
		if(this->relevent_ip.equals(devided_packet[i].trim())) {
			String* output;
			size_t len;
			(packet.trim()).split(IP_DM, &output, &len);

			if(len != IP_MAX) {
				delete [] output;
				return FAIL;
			}

			int ip_packet[DWORD];
			ip_dec_to_bin(ip_packet, output);
			
			for(int j = 0; j < mask; j++) {
				if(bin_ip[i] != ip_packet[i]) {
					delete [] output;
					delete [] devided_packet;
					return FAIL;
				}
			}
			
			delete [] output;
			delete [] devided_packet;
			return SUCCESS;
		}
	}

	delete [] devided_packet;
	return FAIL;
}
