#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
#define ERROR 0
#define MAXLEN 1000
#define FIRST_ID 2024100
#define LAST_ID 2024199

/*
�й��� �������� �л� ������ �����ϴ� ������ �˻� �ý����� ������� �Ѵ�.
�̸� ���� ���� Ž��, Ž�� Ʈ���� ����Ͽ� ���� ����� �����ؾ� �Ѵ�.

�ʼ� ���
1. �л� ���� �߰�
2. �л� ���� Ž��
	- �й��� �Է¹޾� �ش� �л��� �̸� ���, ������ '�ش� �й� ����'�� ����Ѵ�.
3. �л� ���� ����
	- �й��� �Է¹޾� �ش� �л��� ����. ���� �Ŀ��� Ʈ���� ������ ���� Ž�� Ʈ�� ������ �����ؾ� ��
4. ��ü ���

*/

typedef unsigned int element;
typedef const char* String;
typedef struct TreeNode {
	element key;
	String name;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* search(TreeNode*, element);
TreeNode* insert_node(TreeNode*, element, String);
TreeNode* new_node(element, String);
TreeNode* delete_node(TreeNode*, element);
TreeNode* min_value_node(TreeNode*);
int execute_interface(TreeNode *);
int getID(char[], int);
void print_nodes(TreeNode*);

int main(void)
{
	TreeNode* root = NULL;
	element ID = FIRST_ID;
	for (; ID <= LAST_ID; ID++)
		root = insert_node(root, ID, "��**"); /* �̸��� �۵��� Ȯ���ϱ� ���� ��**�� ���� */
	while (execute_interface(root) != EOF)
		;

	return 0;
}


int execute_interface(TreeNode* node)
{
	int ch;

	printf("\n==== �л� ���� �ý��� ====\n");
	printf("(1) �л� ���� Ž��\n");
	printf("(2) �л� ���� ����\n");
	printf("(3) ��ü ���\n");
	printf("(0) ����\n");
	printf("����: ");
	if (isdigit(ch = getchar())) {	/* check whether option(ch) was typed as a number */
		if (ch < '0' || ch > '3') {		/* it is a number but not an expected option */
			printf("\nerror: illegal input\n");
			printf("usage: input 0, 1, 2, 3 only\n");
			getchar(); /* remove a remained character in input buffer from getchar */
			return 0;
		}
		else {						/* it is a number that represent an expected option */
			element key;
			char str[MAXLEN];
			TreeNode* temp;

			putchar('\n');
			switch (ch)
			{
			case '1':
				printf("�й� �Է�: ");
				if (getID(str, MAXLEN) > 0) {
					for (int i = 0; str[i] != '\0'; i++)
						if (!isdigit(str[i])) {
							printf("error: illegal input about Student ID\n");
							printf("usage: type your Student ID properly using numbers only\n");
							return ERROR;
						}

					temp = search(node, atoi(str));
					if (temp == NULL) {
						printf("�ش� �й� ����.\n");
						break;
					}
					printf("�˻� ���: �й�: %d, �̸�: %s\n", temp->key, temp->name);
					putchar('\n');
					break;
				}
				else { /* the length of str is 0 */
					printf("error: illegal input about Student ID\n");
					printf("usage: type your Student ID properly\n");
					return ERROR;
				}
			case '2':
				printf("������ �й� �Է�: ");
				if (getID(str, MAXLEN) > 0) {
					for (int i = 0; str[i] != '\0'; i++)
						if (!isdigit(str[i])) {
							printf("error: illegal input about Student ID\n");
							printf("usage: type your Student ID properly using numbers only\n");
							return ERROR;
						}

					temp = search(node, atoi(str));
					if (temp == NULL) {
						printf("�ش� �й� ����.\n");
						break;
					}
					printf("�й� %d ���� �Ϸ�.\n", temp->key);
					putchar('\n');
					break;
				}
				else {
					printf("error: illegal input about Student ID\n");
					printf("usage: type your Student ID properly\n");
					return ERROR;
				}
			case '3': 
				printf("\n\n--- ��ü �л� ��� (��������) ---\n");
				print_nodes(node);
				getchar(); /* remove a remained character in input buffer from getchar */
				break;
			case '0': /* user wants to terminate this program */
				return EOF;
			}
			return 0;
		}
	}
	else {				/* the option(ch) was typed unproperly */
		printf("\nerror: input is not a number\n");
		printf("usage: input 0, 1, 2, 3 only\n");
		getchar(); /* remove a remained character in input buffer from getchar */
		return ERROR;
	}
}

int getID(char line[], int lim)
{
	int c, i = 0;
	
	c = getchar(); /* remove a remained character in input buffer from getchar */
	while (--lim > 0 && (c = getchar()) != '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}

void print_nodes(TreeNode* root)
{
	if (root) {
		print_nodes(root->left);
		printf("�й�: %d, �̸�: %s\n", root->key, root->name);
		print_nodes(root->right);
	}
}

TreeNode* search(TreeNode* node, element key)
{
    if (node == NULL) /* leaf node was checked but cannot find the key value */
        return NULL;  /* fail */

    if (key == node->key)
        return node;
    else if (key < node->key)             
        return search(node->left, key);  /* search left subtree */
    else
        return search(node->right, key); /* search right subtree */
}

TreeNode* insert_node(TreeNode* root, element key, String name)
{
	if (root == NULL)
		return new_node(key, name);

	if (key < root->key)
		root->left = insert_node(root->left, key, name);
	else if (key > root->key)
		root->right = insert_node(root->right, key, name);

	return root;
}

TreeNode* new_node(element item, String name)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->name = name;
	temp->left = temp->right = NULL;

	return temp;
}

TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) 
		return root;

	if (key < root->key)	
		root->left = delete_node(root->left, key);		/* the key is at least in left subtree */
	else if (key > root->key)
		root->right = delete_node(root->right, key);	/* the key is at least in right subtree */

	else {												/* when this root has the key value */
		if (root->left == NULL && root->right == NULL) {/* case 1: a leaf node */
			free(root);									/* delete */
			return NULL;
		}
		else if (root->left == NULL) {					/* case 2-1: a node has a right subtree only */
			TreeNode* temp = root->right;				/* delete after saving the right subtree */
			free(root);										
			return temp;								/* concatenate temp to a parent tree of root */
		}
		else if (root->right == NULL) {					/* case 2-2: a node has a left subtree only */
			TreeNode* temp = root->left;				/* delete after saving the left subtree */
			free(root);
			return temp;								/* concatenate temp to a parent tree of root */
		}
		
		/* case 3: a node has both right and left subtree */
		TreeNode* temp = min_value_node(root->right);	/* find a node has minimum value in root's subtree */

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	/* delete_node�� �� ��° ��쿡��, 
	����Ʈ�� ���� ��� �� �� Ʈ������ ���� ���� key�� ������ ��尡 ����Ǵ� ��츸��  
	���� Ž�� Ʈ���� ������ �����Ѵ�. �̶�, 
	���� Ʈ���� ��� �� ������ �ܸ� ���,
	������ Ʈ���� ��� �� ���� �ܸ� ��尡 �ּҰ����� �˷��� �ִ�. */
	while (current->left != NULL) // ���⼭�� �� ���� �ܸ� ��带 ã���� �������� ������ ����
		current = current->left;

	return current;
}