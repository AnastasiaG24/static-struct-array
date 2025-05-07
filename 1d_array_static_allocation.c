#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char countryName[50];
	char capital[100];
	int cityCount;
	int foundationYear;
	int area;
	char presidentName[100];
} Country;

void readData(int count, Country* countries) {
	for (int i = 0; i < count; i++) {
		printf("Enter data for country %i:\n", i + 1);
		printf("Country name: ");
		scanf_s("%s", countries[i].countryName, (unsigned)_countof(countries[i].countryName));
		printf("Capital: ");
		scanf_s("%s", countries[i].capital, (unsigned)_countof(countries[i].capital));
		printf("Number of cities: ");
		scanf_s("%i", &countries[i].cityCount);
		printf("Year of foundation: ");
		scanf_s("%i", &countries[i].foundationYear);
		printf("Area: ");
		scanf_s("%i", &countries[i].area);
		printf("President's name: ");
		scanf_s("%s", countries[i].presidentName, (unsigned)_countof(countries[i].presidentName));
	}
}

void displayData(int count, Country* countries) {
	for (int i = 0; i < count; i++) {
		printf("\nCountry %i data:\n", i + 1);
		printf("Country name: %s\n", countries[i].countryName);
		printf("Capital: %s\n", countries[i].capital);
		printf("Number of cities: %i\n", countries[i].cityCount);
		printf("Year of foundation: %i\n", countries[i].foundationYear);
		printf("Area: %i\n", countries[i].area);
		printf("President's name: %s\n", countries[i].presidentName);
	}
}

void searchByNumber(int count, Country* countries, int value) {
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (countries[i].cityCount == value || countries[i].foundationYear == value || countries[i].area == value) {
			printf("Country at index %i matches value %i\n", i + 1, value);
			found = 1;
		}
	}
	if (!found) {
		printf("No country matches the entered value.\n");
	}
}

void searchByWord(int count, Country* countries, char text[100]) {
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(countries[i].countryName, text) == 0 ||
			strcmp(countries[i].capital, text) == 0 ||
			strcmp(countries[i].presidentName, text) == 0) {
			printf("Country at index %i matches value %s\n", i + 1, text);
			found = 1;
		}
	}
	if (!found) {
		printf("No country matches the entered value.\n");
	}
}

// Comparison functions for sorting
int compareCountryName(const void* a, const void* b) {
	return strcmp(((Country*)a)->countryName, ((Country*)b)->countryName);
}
int compareCapital(const void* a, const void* b) {
	return strcmp(((Country*)a)->capital, ((Country*)b)->capital);
}
int compareCityCount(const void* a, const void* b) {
	return ((Country*)a)->cityCount - ((Country*)b)->cityCount;
}
int compareFoundationYear(const void* a, const void* b) {
	return ((Country*)a)->foundationYear - ((Country*)b)->foundationYear;
}
int compareArea(const void* a, const void* b) {
	return ((Country*)a)->area - ((Country*)b)->area;
}
int comparePresidentName(const void* a, const void* b) {
	return strcmp(((Country*)a)->presidentName, ((Country*)b)->presidentName);
}

Country inputNewCountry() {
	Country newCountry;
	printf("Country name: ");
	scanf_s("%s", newCountry.countryName, (unsigned)_countof(newCountry.countryName));
	printf("Capital: ");
	scanf_s("%s", newCountry.capital, (unsigned)_countof(newCountry.capital));
	printf("Number of cities: ");
	scanf_s("%i", &newCountry.cityCount);
	printf("Year of foundation: ");
	scanf_s("%i", &newCountry.foundationYear);
	printf("Area: ");
	scanf_s("%i", &newCountry.area);
	printf("President's name: ");
	scanf_s("%s", newCountry.presidentName, (unsigned)_countof(newCountry.presidentName));
