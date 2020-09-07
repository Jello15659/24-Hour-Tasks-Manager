#pragma once
class Tracker {
private:
	static int dailyComp;
	static int dailyAdd;
	//updated every newDay
	//wiped on monday
	static int weeklyComp;
	static int weeklyAdd;
public:
	//for daily accumulation 
	void addDailyAdd() { dailyAdd++; }
	//called every time task completed
	void addDailyComp() { dailyComp++; }
	//deletes task
	void subAdd() {	dailyAdd--; }
	//added when new day begins
	void addWeeklyComp() { 
		weeklyComp += dailyComp; 
		dailyComp = 0;
	}
	//added when new day begins
	void addWeeklyAdd() { 
		weeklyAdd += dailyAdd; 
		//doesn't reset add because same tasks are reused
	}
	//getters
	int getDailyComp() {
		return dailyComp;
	}
	int getDailyAdd() {
		return dailyAdd;
	}
	int getWeeklyComp() {
		return weeklyComp;
	}
	int getWeeklyAdd() {
		return weeklyAdd;
	}
	//setters
	void setDailyComp(int p) {
		dailyComp = p;
	}
	void setDailyAdd(int p) {
		dailyAdd = p;
	}
	void setWeeklyComp(int p) {
		weeklyComp = p;
	}
	void setWeeklyAdd(int p) {
		weeklyAdd = p;
	}
	//restart week for stats
	void wipeWeekly() {
		weeklyComp = 0;
		weeklyAdd = 0;
	}
	//returns hours
	virtual int calcHours() = 0;
	//returns day
	virtual int calcDays() = 0;
	//returns days since sunday
	virtual int calcWDay() = 0;
	//month and year
	virtual int calcMonth() = 0;
	virtual int calcYear() = 0;
	//stats
	virtual void showProdWeek() = 0;
};
