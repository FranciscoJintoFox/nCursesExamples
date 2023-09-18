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
	int maxOptionLength = 0;
	string menuOption;
	while(getline(menuFile, menuOption)){
		count++;
		if(menuOption.length() > maxOptionLength)
			maxOptionLength = menuOption.length();
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
	int selected = 1; //To store the menu 'state'
	
	while(input != 'q'){ //Add an input that quits
		clear(); //Try to figure out why this should go here

		//Write menu to frame buffer
		mvprintw(1,12, "Main Menu");
		for(int i=0; i<count; i++){
			mvprintw(i+2, 15, "%s", menuOptions[i].c_str());
		}
		if(selected > 0 && selected < (count+1))
			mvchgat(selected+1, 15, maxOptionLength, A_STANDOUT, 1, NULL);
		mvprintw(30, 100, "%i", input); //Debug: write input to frame buffer

		//Print frame buffer to screen
		refresh();

		//Get user input
		input = getch();
		//Change selected option; note:(0,0) is top left
		if(input == KEY_DOWN && selected < (count)) selected++;
		if(input == KEY_UP && selected > 1) selected--;
	   
	}

	endwin();
	delete [] menuOptions;
}
