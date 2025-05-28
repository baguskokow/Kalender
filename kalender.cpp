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
#include <cstdlib>
#include <unistd.h>
#include <argp.h>

void getDayOffData(int month, int year) {
	std::string monthString = std::to_string(month); // Change from int to string
	std::string yearString = std::to_string(year);   // Change from int to string

  std::string updateMonthVariable = "sed -i 's/^MONTH=.*/MONTH=" + monthString + "/' update-dayoff.sh"; // Command to update MONTH variable in update-dayoff.sh
  std::string updateYearVariable = "sed -i 's/^YEAR=.*/YEAR=" + yearString + "/' update-dayoff.sh"; // Command to update YEAR variable in update-dayoff.sh
	std::string runningScript = "bash update-dayoff.sh"; // Command to running script
	std::string cmd = updateMonthVariable + "&&" + updateYearVariable + "&&" + runningScript; // All command at here.

	system(cmd.c_str());
}

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

void help() {
	std::cout << "Usage : kalender -m [1-12] -y [xxxx]\n\n";
	std::cout << "Options : \n\n";
	std::cout << std::setw(15) << "-h = help\n";
	std::cout << std::setw(16) << "-m = month\n";
	std::cout << std::setw(16) << "-y = year\n\n";
	std::cout << "Example : kalender -m 5 -y 2025\n\n";
}

void version() {
	std::cout << "kalender v1.0.0\nCopyright (c) 2025 Bagus Koko Wibawanto\nLicense: MIT Licence\nRepository : https://github.com/baguskokow/Kalender.\n";
}

int main(int argc, char *argv[]) {
	int month; 
	int year; // 2025
	bool showHelp = false;

	int optionInput;
	while((optionInput = getopt(argc, argv, "m:y:h:v")) != -1) {
		switch(optionInput) {
			case 'h':
				showHelp = true;
				break;
			case 'm':
				month = std::atoi(optarg);
				break;
			case 'y':
				year = std::atoi(optarg);
				break;
			case 'v':
				version();
				break;
			default:
				help();
				break;
				return 1;
		}
	}
	
	if(showHelp == true) {
		help();
		showHelp = false;
		return 0;
	}	

	if(month == 0 || year == 0) {
		//help();
	} else {
		getDayOffData(month, year);
		readDataFromJson();
		getDaysOff();
		printCalendar(month, year);
	}
	return 0;
}
