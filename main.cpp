// Driver program. 
#include <iostream>
#include <curl/curl.h> // Library for logging in and grabbing HTML
#include "User.h"
#include "Page.h"

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp); 
string loginAndGetHtml(string username, string password);

int main() {
	string fullName;
	int swipeBalance;
	float munchMoney;
	string rawHTML;

	// Error returns true if there is a login error
	bool error;
	do {
		User user = User();
		rawHTML = loginAndGetHtml(user.getUsername(), user.getPassword());
		Page page = Page(rawHTML);

		fullName = page.getName();
		swipeBalance = page.getSwipeBalance();
		munchMoney = page.getMunchMoney();
		error = page.getErrorStatus();

		// If there is a login error, this won't print
		if (!error) {
			cout << "Meal Plan Balances for: " << fullName << endl;
			cout << "You have " << swipeBalance << " meals left this week." << endl;
			cout << "You have $" << munchMoney << " of munch money left." << endl;
		}
		else {
			cout << "~~~~~~~~~ Wrong Username/Password combination! Try again. ~~~~~~~~~\n" << endl;
		}
	}
	while (error);

	return 0;
}

// This function is from user fa7d0 on stackoverflow
// Prevents cURL from printing HTML to terminal
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string loginAndGetHtml(string username, string password) {
	string postData = 
		"name="+username+
		"&pass="+password+
		"&form_build_id=form-s7kSHZ9fLpU7xXn3ZxDC79ZfEcAkU0168N161pNZRu8"
		"&form_id=user_login"
		"&op=Log in";

	cout << "\nLogging in and fetching data from oncampus.colorado.edu...\n" << endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//																							   //
	// This block of code is a modified version of https://www.hackthissite.org/articles/read/1078 //
	//																							   //
	/////////////////////////////////////////////////////////////////////////////////////////////////
	curl_global_init( CURL_GLOBAL_ALL );
	CURL * myHandle = curl_easy_init ( );
	string readBuffer; // <------- added from original for storing html in string

	// Set up a couple initial paramaters that we will not need to mofiy later.
	curl_easy_setopt(myHandle, CURLOPT_USERAGENT, "Mozilla/4.0");
	curl_easy_setopt(myHandle, CURLOPT_AUTOREFERER, 1 );
	curl_easy_setopt(myHandle, CURLOPT_FOLLOWLOCATION, 1 );
	curl_easy_setopt(myHandle, CURLOPT_COOKIEFILE, "");

	// Visit the login page once to obtain a PHPSESSID cookie
	curl_easy_setopt(myHandle, CURLOPT_URL, 
		"https://oncampus.colorado.edu/user/login"); // <------- This URL has been changed from original
	curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_perform( myHandle );


	// Now, can actually login. First we forge the HTTP referer field, or HTS will deny the login
	curl_easy_setopt(myHandle, CURLOPT_REFERER, 
		"https://oncampus.colorado.edu/user/login"); // <------- This URL has been changed from original
	// Next we tell LibCurl what HTTP POST data to submit
	char *data=&postData[0]; // <------ &postData[0] has been changed from a hardcoded string in original
	curl_easy_setopt(myHandle, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteCallback); // <------- added from original to store html in string
	curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, &readBuffer); // <--------added from original to store html in string

	curl_easy_perform( myHandle );
	curl_easy_cleanup( myHandle );
	/////////////////////////////////////////////////////////////////
	//															   //
	// End of modified code block, all other code is created by me //
	//															   //
	/////////////////////////////////////////////////////////////////
	return readBuffer; // readBuffer is HTML string
}

