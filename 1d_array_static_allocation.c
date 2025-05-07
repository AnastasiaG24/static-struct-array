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
	return newCountry;
}

void insertAtEnd(Country** countries, int* count, Country newCountry) {
	(*count)++;
	Country* temp = realloc(*countries, (*count) * sizeof(Country));
	if (!temp) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	*countries = temp;
	(*countries)[*count - 1] = newCountry;
}

void insertAtBeginning(Country** countries, int* count, Country newCountry) {
	(*count)++;
	Country* temp = realloc(*countries, (*count) * sizeof(Country));
	if (!temp) {
		printf("Memory reallocation failed.\n");
		exit(1);
	}
	*countries = temp;
	for (int i = *count - 1; i > 0; i--) {
		(*countries)[i] = (*countries)[i - 1];
	}
	(*countries)[0] = newCountry;
}

void insertAtPosition(Country** countries, int* count, Country newCountry, int position) {
	if (position < 0 || position > *count) {
		printf("Invalid position.\n");
		return;
	}
	(*count)++;
	Country* temp = realloc(*countries, (*count) * sizeof(Country));
	if (!temp) {
		printf("Memory reallocation failed.\n");
		exit(1);
	}
	*countries = temp;
	for (int i = *count - 1; i > position; i--) {
		(*countries)[i] = (*countries)[i - 1];
	}
	(*countries)[position] = newCountry;
}

void deleteAtPosition(Country** countries, int* count, int position) {
	for (int i = position - 1; i < *count - 1; i++) {
		(*countries)[i] = (*countries)[i + 1];
	}
	(*count)--;
	Country* temp = realloc(*countries, (*count) * sizeof(Country));
	if (!temp && *count > 0) {
		printf("Memory reallocation failed after deletion.\n");
		exit(1);
	}
	*countries = temp;
	printf("Country at position %i has been deleted.\n", position);
}

int main() {
	int count, menuOption, searchOption, sortOption;
	char name[100], capital[100], president[100];
	int cities, year, area;

	printf("Enter number of countries: ");
	scanf_s("%i", &count);

	Country* countries = (Country*)malloc(count * sizeof(Country));
	if (!countries) {
		printf("Memory allocation error.\n");
		return 1;
	}

	readData(count, countries);
	displayData(count, countries);

	printf("\nMenu:\n");
	printf("1 - Search by field\n");
	printf("2 - Sort by field\n");
	printf("3 - Insert at end\n");
	printf("4 - Insert at beginning\n");
	printf("5 - Insert at position\n");
	printf("6 - Delete by position\n");
	printf("Choose an option: ");
	scanf_s("%i", &menuOption);

	switch (menuOption) {
	case 1:
		printf("Search by:\n1-Name 2-Capital 3-Cities 4-Year 5-Area 6-President\nChoose: ");
		scanf_s("%i", &searchOption);
		switch (searchOption) {
		case 1:
			printf("Enter country name: ");
			scanf_s("%s", name, (unsigned)sizeof(name));
			searchByWord(count, countries, name); break;
		case 2:
			printf("Enter capital: ");
			scanf_s("%s", capital, (unsigned)sizeof(capital));
			searchByWord(count, countries, capital); break;
		case 3:
			printf("Enter number of cities: ");
			scanf_s("%i", &cities);
			searchByNumber(count, countries, cities); break;
		case 4:
			printf("Enter foundation year: ");
			scanf_s("%i", &year);
			searchByNumber(count, countries, year); break;
		case 5:
			printf("Enter area: ");
			scanf_s("%i", &area);
			searchByNumber(count, countries, area); break;
		case 6:
			printf("Enter president's name: ");
			scanf_s("%s", president, (unsigned)sizeof(president));
			searchByWord(count, countries, president); break;
		} break;

	case 2:
		printf("Sort by:\n1-Name 2-Capital 3-Cities 4-Year 5-Area 6-President\nChoose: ");
		scanf_s("%i", &sortOption);
		switch (sortOption) {
		case 1: qsort(countries, count, sizeof(Country), compareCountryName); break;
		case 2: qsort(countries, count, sizeof(Country), compareCapital); break;
		case 3: qsort(countries, count, sizeof(Country), compareCityCount); break;
		case 4: qsort(countries, count, sizeof(Country), compareFoundationYear); break;
		case 5: qsort(countries, count, sizeof(Country), compareArea); break;
		case 6: qsort(countries, count, sizeof(Country), comparePresidentName); break;
		}
		printf("\nSorted list:\n");
		displayData(count, countries);
		break;

	case 3:
		insertAtEnd(&countries, &count, inputNewCountry());
		displayData(count, countries);
		break;

	case 4:
		insertAtBeginning(&countries, &count, inputNewCountry());
		displayData(count, countries);
		break;

	case 5: {
		int pos;
		printf("Enter position: ");
		scanf_s("%i", &pos);
		if (pos >= 0 && pos <= count) {
			insertAtPosition(&countries, &count, inputNewCountry(), pos);
			displayData(count, countries);
		}
		else {
			printf("Invalid position.\n");
		}
		break;
	}

	case 6: {
		int pos;
		printf("Enter position to delete: ");
		scanf_s("%i", &pos);
		if (pos >= 1 && pos <= count) {
			deleteAtPosition(&countries, &count, pos);
			displayData(count, countries);
		}
		else {
			printf("Invalid position.\n");
		}
		break;
	}
	}

	free(countries);
	return 0;
}
