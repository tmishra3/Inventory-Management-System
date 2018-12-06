#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product
{
public:
	
	Product (int pn = 0, string n = "", int q = 0, double c = 0.0);
	string getToolName() const;
	int getQuantity() const;
	int getPartNumber() const;
	void setPartNumber(int pn);
	double getCost() const;
	void setQuantity(int q);
	void setCost(double c);
	void setToolName(string n);
private:
	string name;
	int quantity;
	double cost;
	int partNumber;
};

#endif
