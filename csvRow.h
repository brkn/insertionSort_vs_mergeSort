#pragma once
#include <string>
class csvRow {
	std::string price, timestamp;
	static int key;
public:
	std::string rowLine;
	void setMembers();
	bool operator>(csvRow& row2);
	static void setKey(char feature);
};

