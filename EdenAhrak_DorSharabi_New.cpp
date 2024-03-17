#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;
#define SIZE 30
#define SIZE1 15
struct vote
{
	int value; 
	char* comment; 
	char country[SIZE1]; 
	vote* next;
};
//question1_1
struct movies {
	int id; 
	char* fname;
	char* genre;
	char studio[SIZE];
	int year;
	vote* Vote_list;
};
//question1_1

int countLines(const char* fileName);//question1_2
void FromFileToStruct(const char* moviesname, movies* arr , int size); //question1_3
void FromFileToList(const char* textvote, movies arr[], int size);//question1_4
bool addMovie(movies arr[], int& size);//question1_5
bool addVote(movies arr[], int new_id, int size);//question1_6
char printMenu();//question1_7
int printVotes(movies arr[], char name_movie[], int size);//question2_1
char* countGenre(movies arr[], char genre_movie[], int size);//question2_2
void printValue(movies arr[], int value_m, char country_m[], int size);//question2_3
int countCountry(movies arr[], int year_m, int size);//question2_4
void maxByCountry(movies arr[], int size);//question2_5
void RecommendMovie(movies arr[], int vote_value, int size);//question2_6
void deleteWorst(movies arr[], char genre_movie[], int size);//question2_7

void main()//question1_8
{
	int size = countLines("moviesData.txt");
	if (!size) {
		cout << "No system users\n";
		exit(0);
	}
	else
	{
		movies* NewArray = new movies[size];
		vote* vote_list = new vote;
		FromFileToStruct("moviesData.txt", NewArray, size);//question1_c
		FromFileToList("votingData.txt", NewArray, size);
		char menu;
		int Num_id;
		char Name_movie[100];
		char Genre_movie[100];
		char Country[100];
		int Value;
		int Year;
		int Average_votes;
		char Genre_delete[100];
		menu = printMenu();
		while (menu != 0)
		{
			switch (menu)
			{
			case('1'):
				addMovie(NewArray, size);
				break;
			case('2'):
				cout << "Please write a num id : ";
				cin >> Num_id;
				addVote(NewArray, Num_id, size);
				break;
			case('3'):
				cout << "Please enter a name movie : ";
				cin.ignore();
				cin.getline(Name_movie, 100);
				printVotes(NewArray, Name_movie, size);
				break;
			case('4'):
				cout << "Please enter the genre of the movie : ";
				cin.ignore();
				cin.getline(Genre_movie, 100);
				countGenre(NewArray, Genre_movie, size);
				break;
			case('5'):
				cout << "Please enter the value on the movies : ";
				cin >> Value;
				cout << "Please enter the country of the vote : ";
				cin.ignore();
				cin.getline(Country, 100);
				printValue(NewArray, Value, Country, size);
				break;
			case('6'):
				cout << "Please enter the year of the movie : ";
				cin >> Year;
				countCountry(NewArray, Year, size);
				break;
			case('7'):
				maxByCountry(NewArray, size);
				break;
			case('8'):
				cout << "Please enter the average of votes : ";
				cin >> Average_votes;
				RecommendMovie(NewArray, Average_votes, size);
				break;
			case('9'):
				cout << "Please enter genre of movie for deleting : ";
				cin.ignore();
				cin.getline(Genre_delete, 100);
				break;
			case('0'):
				FILE* myFile1;
				FILE* myFile2;
				myFile1 = fopen("moviesData.txt", "w");
				myFile2 = fopen("votingData.txt", "w");
				for (int i = 0; i < size; i++)
				{
					fprintf(myFile1, "%d,", NewArray[i].id);
					fprintf(myFile1,"%s,", NewArray[i].fname);
					fprintf(myFile1, "%s,", NewArray[i].genre);
					fprintf(myFile1,"%s,", NewArray[i].studio);
					fprintf(myFile1,"%d,\n", NewArray[i].year);
				}
				for (int j = 0; j < size; j++)
				{
					vote_list = NewArray[j].Vote_list;
					fprintf(myFile2, "%d", NewArray[j].id);
					while (vote_list != NULL)
					{
						fprintf(myFile2, "%d", vote_list[j].value);
						fprintf(myFile1, "%s", vote_list[j].country);
						fprintf(myFile1, "%s\n", vote_list[j].comment);
						vote_list = vote_list->next;
					}
				}
				fclose(myFile1);
				fclose(myFile2);
				delete vote_list;
				delete NewArray;
				cout << "logged out !!!" << endl;
				exit(1);

			} menu = printMenu();
		}
	}
}







int countLines(const char* fileName) {
	int count = 0;
	char c;
	FILE* myFile = fopen(fileName, "r");
	do {
		c = fgetc(myFile);
		if (c == '\n') {
			count++;
		}
	} while (c != EOF);
	fclose(myFile);
	return count;
}
void FromFileToStruct(const char* moviesname, movies* arr, int size)
{
	FILE* myFile2;
	char arr1[100];
	int count = 0; //count the number of array
	myFile2 = fopen(moviesname, "r");
	if (myFile2 == NULL) {
		cout << "Error - file is empty!!! \n"; // if the file is empty write this message
		return;
	}
	fscanf(myFile2, "%[^\n]", arr1); //scan the first line(we don't need this line)
	while (!feof(myFile2))  //until the file doesn't equal to EOF continue the loop
	{
		fscanf(myFile2, "%*c%[^,]", arr1); //scan from the file ignore the first char(\n) and copy to arr1 until (,)
		arr[count].id = atoi(arr1);  //equal from id to the number arr1(atoi)
		fscanf(myFile2, "%*c%[^,]", arr1); //ignore the first char and copy until(,)
		arr[count].fname = new char[strlen(arr1) + 1];
		strcpy(arr[count].fname, arr1); //copy the details from arr1 to fname
		fscanf(myFile2, "%*c%[^,]", arr1);
		arr[count].genre = new char[strlen(arr1) + 1];
		strcpy(arr[count].genre, arr1);
		fscanf(myFile2, "%*c%[^,]", arr1);
		strcpy(arr[count].studio, arr1);
		fscanf(myFile2, "%*c%[^\n]", arr1);
		arr[count].year = atoi(arr1);
		arr[count].Vote_list = NULL; //the pointer to vote equal to NULL(we didn't need it for now)
		count++;
	}
	fclose(myFile2);
}
void FromFileToList(const char* moviesname, movies arr[], int size) //copy the detail from moviesfile to the array
{
	FILE* myFile2;
	vote* Vote;
	char arr1[100]; // array for equal details from file to array
	myFile2 = fopen(moviesname, "r");
	if (myFile2 == NULL) {
		cout << "Error - file is empty!!! \n"; //if the file is empty, return this message and finish
		return;
	}
	fscanf(myFile2, "%[^\n]", arr1); //scan the first line until \n
	while (!feof(myFile2)) // until the file is not equal to EOF continue the loop
	{
		int m_id_vote;
		int arrayPlace;
		int countif = 0;
		char empty[] = "-";
		fscanf(myFile2, "%*c%[^:]", arr1);//ignore the first char(\n)from the last fscanf and copy the number
		m_id_vote = atoi(arr1); //the first num equal to the id movies number
		for (int i = 0; i < size; i++) //loop for found the place of id in the array
		{
			if (arr[i].id == m_id_vote)
			{
				Vote = new vote;
				countif++; //count if the id is equal to the number in movie id
				arrayPlace = i; // equal for use it outside the loop
				fscanf(myFile2, "%*c%[^:]", arr1); //ignore the first char(:) and scan until you read (:) + copy to arr1
				Vote->value = atoi(arr1);   //equal value to number arr1(atoi)
				fscanf(myFile2, "%*c%[^:]", arr1);
				strcpy(Vote->country, arr1);
				fscanf(myFile2, "%*c%[^\n]", arr1);
				if (strcmp(arr1, empty) == 0)
				{
					Vote->comment = NULL;
				}
				else
				{
					Vote->comment = new char[strlen(arr1) + 1];
					strcpy(Vote->comment, arr1);  //arr[size].Vote_list = Vote->next; //equal the vote to the next vode to continue the linked list
				}
				if (arr[i].Vote_list == NULL)
				{
					arr[arrayPlace].Vote_list = Vote;
					arr[arrayPlace].Vote_list->next = NULL;
				}
				else
				{
					Vote->next = arr[i].Vote_list;
					arr[i].Vote_list = Vote;
				}
				break;
			}
		}
		if (countif == 0)
		{
			fscanf(myFile2, "%[^\n]", arr1); // if the number is not equal to id read until \n
		}
	}
	//arr[size].Vote_list= NULL; //equal the last vote to null to end the linked list
	fclose(myFile2);
}
bool addMovie(movies arr[], int& size)
{
	movies* movie = new movies; // new element to recive from the user
	int size1 = size; //the size of the movies array
	int i = 0; //number for the loop to check
	movie = arr;
	cout << "Please enter name of movie :";
	movie[size1].fname = new char[100];
	cin.ignore();
	cin.getline(movie[size1].fname, 100);
	for (int i = 0; i < size1; i++)
	{
		if (strcmp(arr[i].fname, movie[size1].fname) == 0)
		{
			cout << "There is already such a movie !!!";
			return false;
		}
	}
	movie[size1].id = size1 + 2;
	movie[size1].genre = new char[100];
	cout << "Please enter the genre of the movie : ";
	cin.ignore();
	cin.getline(movie[size1].genre, 100, '\n');
	cout << "Please enter the name of studio : ";
	cin.ignore();
	cin.getline(movie[size1].studio, 100, '\n');
	cout << "Please enter the year of the movie : ";
	cin >> movie[size1].year;
	movie[size1].Vote_list = NULL;
	arr = movie;
	size = size1 + 1;
	return true;
}
bool addVote(movies arr[], int new_id, int size)
{
	vote* new_vote = new vote;
	int index;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i].id == new_id)
		{
			count++;
			index = i;
			break;
		}
	}
	if (count == 0)
	{
		cout << "Error - there is not id movie in the list !!!";
		delete new_vote;
		return false;
	}
	cout << "Please enter value on the movie : " << endl;
	cin >> new_vote->value;
	/*new_vote->value = atoi(x);*/
	cout << "Please enter your comment : " << endl;
	new_vote->comment = new char[100];
	cin.ignore();
	cin.getline(new_vote->comment, 100);
	cout << "Please enter which country you are from : " << endl;
	cin.ignore();
	cin.getline(new_vote->country, 100);
	new_vote->next = NULL;
	if (arr[index].Vote_list->value == new_vote->value)
	{
		if (strcmp(arr[index].Vote_list->comment, new_vote->comment) == 0)
		{
			if (strcmp(arr[index].Vote_list->country, new_vote->country) == 0)
			{
				cout << "There is already such a vote !!!";
				return false;
			}

		}
	}
	else
	{
		new_vote->next = arr[index].Vote_list;
		arr[index].Vote_list = new_vote;
	}
	delete new_vote;
	return true;
}
int printVotes(movies arr[], char name_movie[], int size)
{
	int index_name;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].fname, name_movie) == 0)
		{
			if (arr[i].Vote_list != NULL)
			{
				vote* print_vote = arr[i].Vote_list;
				while (print_vote != NULL) {
					if (print_vote->comment != NULL)
					{
						cout << "Comment : " << print_vote->comment << endl;
					}
					else
					{
						cout << "Comment : " << '-' << endl;
					}
					cout << "Country : " << print_vote->country << endl;
					print_vote = print_vote->next;
				}
				delete print_vote;
				return 1;

			}
			else
			{
				cout << "the list of votes is empty !!!";
				return 0;
			}
		} 
	}
	cout << "This movie doesn't exist in the list !!!";
	return -1;
}
char* countGenre(movies arr[], char genre_movie[], int size)
{
	char* movies_name[100];
	int index_genre = 0;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].genre, genre_movie) == 0)
		{

			movies_name[index_genre] = new char[100];
			strcpy(movies_name[index_genre], arr[i].fname);
			index_genre++;
		}
	}
	if (index_genre == 0)
	{
		cout << "There is no genre like this in the list !!!";
		return 0;
	}
	else
	{
		cout << "This genre is exist is the list";
		return *movies_name;
	}
}
void printValue(movies arr[], int value_m, char country_m[], int size)
{
	vote* count_v_c = new vote;
	int count_if = 0;
	for (int i = 0; i < size; i++)
	{
		count_v_c = arr[i].Vote_list;
		while (count_v_c != NULL)
		{
			if (value_m == count_v_c->value)
			{
				if (strcmp(count_v_c->country, country_m) == 0)
				{
					count_if++;
					cout << "Name movie : " << arr[i].fname << endl;
				}
			}
			count_v_c = count_v_c->next;
		}
	}
	if (count_if == 0)
	{
		cout << "Error - There are no value from this country !!!" << endl;
	}
}
int countCountry(movies arr[], int year_m, int size)
{
	vote* num_country = new vote;
	int index_y_m = 0; //the place of the new arr
	int counterArr; // count if there is more than on of country in the arr
	char* arrayYear_N[100];
	for (int i = 0; i < size; i++)
	{
		num_country = arr[i].Vote_list;
		if (arr[i].year == year_m)
		{
			while (num_country != NULL)
			{
				counterArr = 0; //count if there is match between the new arr to the country from the movies arr
				for (int j = 0; j < index_y_m; j++)
				{
					if (strcmp(arrayYear_N[j], num_country->country) == 0)
						counterArr++; // count if there is a match between the countries
				}
				if (counterArr == 0)
				{
					arrayYear_N[index_y_m] = new char[100];
					strcpy(arrayYear_N[index_y_m], num_country->country); // copy the name of the country to new arr
					index_y_m++; //count the size of arr(the amount of the countries
				}
				num_country = num_country->next;
			}
		}
	}
	if (index_y_m == 0)
	{
		cout << "Error - there are no year and country in this list" << endl;
		delete num_country; //delete from the memory the new element
		return 0;
	}
	for (int t = 0; t < index_y_m; t++)
	{
		delete[]arrayYear_N[t]; // delete the dynamic array from the new arr 
	}
	delete num_country;
	cout << "the number of country : " << index_y_m;
	return index_y_m; //return the size of the array(the size = the amount of the countries)
}
void maxByCountry(movies arr[], int size)
{
	vote* num_comment = new vote; //new elemnt to check the amount of the comment
	vote* num_country = new vote;
	char array_country[100];
	char* country_count[100];
	int max_comment = 0;
	int loop;
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		num_country = arr[i].Vote_list;
		while (num_country != NULL)
		{
			loop = 0;
			strcpy(array_country, num_country->country);
			for (int j = 0; j < size; j++)
			{
				num_comment = arr[j].Vote_list;
				while (num_comment != NULL)
				{
					if (strcmp(num_comment->country, array_country) == 0)
					{
						if (num_comment->comment != NULL)
						{
							loop++;
						}
					}
					num_comment = num_comment->next;
				}
			}
			if (max_comment == 0)
			{
				max_comment = loop;
				country_count[index] = new char[100];
				strcpy(country_count[index], array_country);
				index++;
			}
			else if (max_comment < loop)
			{
				for (int j = 0; j < index; j++)

				{
					if (strcmp(country_count[j], arr[i].Vote_list->country) == 0)
						break;
				}
				max_comment = loop;
				country_count[index] = new char[100];
				strcpy(country_count[index], array_country);
				index++;

			}
			num_country = num_country->next;
		}
	}
	for (int i = 0; i < index; i++)
	{
		cout << "The country with the most votes : " << country_count[i] << endl;
	}
}
void RecommendMovie(movies arr[], int vote_value, int size)
{
	vote* vote_mo = new vote;
	FILE* myFile;
	float sum = 0.0;
	float average;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		vote_mo = arr[i].Vote_list;
		while (vote_mo != NULL)
		{
			sum += vote_mo->value; //add all value to sum
			count++; //count how many value 
			vote_mo = vote_mo->next;
		}
		if (count == 0)
		{
			cout << "ERROR - there are no value !!!" << endl;
		}
		else
		{
			average = sum / count; //average
			if (average >= (float)vote_value)
			{
				myFile = fopen("Recommendation.txt", "a"); //open file
				fprintf(myFile, "%s , %s\n", arr[i].fname, arr[i].genre); //print to file
				fclose(myFile);
			}

		}
	}
}
void deleteWorst(movies arr[], char genre_movie[], int size)
{
	vote* genre = new vote;
	vote* value_vote = new vote;
	int minimum = 10; //10 = maximum value
	int counter = 0; // if it will be still equal to 0 we know there is no match in the loop
	for (int j = 0; j < size; j++) // loop for found the minimum value
	{
		genre = arr[j].Vote_list;
		while (genre != NULL)
		{
			if (minimum > genre->value && strcmp(genre_movie, arr[j].genre) == 0)
			{
				minimum = genre->value;
				counter++; //count if found genre and value 
			}
			genre = genre->next;
		}
	}
	if (counter == 0)
	{
		cout << "Error - genre doesn't found !!!"; //print answer if he doesnt found
	}
	else
	{
		for (int j = 0; j < size; j++) //loop for found the minimum value +  genre and delete the vote list
		{
			value_vote = arr[j].Vote_list;
			while (value_vote != NULL)
			{
				if (minimum == value_vote->value && strcmp(genre_movie, arr[j].genre) == 0) //if there is value and genre 
				{
					delete[]arr[j].Vote_list; //delete the specific list
					arr[j].Vote_list = NULL;
					break;
				}
				value_vote = value_vote->next;
			}
		}
	}
}
char printMenu() {
	char choise = 0;
	cout << "\n*****Which Function do you like to do:*****\n";
	cout << "1-Add movie\n";
	cout << "2-Add vote\n";
	cout << "3-Print  votes\n";
	cout << "4-Count Genre\n";
	cout << "5-Print value\n";
	cout << "6-Count Country\n";
	cout << "7-Max by country\n";
	cout << "8-Recommend movie\n";
	cout << "9-Delete worst\n";
	cout << "0-logOut\n";

	do {
		cin >> choise;
		if ((choise < '0' || choise > '9'))
			cout << "wrong choise - try again\n";
	} while (choise < '0' || choise > '9');

	return choise;
}


