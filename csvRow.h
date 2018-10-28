#pragma once
#include <string>
class csvRow {
	std::string price, timestamp;
	static int key; //1 for price, 0 for timestamp
public:
	std::string rowLine;
	void setRowLine();
	void setMembers();
	bool operator<(csvRow& row2);
	void setKey();
};

