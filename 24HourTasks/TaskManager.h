#pragma once
#include "Tracker.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
class TaskManager : public Tracker
{
private:
	//for time calc
	time_t now;
	struct tm buf;
	int calcHours(time_t &now, tm& buf);
	int calcDays(time_t &now, tm &buf);
	int calcWDay(time_t &now, tm &buf);
	int calcMonth(time_t& now, tm &buf);
	int calcYear(time_t &now, tm &buf);
public:
	int day;
	int month;
	int year;
	///updates from resetTasks and writeVec for oldday
	vector<string> yestTasks;

	void setTime(int pDay, int pMonth, int pYear) {
		day = pDay;
		month = pMonth;
		year = pYear;
	}

	void dispYestTasks(vector<string>& task);
	void displayTasks(vector<string> &task);
	void resetTasks(vector<string> &task);
	//for statistics
	int calcHours() {
		return calcHours(now, buf);
	}
	int calcDays() {
		return calcDays(now, buf);
	}
	int calcWDay() {
		return calcWDay(now, buf);
	}
	int calcMonth() {
		return calcMonth(now, buf);
	}
	int calcYear() {
		return calcYear(now, buf);
	}
	void showProdWeek();

	//constructor
	TaskManager() : Tracker(){
		day = 0;
		month = 0;
		year = 0;
		//calc time for buf
		now = time(0);
		localtime_s(&buf, &now);
	}
};

