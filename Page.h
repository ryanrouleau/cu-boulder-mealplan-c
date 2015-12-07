// Header for Page class (handles raw HTML source)
#ifndef PAGE_H
#define PAGE_H

class Page {
	private:
		std::string rawHTML;
		std:: string fullName;
		int swipeBalance;
		float munchMoney;
		bool error;
	public:
		Page(std::string HTML);
		void setName();
		void setSwipeBalance();
		void setMunchMoney();
		std::string getName();
		int getSwipeBalance();
		float getMunchMoney();
		bool getErrorStatus();
};

#endif