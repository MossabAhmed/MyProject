#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include <random>
using namespace std;
enum enType{enVip = 1, enNor = 2};
class Seat
{
	char _Row;
	int _Culomn;
	enType _Type;

public:
	Seat(char row, int culomn)
	{
		_Row = row;
		_Culomn = culomn;
		if (toupper(_Row) == 'A')
			_Type == enType::enVip;
		else
			_Type == enType::enNor;
	}

	Seat(){}

	void setRow(char row)
	{
		_Row = row;

	}

	void setCulomn(int culomn)
	{
		_Culomn = culomn;
	}

	char getRow()
	{
		return _Row;
	}

	int getCulomn()
	{
		return _Culomn;
	}


	

};

