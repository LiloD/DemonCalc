#ifndef __UI_H__
#define __UI_H__

#include <ncurses.h>
#include <string>

void mvscrolltxt(int row, int col, std::string &s);

void mvscrolltxt(int row, int col, std::string s){
	move(row, col);
	for(int i = 0; i < s.size(); i++){
		addch(s[i]);
		refresh();
		napms(100);
	}
}

#endif //__UI_H__