#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
#define MAXLEN 1000

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
typedef char* String;
typedef struct TreeNode {
	element key;
	String name;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* search(TreeNode*, element);
TreeNode* insert_node(TreeNode*, element);
TreeNode* new_node(element);
TreeNode* delete_node(TreeNode*, element);
TreeNode* min_value_node(TreeNode*);
int execute_interface(void);
int getline(char[], int);

int main(void)
{
	while (execute_interface() != EOF)
		;

	return 0;
}


int execute_interface(void)
{
	int ch;

	printf("==== �л� ���� �ý��� ====\n");
	printf("(1) �л� ���� Ž��\n");
	printf("(2) �л� ���� ����\n");
	printf("(3) ��ü ���\n");
	printf("(0) ����\n");
	printf("����: ");
	if (isdigit(ch = getchar())) {
		if (ch < 0 || ch > 3) {
			printf("illegal input\n");
			printf("usage: input 0, 1, 2, 3 only\n");
			return -1;
		}
		else {
			element key;
			char str[MAXLEN];
			putchar('\n');
			printf("�й� �Է�: ");
			if (getline(str, MAXLEN) > 0){

			}
			
		}
	}
	else if (ch == EOF)
		return ch;
	else {
		printf("illegal input: input is not a number\n");
		printf("usage: input 0, 1, 2, 3 only\n");
		return -1;
	}
}

int getline(char line[], int lim)
{
	int c, i = 0;
	while (--lim > 0 && (c = getchar()) != '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}

TreeNode* search(TreeNode* node, element key)
{
    if (node == NULL) /* leaf node was checked but cannot find the key value */
        return NULL;  /* fail */

    if (key == node->key)
        return node;
    else if (key < node->key)             
        return  search(node->left, key);  /* search left subtree */
    else
        return  search(node->right, key); /* search right subtree */
}

TreeNode* insert_node(TreeNode* root, element key)
{
	if (root == NULL)
		return new_node(key);

	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);

	return root;
}

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
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