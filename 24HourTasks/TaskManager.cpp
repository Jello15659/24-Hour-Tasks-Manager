#include "TaskManager.h"
#include <ctime>
void TaskManager::dispYestTasks(vector<string>& task) {
	cout << "===================================================" << endl;
	cout << "Yesterday's Incomplete Tasks";
	if (yestTasks.size() == 0) {
		cout << ": EMPTY" << endl;
	}
	else {
		cout << endl;
	}
	for (int i = 0; i < yestTasks.size(); i++) {
		cout << yestTasks[i] << endl;
	}
	cout << "===================================================" << endl;

}
void TaskManager::displayTasks(vector<string>& task) {
	cout << "===================================================" << endl;
	cout << "Tasks List" << endl;
	for (auto it = task.begin(); it != task.end(); it++) {
		cout << *it << endl;
	}
	cout << "===================================================" << endl;
}
void TaskManager::resetTasks(vector<string>& task) {
	string check = "**COMPLETED";
	string temp;
	//cleares from yestVector
	yestTasks.clear();
	//removes completed marker
	for (auto it = task.begin(); it != task.end(); it++) {
		temp = *it;
		if (temp.substr(0, 11) == check) {
			(*it).erase(0, 12);
		}
		else {
			//pushes incomplete tasks
			yestTasks.push_back(*it);
		}
	}
	//sort tasks
	//bubble sort based on number
	for (int i = 0; i < task.size() - 1; i++){
		// Last i elements are already in place  
		for (int j = 0; j < task.size() - i - 1; j++) {
			//compare number
			if (stoi(task[j].substr(0, 1)) > stoi(task[j+1].substr(0, 1))) {
				temp = task[j];
				task[j] = task[j + 1];
				task[j + 1] = temp;
			}
		}
	}
}
int TaskManager::calcHours(time_t& now, tm& buf) {
	return (&buf)->tm_hour;
}
int TaskManager::calcDays(time_t& now, tm& buf) {
	return (&buf)->tm_mday;
}
int TaskManager::calcWDay(time_t& now, tm& buf) {
	return (&buf)->tm_wday;
}
int TaskManager::calcMonth(time_t& now, tm& buf) {
	return 1 + (&buf)->tm_mon;
}
int TaskManager::calcYear(time_t& now, tm& buf) {
	return 1900 + (&buf)->tm_year;
}

void TaskManager::showProdWeek() {
	//stop divide by 0 error
	if (getWeeklyAdd() > 0) {
		cout << getWeeklyComp() << " / " << getWeeklyAdd() << " Decimal: " << (double) getWeeklyComp() / getWeeklyAdd() << endl;
	}
	else {
		cout << "There appears to be no information here" << endl;
	}
}