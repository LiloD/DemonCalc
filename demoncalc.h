#ifndef __DEMON_CALC_H__
#define __DEMON_CALC_H__

#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include "ui.h"

class DemonCalc;
class GameState;
struct Question;
struct Answer;


#define OPERATOR_NUMBER (2)

enum operations_t {ADD, MINUS}; 

struct Question{
	int d1;
	int d2;
	int ret;
	operations_t opt;

	void init(unsigned seed = 0){
		//init rand seed
		std::srand(seed);
		if(std::rand()%OPERATOR_NUMBER == 0)
			opt = ADD;
		else
			opt = MINUS;

		d1 = std::rand()%10;

		if(opt == ADD){
			d2 = std::rand()%(10-d1);
			ret = d1+d2;
		}else{
			d2 = std::rand()%(d1+1);
			ret = d1-d2;
		}
	}

	std::string str(){
		std::stringstream ss;
		ss<<d1<<((opt == ADD)?" + ":" - ")<<d2<<" = "<<"?";
		return ss.str();
	}
};

struct Answer{
	int ret;
	bool is_correct;
	void check(int r){
		is_correct = (r == ret);
	}
};

enum state_t {NOT_START, IN_PROGRESS, FINISHED};

class GameState{
public:
	GameState(int size, int st):cur(0), question_size(size), steps(st), questions(size), answers(size){
	}

	void reset(){
		if(steps < 1)
			steps = 1;

		state = NOT_START;
		cur = 0;
		for(int i = 0; i < question_size; ++i){
			questions[i].init(time(0)+i);
			answers[i].ret = questions[i].ret;
			answers[i].is_correct = false;
		}
	}


	void update(int in){
		if(state == NOT_START){
			state = IN_PROGRESS;
		}

		answers[cur++].check(in);

		if(cur == question_size){
			state = FINISHED;
		}
	}

	state_t getState(){
		return state;
	}

	int getSteps(){
		return steps;
	}

	int getQuestionSize(){
		return question_size;
	}

	void addSteps(){
		steps++;
		if(steps > question_size)
			steps--;

		reset();
	}

	void changeSteps(int val){
		if(val < 1)
			steps = 1;
		else
			steps = val;
		reset();
	}

	std::string getQuestionStr(int n){
		return questions[n].str();
	}

	std::vector<Answer> getRes(){
		return answers;
	}

private:
	state_t state;
	int cur;
	int question_size;
	int steps;
	std::vector<Question> questions;
	std::vector<Answer> answers;
};


class DemonCalc{
public:
	DemonCalc(int size = 25, int st = 1):game(size, st){}

	void init();

	void run();

	void showResult();

	void preRun();
private:
	GameState game;
};



#endif //__DEMON_CALC_H__