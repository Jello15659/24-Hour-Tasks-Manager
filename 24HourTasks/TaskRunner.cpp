/**CIS 221 Final
* Author: Justin Liu
* Project Purpose: Program to store and update daily tasks
* Input:  This program accepts inputs for menu and edits
* Desired Output:  Lists, Add, Completed, Delete, Stats
* Variables and Classes: Classes: Tracker.h, TaskManager.h, TaskManager.cpp, Tracker.cpp; Variables: fstream objects, vector, TaskManager, ints
* Formulas:  newDay, dispYestTasks, dispCurTasks, addTasks, completeTask, deleteTask, taskMenu, statsMenu, writeVec, writeFile
* Description of the main algorithm: <iostream> cout is used to display the output

* 4/29/2020
**/


#pragma once
#include <vector>
#include "TaskManager.h"
#include <sstream>
#include <fstream>

//main task manager fxions
void newDay(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void dispYestTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void dispCurTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void addTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void completeTask(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void deleteTask(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);
void taskMenu(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);

//stats funcs
void statsMenu(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1);

//take from and write to file
void writeVec(fstream& in, vector<string>& task, int& taskNum, TaskManager& t1);
void writeFile(fstream& out, vector<string>& task, int& taskNum, TaskManager& t1);

//what hour to reset the day at (5am)
const int SET_RESET = 5;

int main() {
	fstream taskWriter("TaskManager.txt", ios::in);
	TaskManager t1;
	vector<string> tasks;
	int taskNum = 1;
	int pMenu = 0;
	writeVec(taskWriter, tasks, taskNum, t1);
	newDay(pMenu, tasks, taskNum, t1);
	fstream out("TaskManager.txt", ios::out);
	writeFile(out, tasks, taskNum, t1);
}

void newDay(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	//check if newday (day > prevDay && hours > setReset)
	bool nDay = false;
	if ((t1.calcDays() != t1.day || t1.calcMonth() != t1.month || t1.calcYear() != t1.year) && t1.calcHours() > SET_RESET) {
		nDay = true;
		t1.setTime(t1.calcDays(), t1.calcMonth(), t1.calcYear());
	}
	if (nDay) {
		//reset week at monday
		if (t1.calcWDay() == 1) {
			t1.wipeWeekly();
		}
		else {
			//adds
			t1.addWeeklyAdd();
			t1.addWeeklyComp();
		}
		cout << "IT'S A NEW DAY" << endl;
		dispYestTasks(pMenu, task, taskNum, t1);
	}
	else {
		cout << "WELCOME BACK" << endl;
		dispCurTasks(pMenu, task, taskNum, t1);
	}
}

void dispYestTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	//display tasks
	if (task.size() != 0) {
		//reset and display
		t1.resetTasks(task);
		t1.dispYestTasks(task);
	}
	//tasks menu
	taskMenu(pMenu, task, taskNum, t1);
}
void dispCurTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	//display tasks
	if (task.size() != 0) {
		t1.displayTasks(task);
	}
	//tasks menu
	taskMenu(pMenu, task, taskNum, t1);
}

void addTasks(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	//add task
	t1.addDailyAdd();
	string taskName;
	string taskEntry = "";
	cout << "What is the name of the task? ";
	cin.ignore();
	getline(cin, taskName);
	taskEntry += to_string(taskNum);
	taskEntry = taskEntry + ": " + taskName;
	task.push_back(taskEntry);
	taskNum++;
	//view tasks again
	t1.displayTasks(task);
	taskMenu(pMenu, task, taskNum, t1);
}
void completeTask(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	//complete task
	t1.addDailyComp();
	int compNum;
	bool nonValid = true;
	string complete = "**COMPLETED ";
	//check
	while (nonValid) {
		cout << "Enter the number of the task you wish to complete: ";
		cin.ignore();
		cin >> compNum;
		if (compNum > 0 && compNum <= task.size()) {
			nonValid = false;
		}
		else {
			cout << "This number doesn't seem to be in the list. Please try again." << endl;
		}
	}
	//check if already completed
	if (task[-1 + compNum].substr(0, 12) == complete) {
		cout << "Already Completed!!" << endl;
	}
	else {
		complete += task[-1 + compNum];
		task[-1 + compNum] = complete;
	}
	//view tasks again
	t1.displayTasks(task);
	taskMenu(pMenu, task, taskNum, t1);
}

void deleteTask(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	int compNum;
	bool nonValid = true;
	string complete = "**COMPLETED ";
	string temp;
	//check
	while (nonValid) {
		cout << "Enter the number of the task you wish to delete: ";
		cin.ignore();
		cin >> compNum;
		if (compNum > 0 && compNum <= task.size()) {
			nonValid = false;
		}
		else if (compNum == -1) {
			break;
		}
		else {
			cout << "This number doesn't seem to be in the list. Please try again." << endl;
		}
	}
	//delete
	task.erase(task.begin() + compNum - 1);
	t1.subAdd();
	//adjust taskNum
	taskNum--;
	//fix everything after
	for (int i = compNum - 1; i < task.size(); i++) {
		if (task[i].substr(0, 12) == complete) {
			//change number
			task[i] = task[i].substr(0, 12) + to_string((stoi(task[i].substr(12, 1)) - 1)) + task[i].substr(13);
		}
		else {
			task[i] = to_string((stoi(task[i].substr(0, 1)) - 1)) + task[i].substr(1);
		}
	}
	//view tasks again
	t1.displayTasks(task);
	taskMenu(pMenu, task, taskNum, t1);
}
void taskMenu(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	while (pMenu != -1) {
		cout << "1: Add Task" << endl;
		cout << "2: Complete Task " << endl;
		cout << "3: Display Tasks " << endl;
		cout << "4: Delete Task" << endl;
		cout << "5: See stats" << endl;
		cout << "-1: Exit" << endl;
		cout << "USER: ";
		cin >> pMenu;
		switch (pMenu) {
		case 1:
			addTasks(pMenu, task, taskNum, t1);
			break;
		case 2:
			completeTask(pMenu, task, taskNum, t1);
			break;
		case 3:
			dispCurTasks(pMenu, task, taskNum, t1);
			break;
		case 4:
			deleteTask(pMenu, task, taskNum, t1);
			break;
		case 5:
			statsMenu(pMenu, task, taskNum, t1);
			break;
		case -1:
			break;
		default:
			cout << "Error: Value not accepted" << endl;
		}
	}
}

void statsMenu(int& pMenu, vector<string>& task, int& taskNum, TaskManager& t1) {
	while (pMenu != -1) {
		cout << "1: Show Yesterday's Incomplete Tasks" << endl;
		cout << "2: Show weekly stats" << endl;
		cout << "-1: Exit" << endl;
		cout << "USER: ";
		cin.ignore();
		cin >> pMenu;
		switch (pMenu) {
		case 1:
			t1.dispYestTasks(task);
			break;
		case 2:
			t1.showProdWeek();
			break;
		case -1:
			break;
		default:
			cout << "Error: Value not accepted" << endl;
		}
	}
}

void writeVec(fstream& in, vector<string>& task, int& taskNum, TaskManager& t1) {
	//take day, month, year from first line of txt
	int day, month, year, weeklyAdd, weeklyComp, dailyAdd, dailyComp;
	string line;
	in >> day;
	in >> month;
	in >> year;
	in >> weeklyAdd;
	in >> weeklyComp;
	in >> dailyAdd;
	in >> dailyComp;
	in.seekg(2, ios::cur);
	//only goes through if file has contents
	if (day > 0) {
		t1.setTime(day, month, year);
		t1.setDailyAdd(dailyAdd);
		t1.setDailyComp(dailyComp);
		t1.setWeeklyAdd(weeklyAdd);
		t1.setWeeklyComp(weeklyComp);
		//take tasks
		taskNum = 1;
		while (getline(in, line)) {
			taskNum++;
			task.push_back(line);
		}
	}
	else {
		t1.setTime(0, 0, 0);
	}

	in.close();
	//for yesterday vector
	fstream yestIn("YestIncTask.txt", ios::in);
	while (getline(yestIn, line)) {
		t1.yestTasks.push_back(line);

	}
}

void writeFile(fstream& out, vector<string>& task, int& taskNum, TaskManager& t1) {
	//write date to first line
	out << t1.day << " " << t1.month << " " << t1.year << " " << t1.getWeeklyAdd() << " " << t1.getWeeklyComp() << " "
		<< t1.getDailyAdd() << " " << t1.getDailyComp() << "\n";
	//write tasks
	string line;
	for (int i = 0; i < task.size(); i++) {
		line = task[i];
		if (line.substr(0, 11) == "**COMPLETED") {

		}
		else {
			out << line << endl;
		}
	}
	for (int i = 0; i < task.size(); i++) {
		line = task[i];
		if (line.substr(0, 11) == "**COMPLETED") {
			out << line << endl;
		}
	}
	out.close();
	//save incomplete for later in the day (reset at new day)
	fstream yestOut("YestIncTask.txt", ios::out);
	for (int i = 0; i < t1.yestTasks.size(); i++) {
		line = t1.yestTasks[i];
		yestOut << line << endl;
	}
	yestOut.close();
}