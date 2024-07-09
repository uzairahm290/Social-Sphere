#include<iostream>
#include"SocialApp.h"
using namespace std;

int main() {
	SocialNetworkApp app;
	app.readDataFromFile("data.txt");
	app.Run();
	return 0;
}

