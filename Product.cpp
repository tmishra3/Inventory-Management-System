#include <iostream>
#include "Product.h"
#include <string>
#include <vector>

using namespace std;


Product::Product(int pn, string n, int q, double c)
{
partNumber = pn;
name = n;
quantity = q;
cost = c;
}

string Product::getToolName() const
{
	return name;
}

int Product::getPartNumber() const
{
	return partNumber;
}

void Product::setPartNumber(int pn)
{
	partNumber = pn;
}

int Product::getQuantity() const
{
	return quantity;
}

double Product::getCost() const
{
	return cost;
}

void Product::setToolName(string n)
{
	name = n;
}

void Product::setQuantity(int q)
{
	quantity = q;
}

void Product::setCost(double c)
{
	cost = c;
}
