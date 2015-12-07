// User class header (handles username and password)
#ifndef USER_H
#define USER_H

class User {
	private: 
		std::string username;
		std::string password;
	public:
		User();
		void setUsername();
		void setPassword();
		std::string getUsername();
		std::string getPassword();	
};

#endif