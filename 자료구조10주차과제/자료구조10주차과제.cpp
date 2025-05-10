#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
#define ERROR 0
#define MAXLEN 1000
#define FIRST_ID 2024100
#define LAST_ID 2024199

/*
학번을 기준으로 학생 정보를 저장하는 간단한 검색 시스템을 만들고자 한다.
이를 위해 이진 탐색, 탐색 트리를 사용하여 다음 기능을 구현해야 한다.

필수 기능
1. 학생 정보 추가
2. 학생 정보 탐색
	- 학번을 입력받아 해당 학생의 이름 출력, 없으면 '해당 학번 없음'을 출력한다.
3. 학생 정보 삭제
	- 학번을 입력받아 해당 학생을 삭제. 삭제 후에도 트리는 여전히 이진 탐색 트리 성질을 만족해야 함
4. 전체 출력

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
		root = insert_node(root, ID, "김**"); /* 이름은 작동을 확인하기 위해 김**로 통일 */
	while (execute_interface(root) != EOF)
		;

	return 0;
}


int execute_interface(TreeNode* node)
{
	int ch;

	printf("\n==== 학생 정보 시스템 ====\n");
	printf("(1) 학생 정보 탐색\n");
	printf("(2) 학생 정보 삭제\n");
	printf("(3) 전체 출력\n");
	printf("(0) 종료\n");
	printf("선택: ");
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
				printf("학번 입력: ");
				if (getID(str, MAXLEN) > 0) {
					for (int i = 0; str[i] != '\0'; i++)
						if (!isdigit(str[i])) {
							printf("error: illegal input about Student ID\n");
							printf("usage: type your Student ID properly using numbers only\n");
							return ERROR;
						}

					temp = search(node, atoi(str));
					if (temp == NULL) {
						printf("해당 학번 없음.\n");
						break;
					}
					printf("검색 결과: 학번: %d, 이름: %s\n", temp->key, temp->name);
					putchar('\n');
					break;
				}
				else { /* the length of str is 0 */
					printf("error: illegal input about Student ID\n");
					printf("usage: type your Student ID properly\n");
					return ERROR;
				}
			case '2':
				printf("삭제할 학번 입력: ");
				if (getID(str, MAXLEN) > 0) {
					for (int i = 0; str[i] != '\0'; i++)
						if (!isdigit(str[i])) {
							printf("error: illegal input about Student ID\n");
							printf("usage: type your Student ID properly using numbers only\n");
							return ERROR;
						}

					temp = search(node, atoi(str));
					if (temp == NULL) {
						printf("해당 학번 없음.\n");
						break;
					}
					printf("학번 %d 삭제 완료.\n", temp->key);
					putchar('\n');
					break;
				}
				else {
					printf("error: illegal input about Student ID\n");
					printf("usage: type your Student ID properly\n");
					return ERROR;
				}
			case '3': 
				printf("\n\n--- 전체 학생 목록 (오름차순) ---\n");
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
		printf("학번: %d, 이름: %s\n", root->key, root->name);
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

		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;

		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	/* delete_node의 세 번째 경우에서, 
	서브트리 내의 노드 중 그 트리에서 가장 작은 key를 가지는 노드가 복사되는 경우만이  
	이진 탐색 트리의 성질을 만족한다. 이때, 
	왼쪽 트리의 경우 맨 오른쪽 단말 노드,
	오른쪽 트리의 경우 맨 왼쪽 단말 노드가 최소값임이 알려져 있다. */
	while (current->left != NULL) // 여기서는 맨 왼쪽 단말 노드를 찾으러 내려가는 것으로 설정
		current = current->left;

	return current;
}