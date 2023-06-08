#include "string.h"
#include <cstring>


//constructor
String::String() {
	length = 0;
	data = NULL;
}
//copy constructor using other String type
String::String (const String &str) {
	length = str.length;
	data = new char[length+1];
	strcpy(this->data,str.data);
}
//copy constructor using a char array
String::String (const char* str) {
	if(!str) {
		length = 0;
		data = NULL;
	}
	length = strlen(str);
	data = new char[length+1];
	strcpy(data,str);
}
//deconstructor
String::~String() {
	if(data != NULL) {
		delete [] data;
	}
}
// = operator
String& String::operator= (const String& rhs) {
	if(&rhs != this) {
		if(data) {
			delete [] data;
		}
		length = rhs.length;
		if(length) {
			data = new char[length+1];
			strcpy(data,rhs.data);
		}
		else {
			data = NULL;
		}
	}

	return *this;
}
// = operator with char array
String& String::operator= (const char* str) {
	if(data) {
		delete [] data;
	}
	length = strlen(str);
	if(length) {
		data = new char[length+1];
		strcpy(data,str);
	}
	else {
		data = NULL;
	}
	return *this;
}
//@brief Returns true iff the contents of this equals to rhs
bool String::equals(const String& rhs) const {
	if(!data && !(rhs.data)) {
		return true;
	}
	else if(!data || !(rhs.data)) {
		return false;
	}
	else if(length != rhs.length) {
		return false;
	}
	else if(strcmp(data,rhs.data)) {
		return false;
	}
	return true;
}
//@brief Returns true iff the contents of this equals to rhs
bool String::equals(const char* rhs) const {
	if(!data && !(rhs)) {
		return true;
	}
	else if(!data || !(rhs)) {
		return false;
	}
	else if(length != strlen(rhs)) {
		return false;
	}
	else if(strcmp(data,rhs)) {
		return false;
	}
	return true;
}
//split function
void String::split(const char *delimiters,String **output,size_t *size) const {
	if(!length || !data) {
		(*size) = 0;
		return;
	}

	int num = 0;
	char * str = strcpy(new char[length+1],data);
	char * token =  strtok(str,delimiters);
	while(token) {
		num++;
		token = strtok(NULL,delimiters);
	}


	(*size) = num;
	if(output) {
		delete [] *output;
		*output = new String[num];
		token = str;
		for(int i = 0; i < num ; i++) {
			String string(token);
			(*output)[i] = string;
			token += string.length + 1;
		}
	}

	delete [] str;
}
//convert String to integer
int String::to_integer() const {
	return atoi(data);
}
//trim function
String String::trim() const {
	if(!data || !length) {
		return String();
	}

	int start = 0 , end = length-1;
	while(data[start] == ' ') {
		start++;
	}
	while(data[end] == ' ' && start < end) {
		end--;
	}
	if(data[end] == ' ') {
		return String();
	}

	int len = end-start+1;
	char * temp = new char[len+1];
	strncpy(temp,data+start,len);
	temp[length] = '\0';

	String string(temp);
	delete[] temp;
	return string;
}
