/* #########################################
 *
 *      File: main.cpp
 *
 *      Author : Bagus Koko Wibawanto
 *
 * ########################################
 *
 * */

#include <iostream>
#include <iomanip>
#include <ctime>
#include "getdata.cpp"

int getDaysInMonth(int month, int year) {
	int February;

	if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		February = 29;
	} else {
		February = 28;
	}
	
	int days[12] = {31, February, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return days[month - 1];
}

int getDayStart(int month, int year) {
	std::tm dayStart = {0, 0, 0, 1, month - 1, year - 1900}; // 1 Mei 2025
	std::mktime(&dayStart);
	//int dayFrom = dayStart.tm_wday;

	return dayStart.tm_wday; 
}

void printCalendar(int month, int year) {
	std::string daysInWeek[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	std::string monthsInYear[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	int days = 1; // days 1
	int offDay = 17;
	int totalDay = getDaysInMonth(month, year);
	int dayFrom = getDayStart(month, year);
	std::string colorForeground = "\033[47m";
	std::string fontColorBlack = "\033[31m";
	std::string resetColor = "\033[0m";
	bool isHoliday = false;

	int totalSlot = dayFrom + totalDay;

	std::cout << std::setw(16) << monthsInYear[month - 1] << " " << year << "\n";

	for(std::string i : daysInWeek) {
		std::cout << std::setw(5) << std::left << i;
	}

	std::cout << "\n";

	getDaysOff();

	for(int i = 0; i < totalSlot; i++) {
		if(i < dayFrom) {
			std::cout << std::setw(5) << " ";
		} else {
			bool isHoliday = false;

			for(int j = 0; j < dayOffTotal; j++) {
				if(dayOff[j] == days) {
					std::cout << fontColorBlack;
					std::cout << std::setw(5) << days;
					std::cout << resetColor;
					isHoliday = true;
					break;
				}
			}
		
			if(!isHoliday) {
				std::cout << std::setw(5) << days;
			}			

			days++;
		}
		
		
		if((i + 1) % 7 == 0) {
			std::cout << "\n";
		}
	}

	std::cout << "\n\n";
	printDateOff();

}

int main() {
	int month = 5; 
	int year = 2025; // 2025

	readDataFromJson();
	getDaysOff();
	printCalendar(month, year);

	return 0;
}
