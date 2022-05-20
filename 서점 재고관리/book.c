#define _CRT_SECURE_NO_WARNINGS

//displayInventory(Inven) 구현 X

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

int flag = 0, choice = 0, i = 0; // 파일 읽기 성공여부 플래그, 프로그램 동작 choice변수, 구조체 배열에 접근하기 위한 인덱스 변수
char file_name[20] = { 0, }; // 파일 이름

int string_compare(char*, char*);
// 서적 정보를 저장하는 자료구조
typedef struct books {
	char title[30]; // 책 이름
	int qty; // 양
	double price; // 가격
	struct books* link;
}library;

// 저자 정보를 저장하는 자료구조
typedef struct Inventory {
	char last_name[20]; // 성
	char first_name[20]; // 이름
	struct books *head; // 서적 정보 주소 저장
}theInventory;


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// 사용자 추가 함수///////////////////////////////

// 파일에서 읽어온 데이터를 단순연결리스트로 만듬
void makeInventoryList(theInventory* Inven, char* last_name, char* first_name, char* book_title, int qty, double price) {
	library* last_book;
	library* new_book = (library*)malloc(sizeof(library));
	for (int check = 0; check < i; check++)
	{
		if (strcmp(Inven[check].last_name, last_name) == 0 && strcmp(Inven[check].first_name, first_name) == 0) // 배열에 저자명이 같은 저자가 존재한다면 배열에 할당X 및 서적 정보 연결
		{
			strcpy(new_book->title, book_title);
			new_book->qty = qty;
			new_book->price = price;
			new_book->link = Inven[check].head;
			Inven[check].head = new_book;
			return;
		}
	}

	// 같은 저자가 존재하지 않는다면 배열에 새로 할당하고 서적 정보 연결
	strcpy(Inven[i].last_name, last_name);
	strcpy(Inven[i].first_name, first_name);
	strcpy(new_book->title, book_title);
	new_book->qty = qty;
	new_book->price = price;
	new_book->link = Inven[i].head;
	Inven[i].head = new_book;
	i++;
}

// 버블정렬
void bubble_sort(char** title_array, int * qty_array, double * price_array, int title_cnt2)
{
	char tmp_title[30] = {0, };
	int tmp_qty = 0;
	double tmp_price = 0.0;

	for (int a = 0; a < title_cnt2; a++)
	{
		for (int b = 0; b < a; b++)
		{
			if (strcmp(title_array[b], title_array[b + 1]) > 0) // title_array[b]가 title_array[b+1]보다 작다면
			{
				strcpy(tmp_title, title_array[b]);
				tmp_qty = qty_array[b];
				tmp_price = price_array[b];

				strcpy(title_array[b], title_array[b + 1]);
				qty_array[b] = qty_array[b + 1];
				price_array[b] = price_array[b + 1];

				strcpy(title_array[b + 1], tmp_title);
				qty_array[b + 1] = tmp_qty;
				price_array[b + 1] = tmp_price;
			}
		}
	}

	for (int iteration = 0; iteration < title_cnt2; iteration++)
	{
		printf("	The title is: %s\n", title_array[iteration]);
		printf("	The qty is: %d\n", qty_array[iteration]);
		printf("	The price is: %.2lf\n", price_array[iteration]);
		printf("\n");
		printf("	------\n");
		printf("\n");
	}
}
///////////////////////////////////////////////////////////////////////////////


// 프로그램 시작 문구 출력
void greeting() {
	printf("Welome to the book store program!\n");
}

// 파일에서 읽어서 자료구조에 할당하는 함수
void readDatabase(theInventory* Inven) {
	char buffer[100] = { 0, }; // 파일에서 한줄 씩 읽어오기위한 버퍼
	char* ptr = NULL; // 문자열을 콤마로 구분하기 위한 포인터 변수

	char temp_last_name[20] = { 0, }; // 저자 이름 임시저장 변수
	char temp_first_name[20] = { 0, }; // 저자 성 임시저장 변수
	char temp_book_title[30] = { 0, }; // 책 제목 임시저장 변수
	int temp_qty = 0; // 책 수량 임시저장 변수
	double temp_price = 0.0; // 책 가격 임시저장 변수

	int cnt = 0;
	FILE* file;

	printf("Enter the name of the file: ");
	scanf("%s", file_name); // 파일 이름 입력 받기
	file = fopen(file_name, "r"); // 파일 읽기모드 실행

	while (file == NULL)
	{
		printf("Error: reading Database\n");
		printf("Enter the name of the file: ");
		scanf("%s", file_name); // 파일 이름 입력 받기
		file = fopen(file_name, "r"); // 파일 읽기모드 실행
		while (getchar() != '\n'); // 입력 버퍼 비우기
		flag = 0;
	}

	for (int j = 0; j < 50; j++)
	{
		Inven[j].head = NULL; // 구조체 배열의 head를 모두 NULL로 초기화하고 시작
	}

	while (fgets(buffer, sizeof(buffer), file) != NULL) // 파일 한줄 씩 읽어오기
	{
		memset(temp_last_name, '\0', sizeof(temp_last_name));
		memset(temp_first_name, '\0', sizeof(temp_first_name));
		memset(temp_book_title, '\0', sizeof(temp_book_title));

		ptr = strtok(buffer, ","); // 버퍼에서 받아온 파일 한줄을 콤마 기준으로 문자열 자르기

		while (ptr != NULL) // 콤마 기준으로 문자열 자르는 반복문
		{
			if (cnt == 0)
			{
				strcpy(temp_last_name, ptr);
			}
			else if (cnt == 1)
			{
				strcpy(temp_first_name, ptr);
			}

			else if (cnt == 2)
			{
				strcpy(temp_book_title, ptr);
			}

			else if (cnt == 3)
			{
				temp_qty = atoi(ptr);
			}

			else if (cnt == 4)
			{
				temp_price = atof(ptr);
			}

			ptr = strtok(NULL, ",");  // 다음 문자열을 잘라서 포인터 반환
			cnt++;
			if (cnt == 5) cnt = 0; // 콤마 기준으로 구분 완료
		}
		makeInventoryList(Inven, temp_last_name, temp_first_name, temp_book_title, temp_qty, temp_price);
	}
	flag = 1;
	fclose(file);
}

// 메뉴 출력
int printMenu() {
	int check = 0;
	printf("\n");
	printf("--------------------------------------\n");
	printf("Enter 0 to display the original inventory\n");
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to chage the price on hand\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");
	printf("Enter your choice: ");

	while (scanf("%d", &choice) == 0 || choice < 0) // 정수만 입력 받음
	{
		printf("Error: Invalida Choice\n");
		printf("Enter your choice: ");
		while (getchar() != '\n'); // 버퍼 초기화
	}
	return choice;
}

// 데이터베이스 출력
void displayOrigianlInventory(theInventory* Inven) {
	library* p = NULL;

	for (int j = 0; j < i; j++)
	{
		p = Inven[j].head;

		printf("The author is: %s, %s\n", Inven[j].last_name, Inven[j].first_name);
		while (p != NULL) 
		{
			printf("\n");
			printf("	The title is: %s\n", p->title);
			printf("	The qty is: %d\n", p->qty);
			printf("	The price is: %.2lf\n", p->price);
			printf("\n");
			printf("	----------\n");
			printf("\n");
			p = p->link;
		}
	}
}

void displayAuthorsWork(theInventory* Inven) {
	library* ptr; // library head정보를 저장할 변수 
	char last_name[20] = { 0, };
	char first_name[20] = { 0, };

	int title_cnt = 0;
	int title_cnt2 = 0;

	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32;

	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32;

	for (int j = 0; j < i; j++) // 이미 존재하는 정보인지 탐색
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0) // 저자명 일치
		{
			while (ptr != NULL)
			{
				title_cnt++;
				ptr = ptr->link;
			}
			
			ptr = Inven[j].head; // 포인터 헤드로 초기화
			char** title_array = (char *)malloc(sizeof(char *) * title_cnt); // 문자열 배열 선언
			for (int cnt = 0; cnt < title_cnt; cnt++)
			{
				title_array[cnt] = (char*)malloc(sizeof(char) * 30); // 문자열을 최대 30만큼 받아오도록 동적할당
			}
			
			int *qty_array = (int*)malloc(sizeof(int) * title_cnt); // 수량을 저장할 배열 선언
			double* price_array = (double*)malloc(sizeof(double) * title_cnt); // 가격을 저장할 배열 선언

			while (ptr != NULL)
			{
				title_array[title_cnt2] = ptr->title; // 문자열 배열에 책 제목 할당
				qty_array[title_cnt2] = ptr->qty;
				price_array[title_cnt2] = ptr->price;
				ptr = ptr->link;
				title_cnt2++;
			}
			bubble_sort(title_array, qty_array, price_array, title_cnt2); // 버블정렬
			return;
		}
		else
		{
			if (j == i - 1) // 인덱스 끝까지 탐색했음에도 일치하는 저자명이 없다면 에러 출력
			{
				printf("Sorry, but no books by %s, %s in the inventory\n", last_name, first_name);
				return;
			}
		}
	}

}

void addBook(theInventory* Inven) {
	library* ptr = NULL;

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[30] = { 0, };
	int qty = 0;
	
	double price = 0;
	char f_price[10] = {0, }; // price를 문자열로 입력받은 후 atof()로 실수로 변경하기 위한 변수
	char f_qty[10] = { 0, };// qty를 문자열로 입력받은 후 atof()로 실수로 변경하기 위한 변수

	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // 첫번째 문자 대문자로 변경

	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // 첫번째 문자 대문자로 변경


	while (getchar() != '\n'); // 입력 버퍼 비우기
	printf("Enter the title: ");
	scanf("%[^\n]s", title);
	_strlwr(title);
	title[0] -= 32; // 가장 첫번째 문자 대문자로 변경
	for (int k = 0; k < strlen(title); k++) // 공백 뒤에 존재한 문자들을 대문자로 변경하는 반복문
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	for (int j = 0; j < i; j++) // 이미 존재하는 정보인지 검사
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				if (strcmp(ptr->title, title) == 0)
				{
					printf("This book is already in the Inventory and cannot be added again\n");
					return;
				}
				ptr = ptr->link;
			}
		}
	}
	
	printf("Enter the qty: ");
	scanf("%s", f_qty);
	qty = atoi(f_qty);
	while (strlen(f_qty) != 1 || qty < 0) // 0과 양의 정수만 입력 받기
	{
		printf("Invalid input for qty\n");
		printf("Enter the qty: ");
		while (getchar() != '\n'); // 입력 버퍼 비우기
		scanf("%s", f_qty);
		qty = atoi(f_qty);
	}

	printf("Enter the price: ");
	scanf("%s", f_price);
	price = atof(f_price);
	while (strlen(f_price) != 4 || price < 0.0)
	{
		printf("Invalid input for price\n");
		printf("Enter the price: ");
		while (getchar() != '\n'); // 입력 버퍼 비우기
		scanf("%s", f_price);
		price = atof(f_price);
	}

	makeInventoryList(Inven, last_name, first_name, title, qty, price); // 존재하지 않는 정보라면 인벤토리 업데이트
}

void changePrice(theInventory* Inven) {
	library* ptr = NULL; // 서적 리스트의 헤드를 가리키는 포인터 변수

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[20] = { 0, };

	double price = 0;
	char f_price[10] = { 0, }; // price를 문자열로 입력받은 후 atof()로 실수로 변경하기 위한 변수

	int find_title_flag = 0;
	int res;

	// 저자 퍼스트 네임 데이터 처리
	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // 첫번째 문자 대문자로 변경

	// 저자 라스트 네임 데이터 처리
	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // 첫번째 문자 대문자로 변경

	// 이미 존재하는 저자 정보인지 검사
	for (int j = 0; j < i; j++)
	{
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			break;
		}
		else
		{
			if (j == i - 1) // 반복문을 끝까지 탐색했음에도 저자가 없다면 에러 출력
			{
				printf("No such author in your database. So you cannot change the price\n");
				return;
			}
		}
	}

	// 책 존재하는지 탐색
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				res = string_compare(ptr->title, title);
				if (res == 1)
				{
					find_title_flag = 1; 
				}
				ptr = ptr->link;
			}
			if (find_title_flag == 0)
			{
				printf("No book with the title %s by %s, %s in the inventory\n", title, last_name, first_name);
				return;
			}
		}
	}

	// 책 제목 입력 데이터 처리
	while (getchar() != '\n'); // 입력 버퍼 비우기
	printf("Enter the title: ");
	scanf("%[^\n]s", title); // 공백 포함해서 입력 받기
	title[0] -= 32; // 가장 첫번째 문자 대문자로 변경
	for (int k = 0; k < strlen(title); k++) // 공백 기준 뒤에 존재한 문자들을 대문자로 변경하는 반복문
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	// 책 가격 입력 데이터 처리
	printf("Enter the price: ");
	scanf("%s", f_price);
	price = atof(f_price);
	while (strlen(f_price) != 4 || price < 0.0)
	{
		printf("Invalid input for price\n");
		printf("Enter the price: ");
		while (getchar() != '\n'); // 입력 버퍼 비우기
		scanf("%s", f_price);
		price = atof(f_price);
	}

	// 책 가격 변경하기 위해 탐색
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				res = string_compare(ptr->title, title);
				if (res == 1)
				{
					printf("Price will be updated from %.2lf to %.2lf", ptr->price, price);
					(* ptr).price = price;
					return;
				}
				ptr = ptr->link;
			}
		}
	}
}

void changeQty(theInventory* Inven) {
	library* ptr = NULL; // 서적 리스트의 헤드를 가리키는 포인터 변수

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[30] = { 0, };
	int qty = 0;

	// 저자 퍼스트 네임 데이터 처리
	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // 첫번째 문자 대문자로 변경

	// 저자 라스트 네임 데이터 처리
	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // 첫번째 문자 대문자로 변경

	// 이미 존재하는 저자 정보인지 검사
	for (int j = 0; j < i; j++)
	{
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			break;
		}
		else
		{
			if (j == i - 1) // 반복문을 끝까지 탐색했음에도 저자가 없다면 에러 출력
			{
				printf("No such author in your database. So you cannot change the qty\n");
				return;
			}
		}
	}

	// 책 제목 입력 데이터 처리
	while (getchar() != '\n'); // 입력 버퍼 비우기
	printf("Enter the title: ");
	scanf("%[^\n]s", title); // 공백 포함해서 입력 받기
	title[0] -= 32; // 가장 첫번째 문자 대문자로 변경
	for (int k = 0; k < strlen(title); k++) // 공백 기준 뒤에 존재한 문자들을 대문자로 변경하는 반복문
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	printf("Enter the qty: ");
	while (scanf("%d", &qty) != 1 || qty < 0) // 0과 양의 정수만 입력 받기
	{
		printf("Invalid input for qty\n");
		printf("Enter the qty: ");
		while (getchar() != '\n'); // 입력 버퍼 비우기
	}

	// 책 수량 변경하기 위해 탐색
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				if (strcmp(ptr->title, title) == 0)
				{
					printf("Qty will be updated from %d to %d", ptr->qty, qty);
					ptr->qty = qty;
					return;
				}
				ptr = ptr->link;
			}
		}
	}
}

void totalQty(theInventory *Inven) {
	library* ptr = NULL;
	int total = 0;
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		while (ptr != NULL)
		{
			total += ptr->qty;
			ptr = ptr->link;
		}
	}
	printf("The total number of books is %d\n", total);
}

void calculateTotalAmount(theInventory * Inven) {
	library* ptr = NULL;
	double total_amount = 0;
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		while (ptr != NULL)
		{
			total_amount += (ptr->qty * ptr->price);
			ptr = ptr->link;
		}
	}
	printf("The total value of inventory is $%.2f\n", total_amount);
}

int main() {	
	theInventory Inven[50]; // 구조체 일차원 배열 생성
	greeting(); // 환영 문구 출력

	readDatabase(Inven);

	while (flag)
	{
		choice = printMenu();
		switch (choice)
		{
		case 0:
			displayOrigianlInventory(Inven);
			break;
		case 1:
			//displayInventory(Inven);
			break;
		case 2:
			displayAuthorsWork(Inven);
			break;
		case 3:
			addBook(Inven);
			break;
		case 4:
			changePrice(Inven);
			break;
		case 5:
			changeQty(Inven);
			break;
		case 6:
			totalQty(Inven);
			break;
		case 7:
			calculateTotalAmount(Inven);
			break;
		case 8:
			printf("Thank you for using this program\n");
			flag = 0;
			break;
		default:
			printf("Invalid Choice\n");
			break;
		}
	}
	return 0;
}
