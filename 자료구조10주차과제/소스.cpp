#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
#define MAXLEN 1000

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

	printf("==== 학생 정보 시스템 ====\n");
	printf("(1) 학생 정보 탐색\n");
	printf("(2) 학생 정보 삭제\n");
	printf("(3) 전체 출력\n");
	printf("(0) 종료\n");
	printf("선택: ");
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
			printf("학번 입력: ");
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