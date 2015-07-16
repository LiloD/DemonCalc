#include "demoncalc.h"

void DemonCalc::init(){
	game.reset();
	//init ncurses
	initscr();

	//show welcome msg
	printw("Welcome to Demon Calculation!\n");
	printw("You will start at level %d\n", game.getSteps());
	printw("Press A to begin, press anything else to exit...\n");
	refresh();

	int ch = getchar();
	switch(ch){
		case 'a':
			preRun();
			run();
			break;
		default:
			getchar();
			endwin();
	}
}

void DemonCalc::run(){
	int i  = game.getSteps();
	while(true){
		if(game.getState() == FINISHED){
			showResult();

			printw("\nPress A to enter the next level, anything else to exit: ");
			refresh();
			int ch = getchar();
			if(ch == 'a'){
				// game.changeSteps(game.getSteps()+1);
				game.addSteps();
				preRun();
				i = game.getSteps();
			}else{
				break;		
			}
		}

		clear();
		std::stringstream ss;
		std::string q;
		if(i < game.getQuestionSize()){
			q = game.getQuestionStr(i);
		}else{
			q = "? + ? = ?";
		}
		ss<<"No."<<(i+1)<<": "<<q<<std::endl;
		mvscrolltxt(0, 0, ss.str());
		ss.flush();

		mvprintw(1,0, "Please enter the result of Question No.%d: ", (i-game.getSteps()+1));
		refresh();

		int input;
		int r, c;
		getyx(stdscr, r, c);
		while((input = getchar())){
			if(input <= '9' && input >= '0'){
				break;
			}
			mvprintw(r+1, 0, "Please enter valid input : 0-9");
			move(r, c);
			refresh();
		}
		game.update(input-'0');
		i++;
	}


	getchar();
	endwin();
}

void DemonCalc::showResult(){
	clear();
	std::vector<Answer> res = game.getRes();
	mvscrolltxt(0,0, "The final result is......");

	for(int i = 0; i < res.size(); i++){
		int r = i/5;
		int c = i%5;
		mvaddstr(r+1, c*2, res[i].is_correct?"O ":"X ");
		napms(200);
		refresh();
	}
}

void DemonCalc::preRun(){
	clear();
	printw("Game Start! The current level is %d\n", game.getSteps());
	printw("Please remeber the results!!");
	refresh();
	napms(1000);
	clear();

	for(int i = 0; i < game.getSteps(); ++i){
		std::string s = game.getQuestionStr(i);
		std::stringstream ss;
		ss<<"No."<<(i+1)<<": "<<s;

		mvscrolltxt(0, 0, ss.str());
		napms(1000);

		printw("\ncount down:");
		int r, c;
		getyx(stdscr, r, c);

		for(int i = 0; i < 5; i++){
			mvaddch(r, c+1, '0'+(5-i));
			refresh();
			napms(1000);
		}

		mvaddch(r, c+1, ' ');
		refresh();
	}
}

int main(int argc, char *argv[]){
	DemonCalc game(15, 1);
	game.init();
	return 0;
}



