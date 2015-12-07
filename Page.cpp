// (Page) Class for handling raw HTML source
#include <iostream>
#include "Page.h"

using namespace std;

Page::Page(string _rawHTML) {
	rawHTML = _rawHTML;
	error = false;
	setName();
	setSwipeBalance();
	setMunchMoney();
}
void Page::setName() {
	string name;
	// Finding location of user's name in HTML string.
	// 27 (length of string to find) is added since find() returns starting pos of string to find
	int pos = rawHTML.find("<div class=\"field-content\">")+27;

	// Keeps adding characters until the closing tag </div> is hit
	while (rawHTML[pos] != '<') {
		name += rawHTML[pos];
		pos++;
	}

	fullName = name;
}
void Page::setSwipeBalance() {
	// Finding location of meal swipe balance
	int pos = rawHTML.find("Meal Plan Balance:")+26;
	// Gets the string holding the balance from the html
	string strSwipes = rawHTML.substr(pos, 2);

	// Checks how many digits the string is so stoi() doesn't throw error
	if (isdigit(strSwipes[1])) {
		swipeBalance = stoi(strSwipes);
		error = false;
	}
	else if (isdigit(strSwipes[0])) {
		swipeBalance = stoi(strSwipes.substr(0,1));
		error = false;
	}
	// If niether char is int, then we have gotten a wrong login page.   
	else {
		error = true;
	}
}
void Page::setMunchMoney() {
	int pos = rawHTML.find("<span class=\"label-munch-money\">Munch Money Balance:</span>")+59;
	string strMoney;
	// Check if rawHTML is correct log in page (see setSwipeBalance)
	// Otherwise stof would throw error. 
	if (!error) {
		while (rawHTML[pos] != '<') {
			// Removes unpredictable spaces and dollar sign
			if (rawHTML[pos] != ' ' && rawHTML[pos] != '$') {
				strMoney += rawHTML[pos];
			}
			pos++;
		}

		munchMoney = stof(strMoney);
	}
}
string Page::getName() {
	return fullName;
}
int Page::getSwipeBalance() {
	return swipeBalance;
}
float Page::getMunchMoney() {
	return munchMoney;
}
bool Page::getErrorStatus() {
	return error;
}