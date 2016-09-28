// 0928

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 结构体：字符串对
typedef struct string_pair
{
	char *src_substring;
	char *dst_substring;
} STRING_PAIR;

// 结构体：字符串对结点
typedef struct pair_node
{
	STRING_PAIR *pair;
	struct pair_node *next;
} PAIR_NODE;

// 结构体：字符串对列表
typedef struct pair_list
{
	PAIR_NODE *first_pair;
	PAIR_NODE *last_pair;
} PAIR_LIST;

// 结构体：栈
typedef struct stack_t
{
	STRING_PAIR **pair;
	int top_index;
	int size;
} STACK;

// 结构体：目标字符串结点
typedef struct dst_string_node
{
	char *dst_string;
	struct dst_string_node *next;
} DST_STRING_NODE;

// 结构体：目标字符串列表
typedef struct dst_string_list
{
	char *first_dst_string;
	char *last_dst_string;
} DST_STRING_LIST;

// 为源字符串匹配对应的符合规则的目标字符串
void CreateGroup(STACK *stack, PAIR_LIST *list, const char *src_string);
int IsHeaderSubStr(const char *sub_str, const char *src_string);
char *ConvertToStrFromStack(STACK *stack);
void AddToDstString(DST_STRING_LIST *dst_list, char *string);

PAIR_LIST pairlist;
DST_STRING_LIST *dst_list;

void CreateGroup(STACK *stack, PAIR_LIST *list, const char *src_string)
{
	PAIR_NODE *pNode = pairlist->first_pair;

	while (pNode != NULL)
	{
		// 判断源字符串的各段是否在规则表中
		if (IsHeaderSubStr(pNode->pair->src_substring, src_string))
		{
			// 将当前结点压栈进字符串栈
			Push(stack, pNode->pair);
			printf("Push %s--%s\n", pNode->pair->src_substring, pNode->pair->dst_substring);

			// 判断是否完全相同，若相同，说明src_string匹配到结尾，整个栈规则有效可行
			if (strcmp(pNode->pair->src_substring, src_string) == 0)
			{
				char *tmp = ConvertToStrFromStack(stack);
				AddToDstString(dst_list, tmp);
			}

			// 否则，递归匹配src_string剩余字符串
			else
			{
				CreateGroup(stack, pairlist, src_string + strlen(pNode->pair->src_substring));
			}

			Pop(stack);
			printf("Pop %s--%s\n", pNode->pair->src_substring, pNode->pair->dst_substring);			
		}

		pNode = pNode->next;
	}
}

int IsHeaderSubStr(const char *sub_str, const char *src_string)
{
	int i;
	int len_sub_str = strlen(sub_str);
	int len_src_string = strlen(src_string);

	if (len_sub_str > len_src_string)
		return 0;
	
	else
	{
		for (i = 0; i < len_sub_str; i++)
		{
			if (sub_str[i] != src_string[i])
				return 0;
		}
	}

	return 1;
}