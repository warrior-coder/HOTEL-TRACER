#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <conio.h>

using namespace std;

// +-----------------------------------------------------------------+
// 
// HOTEL INFO

struct Hotel_Room
{
	// readable data
	char site[20];
	char city[20];
	char hotel_name[20];
	char hotel_adress[30];
	char room_class[20];
	int guests;
	int price;
	int reserved;

	// non-readable data
	bool FILTER;
};

struct Hotel_Filter
{
	char site[20];
	char city[20];
	char hotel_name[20];
	char hotel_adress[30];
	char room_class[20];
	int guests;
	int price_min, price_max;
	int reserved;
}FILTER;

// +-----------------------------------------------------------------+
// 
// DOUBLY LINKED LIST

struct Node
{
	Hotel_Room room;
	Node* next;
	Node* prev;
};

struct List
{
	Node* begin = nullptr;
	Node* end = nullptr;

	void push_back(Hotel_Room room)
	{
		Node* ptr = new Node;

		ptr->room = room;
		ptr->next = nullptr;

		if (begin == nullptr)
		{
			begin = end = ptr;
			ptr->prev = nullptr;
		}
		else
		{
			end->next = ptr;
			ptr->prev = end;
			end = ptr;
		}
	}

	void show(bool filter = false)
	{
		Node* ptr = begin;

		int i = 1;
		cout << "[N] "
			<< setw(15) << "[site]"
			<< setw(15) << "[city]"
			<< setw(15) << "[name]"
			<< setw(20) << "[adress]"
			<< setw(15) << "[class]"
			<< setw(10) << "[guests]"
			<< setw(10) << "[price]"
			<< setw(8) << "[res]" << endl;
		while (ptr)
		{
			if (!filter || ptr->room.FILTER == filter)
			{
				cout <<
				setw(2) << i << ":" <<
				setw(15) << ptr->room.site <<
				setw(15) << ptr->room.city <<
				setw(15) << ptr->room.hotel_name <<
				setw(20) << ptr->room.hotel_adress <<
				setw(15) << ptr->room.room_class <<
				setw(10) << ptr->room.guests <<
				setw(10) << ptr->room.price <<
				setw(8) << (ptr->room.reserved == 1 ? "yes" : "no") <<
				endl;
				
				i++;
			}
			ptr = ptr->next;
		}
	}

	void clear()
	{
		Node* ptr;

		while (begin)
		{
			ptr = begin;
			begin = begin->next;
			delete ptr;
		}
		begin = nullptr;
	}
} rooms;

// +-----------------------------------------------------------------+
// 
// PROTOTYPES

int menu();
void menu_after_search();

void read_data_from_file(const char*);
void write_data_to_file(const char*);

void filter_site();
void filter_city();
void filter_hotel_name();
void filter_hotel_adress();
void filter_room_class();
void filter_guests();
void filter_price();
void filter_reserved();
void filter_clear();

void search();

// +-----------------------------------------------------------------+
// 
// MAIN

int main()
{
	// Set up
	read_data_from_file("AllHotels");
	read_data_from_file("HotelQuest");
	read_data_from_file("hotels");
	read_data_from_file("opodo");
	read_data_from_file("orbitz");
	read_data_from_file("TravelWeb");
	read_data_from_file("TravelWorm");

	strcpy_s(FILTER.site, "0");
	strcpy_s(FILTER.city, "0");
	strcpy_s(FILTER.hotel_name, "0");
	strcpy_s(FILTER.hotel_adress, "0");
	strcpy_s(FILTER.room_class, "0");
	FILTER.guests = 0;
	FILTER.price_min = 0;
	FILTER.price_max = 0;
	FILTER.reserved = 0;

	// App cycle
	while (true)
	{
		switch (menu())
		{
			case '1': filter_site(); break;
			case '2': filter_city(); break;
			case '3': filter_hotel_name(); break;
			case '4': filter_hotel_adress(); break;
			case '5': filter_room_class(); break;
			case '6': filter_guests(); break;
			case '7': filter_price(); break;
			case '8': filter_reserved(); break;
			case '0': filter_clear(); break;
			case 's': search(); break;
			default: rooms.clear(); return 0;
		}

		cout << endl;
		system("pause");
		system("cls");
	}
}

int menu()
{
	// Title
	cout << "+-------HOTEL-TRACER-------+" << endl;
	cout << "          Filters:      " << endl;

	// 1. Site
	cout << "  1 - Site         ";
	if (FILTER.site[0] != '0') cout << FILTER.site << endl;
	else cout << "[___]" << endl;

	// 2. City
	cout << "  2 - City         ";
	if (FILTER.city[0] != '0') cout << FILTER.city << endl;
	else cout << "[___]" << endl;

	// 3. Hotel Name
	cout << "  3 - Hotel Name   ";
	if (FILTER.hotel_name[0] != '0') cout << FILTER.hotel_name << endl;
	else cout << "[___]" << endl;

	// 4. Hotel adress
	cout << "  4 - Hotel adress ";
	if (FILTER.hotel_adress[0] != '0') cout << FILTER.hotel_adress << endl;
	else cout << "[___]" << endl;

	// 5. Room class
	cout << "  5 - Room class   ";
	if (FILTER.room_class[0] != '0') cout << FILTER.room_class << endl;
	else cout << "[___]" << endl;

	// 6. Guests
	cout << "  6 - Guests       ";
	if (FILTER.guests) cout << FILTER.guests << endl;
	else cout << "[___]" << endl;

	// 7. Price
	cout << "  7 - Price        ";
	if (FILTER.price_min == -1) cout << "lowest" << endl;
	else if (FILTER.price_max == -1) cout << "highest" << endl;
	else if (FILTER.price_min > 0 || FILTER.price_max > 0)
	{
		if (FILTER.price_min > 0) cout << "from " << FILTER.price_min << " ";
		if (FILTER.price_max > 0) cout << "to " << FILTER.price_max;
		cout << endl;
	}
	else cout << "[___]" << endl;

	// 8. Reserved
	cout << "  8 - Reserved     ";
	if (FILTER.reserved == 1) cout << "yes" << endl;
	else if (FILTER.reserved == -1) cout << "no" << endl;
	else cout << "[___]" << endl;
	
	// Actions
	cout << endl;
	cout << "          Actions:      " << endl;
	cout << "  0 - Clear all filters" << endl;
	cout << "  s - Search" << endl;
	cout << "  e - Exit" << endl;
	cout << "+--------------------------+" << endl;

	char menu;
	cout << ">";
	cin >> menu;
	cout << endl;
	return menu;
}

// +-----------------------------------------------------------------+
// 
// SET FILTERS

void filter_site()
{
	cout << "Choose site:" << endl;
	cout << "1 - AllHotels" << endl;
	cout << "2 - HotelQuest" << endl;
	cout << "3 - hotels" << endl;
	cout << "4 - opodo" << endl;
	cout << "5 - orbitz" << endl;
	cout << "6 - TravelWeb" << endl;
	cout << "7 - TravelWorm" << endl;
	cout << "c - clear filter" << endl;

	char site;
	cout << ">";
	cin >> site;

	switch (site)
	{
		case '1': strcpy_s(FILTER.site, "AllHotels"); break;
		case '2': strcpy_s(FILTER.site, "HotelQuest"); break;
		case '3': strcpy_s(FILTER.site, "hotels"); break;
		case '4': strcpy_s(FILTER.site, "opodo"); break;
		case '5': strcpy_s(FILTER.site, "orbitz"); break;
		case '6': strcpy_s(FILTER.site, "TravelWeb"); break;
		case '7': strcpy_s(FILTER.site, "TravelWorm"); break;
		default:  strcpy_s(FILTER.site, ""); break;
	}
}

void filter_city()
{
	cout << "0 - clear filter" << endl;
	cout << "Enter city: ";

	char chr = getchar();
	char city[20];
	gets_s(city);

	if (city[0] == '0') strcpy_s(FILTER.city, "");
	else strcpy_s(FILTER.city, city);
}

void filter_hotel_name()
{
	cout << "0 - clear filter" << endl;
	cout << "Enter hotel name: ";

	char chr = getchar();
	char hotel_name[20];
	gets_s(hotel_name);

	if (hotel_name[0] == '0') strcpy_s(FILTER.hotel_name, "");
	else strcpy_s(FILTER.hotel_name, hotel_name);
}

void filter_hotel_adress()
{
	cout << "0 - clear filter" << endl;
	cout << "Enter hotel adress: ";

	char chr = getchar();
	char hotel_adress[20];
	gets_s(hotel_adress);

	if (hotel_adress[0] == '0') strcpy_s(FILTER.hotel_adress, "");
	else strcpy_s(FILTER.hotel_adress, hotel_adress);
}

void filter_room_class()
{
	cout << "Choose room class:" << endl;
	cout << "1 - regular" << endl;
	cout << "2 - half-luxe" << endl;
	cout << "3 - luxe" << endl;
	cout << "4 - vip" << endl;
	cout << "0 - clear filter" << endl;

	char room_class;
	cout << ">";
	cin >> room_class;

	switch (room_class)
	{
		case '1': strcpy_s(FILTER.room_class, "regular"); break;
		case '2': strcpy_s(FILTER.room_class, "half-luxe"); break;
		case '3': strcpy_s(FILTER.room_class, "luxe"); break;
		case '4': strcpy_s(FILTER.room_class, "vip"); break;
		default:  strcpy_s(FILTER.room_class, ""); break;
	}
}

void filter_guests()
{
	cout << "0 - clear filter" << endl;
	cout << "Enter guests number: ";

	int guests;
	cin >> guests;

	if (guests == 0) FILTER.guests = 0;
	else FILTER.guests = guests;
}

void filter_price()
{
	cout << "0 - clear filter" << endl;
	cout << "1 - use lowest price" << endl;
	cout << "2 - use highest price" << endl;
	cout << "3 - set min price" << endl;
	cout << "4 - set max price" << endl;

	char price;
	cout << ">";
	cin >> price;

	switch (price)
	{
		case '1': FILTER.price_min = -1; FILTER.price_max = 0;  break;
		case '2': FILTER.price_min = 0; FILTER.price_max = -1;  break;
		case '3': 
			int price_min;
			cout << "Enter min price:" << endl;
			cin >> price_min;

			if (price_min > 0) FILTER.price_min = price_min; 
			if (FILTER.price_max < 0) FILTER.price_max = 0;
		break;
		case '4':
			int price_max;
			cout << "Enter max price:" << endl;
			cin >> price_max;

			if (price_max > 0) FILTER.price_max = price_max;
			if (FILTER.price_min < 0) FILTER.price_min = 0;
		break;
		default: FILTER.price_min = FILTER.price_max = 0;
	}
}

void filter_reserved()
{
	cout << "0 - clear filter" << endl;
	cout << "Reserved (y/n): ";

	char reserved;
	cin >> reserved;

	switch (reserved)
	{
		case 'y': FILTER.reserved = 1; break;
		case 'n': FILTER.reserved = -1; break;
		default: FILTER.reserved = 0;
	}
}

void filter_clear()
{
	strcpy_s(FILTER.site, "0");
	strcpy_s(FILTER.city, "0");
	strcpy_s(FILTER.hotel_name, "0");
	strcpy_s(FILTER.hotel_adress, "0");
	strcpy_s(FILTER.room_class, "0");
	FILTER.guests = 0;
	FILTER.price_min = 0;
	FILTER.price_max = 0;
	FILTER.reserved = 0;

	cout << "Filters cleared." << endl;
}

// +-----------------------------------------------------------------+
// 
// SEARCH USING FILTERS

void search()
{
	// copy list
	for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
	{
		ptr->room.FILTER = true;
	}

	// 1. site filter
	if (FILTER.site[0] != '0')
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.site, FILTER.site)) ptr->room.FILTER = false;
	}

	// 2. city filter
	if (FILTER.city[0] != '0')
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.city, FILTER.city)) ptr->room.FILTER = false;
	}

	// 3. hotel_name filter
	if (FILTER.hotel_name[0] != '0')
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.hotel_name, FILTER.hotel_name)) ptr->room.FILTER = false;
	}

	// 4. hotel_adress filter
	if (FILTER.hotel_adress[0] != '0')
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.hotel_adress, FILTER.hotel_adress)) ptr->room.FILTER = false;
	}

	// 5. room_class filter
	if (FILTER.room_class[0] != '0')
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.room_class, FILTER.room_class)) ptr->room.FILTER = false;
	}

	// 6. guests filter
	if (FILTER.guests > 0)
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.guests != FILTER.guests) ptr->room.FILTER = false;
	}

	// 8. reserved filter
	if (FILTER.reserved != 0)
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.reserved != FILTER.reserved) ptr->room.FILTER = false;
	}

	// 7. price filter
	if (FILTER.price_min == -1)
	{
		Node* ptr_price_min = nullptr;

		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.FILTER)
			{
				ptr_price_min = ptr;
				break;
			}

		if (ptr_price_min)
		{
			for (Node* ptr = ptr_price_min->next; ptr; ptr = ptr->next)
				if (ptr->room.FILTER && ptr->room.price < ptr_price_min->room.price)
				{
					ptr_price_min->room.FILTER = false;
					ptr_price_min = ptr;
				}
				else
				{
					ptr->room.FILTER = false;
				}
		}
	}
	else if (FILTER.price_max == -1)
	{
		Node* ptr_price_max = nullptr;

		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.FILTER)
			{
				ptr_price_max = ptr;
				break;
			}

		if (ptr_price_max)
		{
			for (Node* ptr = ptr_price_max->next; ptr; ptr = ptr->next)
				if (ptr->room.FILTER && ptr->room.price > ptr_price_max->room.price)
				{
					ptr_price_max->room.FILTER = false;
					ptr_price_max = ptr;
				}
				else
				{
					ptr->room.FILTER = false;
				}
		}
	}

	if (FILTER.price_min > 0)
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.price < FILTER.price_min) ptr->room.FILTER = false;
	}
	if (FILTER.price_max > 0)
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.price > FILTER.price_max) ptr->room.FILTER = false;
	}

	// Search results
	bool results = false;
	for (Node* ptr = rooms.begin; ptr && !results; ptr = ptr->next)
		results = ptr->room.FILTER;

	if (results) menu_after_search();
	else cout << "No results" << endl;
}

void menu_after_search()
{
	// Show menu
	system("cls");
	cout << "+-------HOTEL-TRACER-------+" << endl;
	cout << "  r - Reservation" << endl;
	cout << "  c - Close results" << endl;
	cout << "+--------------------------+" << endl;
	cout << endl;

	// Generate query
	cout << "Your query:";

	if (FILTER.site[0] != '0') cout << " site - " << FILTER.site << ",";

	if (FILTER.city[0] != '0') cout << " sity - " << FILTER.city << ",";

	if (FILTER.hotel_name[0] != '0') cout << " hotel name - " << FILTER.hotel_name << ",";

	if (FILTER.hotel_adress[0] != '0') cout << " hotel adress - " << FILTER.hotel_adress << ",";

	if (FILTER.room_class[0] != '0') cout << " " << FILTER.room_class << " class,";

	if (FILTER.guests)
	{
		cout << " " << FILTER.guests;
		if (FILTER.guests == 1) cout << " guest,";
		else cout << " guests,";
	}

	if (FILTER.price_min == -1) cout << " lowest price,";
	else if (FILTER.price_max == -1) cout << " highest price,";
	else if (FILTER.price_min > 0 || FILTER.price_max > 0)
	{
		cout << "price ";
		if (FILTER.price_min > 0) cout << " from " << FILTER.price_min;
		if (FILTER.price_max > 0) cout << " to " << FILTER.price_max;
		cout << ",";
	}

	if (FILTER.reserved == 1) cout << " reserved,";
	else if (FILTER.reserved == -1) cout << " not reserved,";

	cout << "\b." << endl;

	// Show search results
	cout << endl;
	cout << "Search results:" << endl;
	rooms.show(1);

	char m;
	cout << endl;
	cout << ">";
	cin >> m;

	// Reservation
	if (m == 'r')
	{
		cout << "1 - Reserve room" << endl;
		cout << "0 - Clear reservation" << endl;
		cout << ">";
		cin >> m;

		if (m != '1' && m != '0') return;

		// find room
		int N;
		cout << "Enter room number: ";
		cin >> N;
		
		int i = 1;
		Node* ptr_reserve = nullptr;
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (ptr->room.FILTER)
			{
				if (i == N)
				{
					ptr_reserve = ptr;
					break;
				}
				i++;
			}

		// if room found
		if (ptr_reserve)
		{
			// Set reservation
			if (m == '1')
			{
				if (ptr_reserve->room.reserved == 1) cout << "Room already reserved." << endl;
				else
				{
					ptr_reserve->room.reserved = 1;
					write_data_to_file(ptr_reserve->room.site);
					cout << "Room reserved." << endl;
				}
			}
			// Clear reservation
			else if (m == '0')
			{
				if (ptr_reserve->room.reserved == 1)
				{
					ptr_reserve->room.reserved = 0;
					write_data_to_file(ptr_reserve->room.site);
					cout << "Reservation cleared." << endl;
				}
				else cout << "Reservation already clear." << endl;
			}
		}
		else cout << "Room not found." << endl;
	}
}

// +-----------------------------------------------------------------+
// 
// WORK WITH DATABASE

void read_data_from_file(const char* site)
{
	// open file
	FILE* fp;
	char fname[30] = "travel_sites/";
	strcat_s(fname, site);
	strcat_s(fname, ".txt");
	fopen_s(&fp, fname, "rt");

	// read data
	if (fp)
	{
		Hotel_Room room;
		fscanf_s(fp, "%s", room.site, 20);
		while (strlen(room.site) > 1)
		{
			fscanf_s(fp, "%s", room.city, 20);
			fscanf_s(fp, "%s", room.hotel_name, 20);
			fscanf_s(fp, "%s", room.hotel_adress, 30);
			fscanf_s(fp, "%s", room.room_class, 20);
			fscanf_s(fp, "%d", &room.guests);
			fscanf_s(fp, "%d", &room.price);
			fscanf_s(fp, "%d", &room.reserved);

			rooms.push_back(room);
			room.site[0] = '\0';
			fscanf_s(fp, "%s", room.site, 20);
		}
		fclose(fp);
	}
}

void write_data_to_file(const char* site)
{
	// open file
	FILE* fp;
	char fname[30] = "travel_sites/";
	strcat_s(fname, site);
	strcat_s(fname, ".txt");
	fopen_s(&fp, fname, "wt");

	// write data
	if (fp)
	{
		for (Node* ptr = rooms.begin; ptr; ptr = ptr->next)
			if (strcmp(ptr->room.site, site) == 0)
			{
				fprintf(fp, "%s\n", ptr->room.site);
				fprintf(fp, "%s\n", ptr->room.city);
				fprintf(fp, "%s\n", ptr->room.hotel_name);
				fprintf(fp, "%s\n", ptr->room.hotel_adress);
				fprintf(fp, "%s\n", ptr->room.room_class);
				fprintf(fp, "%d\n", ptr->room.guests);
				fprintf(fp, "%d\n", ptr->room.price);
				fprintf(fp, "%d\n", ptr->room.reserved);
				fprintf(fp, "\n");
			}
		fclose(fp);
	}
}