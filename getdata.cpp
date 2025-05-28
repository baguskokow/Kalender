/*
 * =====================================================================================
 *
 *       Filename:  getdata.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/28/2025 10:14:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
using json = nlohmann::json;

std::string getDateFromJson;
std::string getDescribe;
std::string monthOffString;
std::string dayOffString;
int dayOffTotal;
int monthOff;
int dayOff[10];
json dayoff;

void readDataFromJson() {
	std::ifstream readDayOff("dayoff.json", std::ifstream::in);
	readDayOff >> dayoff;

	dayOffTotal = dayoff.size();
}

void getDaysOff() {
	for(int i = 0; i < dayOffTotal; i++) {
		getDateFromJson = dayoff[i]["tanggal"];
		//monthOffString = getDateFromJson.substr(5,2);
		dayOffString = getDateFromJson.substr(8,2);
		//monthOff = std::stoi(monthOffString);
		dayOff[i] = std::stoi(dayOffString);
	}
}

void getDescribeDaysOff() {
	for(int i = 0; i < dayOffTotal; i++) {
		getDescribe = dayoff[i]["keterangan"];
	}
}

void printDateOff() {
	readDataFromJson();

//	for(int i = 0; i < dayOffTotal; i++) {
//		getDateFromJson = dayoff[i]["tanggal"];
//		getDescribe = dayoff[i]["keterangan"];
//		monthOffString = getDateFromJson.substr(5,2);
//		dayOffString = getDateFromJson.substr(8,2);
//		monthOff = std::stoi(monthOffString);
//		dayOff[i] = std::stoi(dayOffString);
//		std::cout << dayOff[i] << ": " << getDescribe << "\n";
//	}
		
	for(int i = 0; i < dayOffTotal; i++) {
		getDescribe = dayoff[i]["keterangan"];
		std::cout << dayOff[i] << ": " << getDescribe << "\n";
	}

}
