// (User) class for handeling username and password
#include <iostream>
#include "User.h"

using namespace std;

User::User() {
	setUsername();
	setPassword();
}
void User::setUsername() {
	cout << "Enter IdentiKey: ";
	cin >> username;
}
void User::setPassword() {
	password = getpass("Enter Password: ");
}
string User::getUsername() {
	return username;
}
string User::getPassword() {
	return password;
}