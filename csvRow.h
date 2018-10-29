
#include <string>
class csvRow {
	std::string timestamp;
	float price;
	static int key; //1 for price 0 for time
public:
	std::string rowLine;
	void setMembers();
	bool operator>(csvRow& row2);
	bool operator<=(csvRow& row2);
	static void setKey(char feature);
};

