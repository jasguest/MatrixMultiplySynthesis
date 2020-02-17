#include "CacheEmitter.hpp"
#include <string>
#include <sstream>
using namespace std;

/* This file defines the functions declared in CacheEmitter.hpp */

/* Emit read function, returns the address as a string in hex format to the variable provided to read */
string emit_readInt(int var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}

string emit_readDouble(double var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}

string emit_readFloat(float var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}

/* Emit write function, returns address as a hex string to the provided variable to write */
string emit_writeInt(int var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}

string emit_writeDouble(double var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}

string emit_writeFloat(float var) {
	ostringstream stream;
	stream << &var;
	string address = stream.str();
	return address;
}
