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

	printf("���� PC ���� ���α׷��� ���� ���� ȯ���մϴ�.\n");
	printf("���ϴ� �۾��� �����ϼ���.\n");

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
			printf("�����մϴ�!\n");
			for (int i = 0; i < component_count; i++)
			{
				free(components[i]);
			}
			return 0;
		default:
			printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
			break;
		}
	}
}

// �޴��� ���
void printMenu(void)
{
	printf("\n�޴�:\n");
	printf("1. ��ǰ �߰�\n");
	printf("2. ��ǰ ID �� �̸����� ��ȸ(ID�� �𸣸� �ƹ� ���ڳ� �Է�)\n");
	printf("3. ��ǰ ��� ���\n");
	printf("4. �� ���� ���\n");
	printf("5. ��ǰ ���� ����\n");
	printf("6. ����\n");
	printf("����: ");
}

// �޴� ������ �Է�
int getMenuChoice(void)
{
	int choice;
	choice = getchar() - '0';
	flushInputBuffer();
	return choice;
}

// ���ο� ��ǰ�� �߰�
void addComponent(Component** components, int* component_count, int* next_id)
{
	if (*component_count >= MAX_COMPONENTS)
	{
		printf("�� �̻� �߰��� �� �����ϴ�.\n");
		return;
	}

	components[*component_count] = (Component*)malloc(sizeof(Component));

	flushInputBuffer();
	printf("��ǰ �̸�: ");
	fgets(components[*component_count]->name, MAX_NAME_LENGTH, stdin);
	removeInputEnter(components[*component_count]->name);
	components[*component_count]->component_id = (*next_id)++;
	printf("��ǰ ����: ");
	if (scanf("%f", &components[*component_count]->price) != 1)
	{
		printf("�Է� ����\n");
		flushInputBuffer();
		return;
	}
	flushInputBuffer();
	printf("��ǰ ����: ");
	if (scanf("%d", &components[*component_count]->quantity) != 1)
	{
		printf("�Է� ����\n");
		flushInputBuffer();
		return;
	}
	flushInputBuffer();
	(*component_count)++;
}

// ��ǰ ���� ���
void printComponentInfo(Component c)
{
	printf("��ǰ ID [%d] | ��ǰ �̸� : [%s] | ��ǰ ���� : [%.2f] | ��ǰ ���� : [%d]\n",
		c.component_id, c.name, c.price, c.quantity);
}

// Ư�� ��ǰ�� ���� ����
void updateComponentQuantity(Component** components, int component_count)
{
	char input[MAX_NAME_LENGTH];
	int id, new_quantity;
	int found = 0;

	flushInputBuffer();
	printf("������ ��ǰ ID: ");
	if (scanf("%d", &id) == 1)
	{
		flushInputBuffer();
		for (int i = 0; i < component_count; i++)
		{
			if (components[i]->component_id == id)
			{
				printComponentInfo(*components[i]);
				printf("�� ���� �Է�: ");
				if (scanf("%d", &new_quantity) != 1)
				{
					printf("�Է� ����\n");
					flushInputBuffer();
					return;
				}
				flushInputBuffer();
				components[i]->quantity = new_quantity;
				printf("������ ������Ʈ �Ǿ����ϴ�.\n");
				found = 1;
				break;
			}
		}
	}
	else
	{
		flushInputBuffer();
		printf("������ ��ǰ �̸�: ");
		fgets(input, MAX_NAME_LENGTH, stdin);
		removeInputEnter(input);
		for (int i = 0; i < component_count; i++)
		{
			if (strcmp(components[i]->name, input) == 0)
			{
				printComponentInfo(*components[i]);
				printf("�� ���� �Է�: ");
				if (scanf("%d", &new_quantity) != 1)
				{
					printf("�Է� ����\n");
					flushInputBuffer();
					return;
				}
				flushInputBuffer();
				components[i]->quantity = new_quantity;
				printf("������ ������Ʈ �Ǿ����ϴ�.\n");
				found = 1;
				break;
			}
		}
	}

	if (!found)
	{
		printf("��ǰ�� ã�� �� �����ϴ�.\n");
	}
}

// ��ǰ ID Ȥ�� �̸��� �Է¹޾� �ش� ��ǰ�� ��ȸ
void searchByComponentIDOrName(Component** components, int component_count)
{
	char input[MAX_NAME_LENGTH];
	int id;
	int found = 0;

	flushInputBuffer();
	printf("��ȸ�� ��ǰ ID: ");
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
		printf("��ȸ�� ��ǰ �̸�: ");
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
		printf("��ǰ�� ã�� �� �����ϴ�.\n");
	}
}

// ��ǰ ��� ���
void showComponentList(Component** components, int component_count)
{
	for (int i = 0; i < component_count; i++)
	{
		printComponentInfo(*components[i]);
	}
}

// ��ǰ �� ���� ���
void calculateTotalPrice(Component** components, int component_count)
{
	float total_price = 0.0;
	for (int i = 0; i < component_count; i++)
	{
		total_price += components[i]->price * components[i]->quantity;
	}
	printf("�� ����: %.2f\n", total_price);
}

// �Է� ���۸� �����
void flushInputBuffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// ���ڿ� ���� �����ִ� ���� ���ڸ� ����
void removeInputEnter(char* str)
{
	str[strcspn(str, "\n")] = '\0';
}
