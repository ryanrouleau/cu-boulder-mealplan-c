# curl/curl.h is required to run/compile.  Installed by default on OSX.

OBJS = User.o Page.o main.o
CPPFLAGS = -Wall -std=c++11 
PROG = mealplan
CC = g++

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lcurl

User.o: User.cpp User.h
	$(CC) $(CPPFLAGS) -c User.cpp

Page.o: Page.cpp Page.h
	$(CC) $(CPPFLAGS) -c Page.cpp

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	$(RM) $(PROG) $(OBJS)