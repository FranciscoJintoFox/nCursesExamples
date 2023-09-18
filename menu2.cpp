#include<ncurses.h>
#include<fstream>
#include<iostream>

using namespace std;

int main(){

	//Setup input file
	ifstream menuFile;
	menuFile.open("MenuOptions.txt");
	if(!menuFile){
		cout << "Unable to Open MenuOptions.txt" << endl;
		exit(1);
	}

	//Get number of file options
	int count = 0;
	string menuOption;
	while(getline(menuFile, menuOption)){
		count++;
	}

	//Reset File Pointer back to beginning of file
	menuFile.clear();
	menuFile.seekg(0, ios::beg);

	//Put menu options in array
	string *menuOptions = new string[count];
	for(int i=0; i<count; i++){
		getline(menuFile, menuOption);
		menuOptions[i] = menuOption;
	}

	//Set up nCurses screen
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE); //Lets us hijack the arrow keys and keypad

	//Open interactive Menu
	int input = 0; //To store User Input

	while(input != 'q'){ //Add an input that quits
		clear(); //Try to figure out why this should go here

		//Write menu to frame buffer
		mvprintw(1,12, "Main Menu");
		for(int i=0; i<count; i++){
			mvprintw(i+2, 15, "%s", menuOptions[i].c_str());
		}
		mvprintw(30, 100, "%i", input); //Debug: write input to frame buffer

		//Print frame buffer to screen
		refresh();

		//Get user input
		input = getch();
	   
}

	endwin();
	delete [] menuOptions;
}
