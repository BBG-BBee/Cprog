#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_COMPONENTS 50
#define MAX_NAME_LENGTH 30

typedef struct
{
	char name[MAX_NAME_LENGTH];
	int component_id;
	float price;
	int quantity;
} Component;

void printMenu(void);
void addComponent(Component** components, int* component_count, int* next_id);
void printComponentInfo(Component c);
void updateComponentQuantity(Component** components, int component_count);
void searchByComponentIDOrName(Component** components, int component_count);
void showComponentList(Component** components, int component_count);
void calculateTotalPrice(Component** components, int component_count);
void flushInputBuffer(void);
void removeInputEnter(char* str);
int getMenuChoice(void);

int main(void)
{
	Component* components[MAX_COMPONENTS] = { 0 };
	int component_count = 0;
	int next_id = 1;
	int input_menu = 0;

	printf("조립 PC 견적 프로그램에 오신 것을 환영합니다.\n");
	printf("원하는 작업을 선택하세요.\n");

	while (1)
	{
		printMenu();
		input_menu = getMenuChoice();

		switch (input_menu)
		{
		case 1:
			addComponent(components, &component_count, &next_id);
			break;
		case 2:
			searchByComponentIDOrName(components, component_count);
			break;
		case 3:
			showComponentList(components, component_count);
			break;
		case 4:
			calculateTotalPrice(components, component_count);
			break;
		case 5:
			updateComponentQuantity(components, component_count);
			break;
		case 6:
			printf("종료합니다!\n");
			for (int i = 0; i < component_count; i++)
			{
				free(components[i]);
			}
			return 0;
		default:
			printf("잘못된 선택입니다. 다시 시도하세요.\n");
			break;
		}
	}
}

// 메뉴를 출력
void printMenu(void)
{
	printf("\n메뉴:\n");
	printf("1. 부품 추가\n");
	printf("2. 부품 ID 및 이름으로 조회(ID를 모르면 아무 문자나 입력)\n");
	printf("3. 부품 목록 출력\n");
	printf("4. 총 가격 계산\n");
	printf("5. 부품 수량 수정\n");
	printf("6. 종료\n");
	printf("선택: ");
}

// 메뉴 선택을 입력
int getMenuChoice(void)
{
	int choice;
	choice = getchar() - '0';
	flushInputBuffer();
	return choice;
}

// 새로운 부품을 추가
void addComponent(Component** components, int* component_count, int* next_id)
{
	if (*component_count >= MAX_COMPONENTS)
	{
		printf("더 이상 추가할 수 없습니다.\n");
		return;
	}

	components[*component_count] = (Component*)malloc(sizeof(Component));

	flushInputBuffer();
	printf("부품 이름: ");
	fgets(components[*component_count]->name, MAX_NAME_LENGTH, stdin);
	removeInputEnter(components[*component_count]->name);
	components[*component_count]->component_id = (*next_id)++;
	printf("부품 가격: ");
	if (scanf("%f", &components[*component_count]->price) != 1)
	{
		printf("입력 오류\n");
		flushInputBuffer();
		return;
	}
	flushInputBuffer();
	printf("부품 수량: ");
	if (scanf("%d", &components[*component_count]->quantity) != 1)
	{
		printf("입력 오류\n");
		flushInputBuffer();
		return;
	}
	flushInputBuffer();
	(*component_count)++;
}

// 부품 정보 출력
void printComponentInfo(Component c)
{
	printf("부품 ID [%d] | 부품 이름 : [%s] | 부품 가격 : [%.2f] | 부품 수량 : [%d]\n",
		c.component_id, c.name, c.price, c.quantity);
}

// 특정 부품의 수량 수정
void updateComponentQuantity(Component** components, int component_count)
{
	char input[MAX_NAME_LENGTH];
	int id, new_quantity;
	int found = 0;

	flushInputBuffer();
	printf("수정할 부품 ID: ");
	if (scanf("%d", &id) == 1)
	{
		flushInputBuffer();
		for (int i = 0; i < component_count; i++)
		{
			if (components[i]->component_id == id)
			{
				printComponentInfo(*components[i]);
				printf("새 수량 입력: ");
				if (scanf("%d", &new_quantity) != 1)
				{
					printf("입력 오류\n");
					flushInputBuffer();
					return;
				}
				flushInputBuffer();
				components[i]->quantity = new_quantity;
				printf("수량이 업데이트 되었습니다.\n");
				found = 1;
				break;
			}
		}
	}
	else
	{
		flushInputBuffer();
		printf("수정할 부품 이름: ");
		fgets(input, MAX_NAME_LENGTH, stdin);
		removeInputEnter(input);
		for (int i = 0; i < component_count; i++)
		{
			if (strcmp(components[i]->name, input) == 0)
			{
				printComponentInfo(*components[i]);
				printf("새 수량 입력: ");
				if (scanf("%d", &new_quantity) != 1)
				{
					printf("입력 오류\n");
					flushInputBuffer();
					return;
				}
				flushInputBuffer();
				components[i]->quantity = new_quantity;
				printf("수량이 업데이트 되었습니다.\n");
				found = 1;
				break;
			}
		}
	}

	if (!found)
	{
		printf("부품을 찾을 수 없습니다.\n");
	}
}

// 부품 ID 혹은 이름을 입력받아 해당 부품을 조회
void searchByComponentIDOrName(Component** components, int component_count)
{
	char input[MAX_NAME_LENGTH];
	int id;
	int found = 0;

	flushInputBuffer();
	printf("조회할 부품 ID: ");
	if (scanf("%d", &id) == 1)
	{
		flushInputBuffer();
		for (int i = 0; i < component_count; i++)
		{
			if (components[i]->component_id == id)
			{
				printComponentInfo(*components[i]);
				found = 1;
				break;
			}
		}
	}
	else
	{
		flushInputBuffer();
		printf("조회할 부품 이름: ");
		fgets(input, MAX_NAME_LENGTH, stdin);
		removeInputEnter(input);
		for (int i = 0; i < component_count; i++)
		{
			if (strcmp(components[i]->name, input) == 0)
			{
				printComponentInfo(*components[i]);
				found = 1;
				break;
			}
		}
	}

	if (!found)
	{
		printf("부품을 찾을 수 없습니다.\n");
	}
}

// 부품 목록 출력
void showComponentList(Component** components, int component_count)
{
	for (int i = 0; i < component_count; i++)
	{
		printComponentInfo(*components[i]);
	}
}

// 부품 총 가격 계산
void calculateTotalPrice(Component** components, int component_count)
{
	float total_price = 0.0;
	for (int i = 0; i < component_count; i++)
	{
		total_price += components[i]->price * components[i]->quantity;
	}
	printf("총 가격: %.2f\n", total_price);
}

// 입력 버퍼를 비워줌
void flushInputBuffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// 문자열 끝에 남아있는 개행 문자를 제거
void removeInputEnter(char* str)
{
	str[strcspn(str, "\n")] = '\0';
}
