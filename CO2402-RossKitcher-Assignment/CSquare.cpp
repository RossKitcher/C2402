// Ross Kitcher

#include <iostream>
#include "CSquare.h"

using namespace std;

// Base constructor to set member variables used by all derived classes.
CSquare::CSquare(int id, string name) {
	mType = id;
	mName = name;

}

// Setter to set mName.
void CSquare::SetName(string name) {
	mName = name;
}

// Getter to get mName.
string CSquare::GetName() {
	return mName;
}

// Getter to get mType.
int CSquare::GetType() {
	return mType;
}

