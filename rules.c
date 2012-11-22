#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "rules.h"

enum ACTION
{
	ACTION_LEFT = 1,
	ACTION_RIGHT = 2,
	ACTION_UP = 5,
	ACTION_DOWN = 6,
};

enum TARGET
{
	TARGET_ANY = 1,
	TARGET_NUMBER = 2,
	TARGET_NEXT = 3,
	TARGET_PREVIOUS = 4,
	TARGET_LESS = 5,
	TARGET_LESS_OR_EQUAL = 6,
	TARGET_GREATER = 7,
	TARGET_GREATER_OR_EQUAL = 8,
};

enum RESULT
{
	RESULT_SOURCE = 1,
	RESULT_TARGET = 2,
	RESULT_SUM = 3,
	RESULT_DIFFERENCE_FROM_SOURCE = 4,
	RESULT_DIFFERENCE_FROM_TARGET = 5,
	RESULT_DIFFERENCE_FROM_OPTIONS = 6,
	RESULT_PRODUCT = 7,
	RESULT_DIVISION = 8,
	RESULT_OPTIONS = 9,
	RESULT_MODULUS = 10,
	RESULT_NOTHING = 404,
};

int result(rule *r, int a, int b)
{
	switch (r->result) {
		case RESULT_SOURCE: return a;
		case RESULT_TARGET: return b;
		case RESULT_SUM: return a + b;
		case RESULT_PRODUCT: return b * r->options;
		case RESULT_DIVISION: return b / r->options;
		case RESULT_OPTIONS: return r->options;
		case RESULT_DIFFERENCE_FROM_SOURCE: return a - b;
		case RESULT_DIFFERENCE_FROM_TARGET: return b - a;
		case RESULT_DIFFERENCE_FROM_OPTIONS: return r->options - b;
		case RESULT_MODULUS: ;return (b + r->options) % r->options;
		default: return -1;
	}
}

int rules_ProcessRule(rule *r, int action, int a, int b)
{
	if (r->action != action) return -1;
	if (r->value != -1 && r->value != a) return -1;
	
	switch (r->target) {
		case TARGET_NUMBER: if (b == r->options) return result(r, a, b); break;
		case TARGET_NEXT: if (b == a+1) return result(r, a, b); break;
		case TARGET_PREVIOUS: if (b == a-1) return result(r, a, b); break;
		case TARGET_LESS: if (b < a) return result(r, a, b); break;
		case TARGET_LESS_OR_EQUAL: if (b <= a) return result(r, a, b); break;
		case TARGET_GREATER: if (b > r->result) return result(r, a, b); break;
		case TARGET_GREATER_OR_EQUAL: if (b >= r->result) return result(r, a, b); break;
	}
	
	return -1;
}

rule rules_CreateRule
(const char *action, const char *target, const char *result,
 int value, int options)
{
	int action_num = -1;
	if (strcmp(action, "left") == 0) action_num = ACTION_LEFT;
	else if (strcmp(action, "right") == 0) action_num = ACTION_RIGHT;
	else if (strcmp(action, "up") == 0) action_num = ACTION_UP;
	else if (strcmp(action, "down") == 0) action_num = ACTION_DOWN;
	
	int target_num = -1;
	if (strcmp(target, "any") == 0) target_num = TARGET_ANY;
	else if (strcmp(target, "number") == 0) target_num = TARGET_NUMBER;
	else if (strcmp(target, "next") == 0) target_num = TARGET_NEXT;
	else if (strcmp(target, "previous") == 0) target_num = TARGET_PREVIOUS;
	else if (strcmp(target, "less") == 0) target_num = TARGET_LESS;
	else if (strcmp(target, "less or equal") == 0) {
		target_num = TARGET_LESS_OR_EQUAL;
	}
	else if (strcmp(target, "greater") == 0) target_num = TARGET_GREATER;
	else if (strcmp(target, "greater or equal") == 0) {
		target_num = TARGET_GREATER_OR_EQUAL;
	}
	
	int result_num = -1;
	if (strcmp(action, "source") == 0) result_num = RESULT_SOURCE;
	else if (strcmp(action, "target") == 0) result_num = RESULT_TARGET;
	else if (strcmp(action, "sum") == 0) result_num = RESULT_SUM;
	else if (strcmp(action, "difference from source") == 0) {
		result_num = RESULT_DIFFERENCE_FROM_SOURCE;
	}
	else if (strcmp(action, "difference from target") == 0) {
		result_num = RESULT_DIFFERENCE_FROM_TARGET;
	}
	else if (strcmp(action, "difference from options") == 0) {
		result_num = RESULT_DIFFERENCE_FROM_OPTIONS;
	}
	else if (strcmp(action, "product") == 0) result_num = RESULT_PRODUCT;
	else if (strcmp(action, "division") == 0) result_num = RESULT_DIVISION;
	else if (strcmp(action, "options") == 0) result_num = RESULT_OPTIONS;
	else if (strcmp(action, "modulus") == 0) result_num = RESULT_MODULUS;
	else if (strcmp(action, "nothing") == 0) result_num = RESULT_NOTHING;
	
	return (rule){.action = action_num, .target = target_num,
		.result = result_num, .value = value, .options = options};
}

void test_1(void)
{
	rule r = {
		.action = ACTION_LEFT,
		.target = TARGET_NUMBER,
		.result = RESULT_SOURCE,
		.value = 4,
		.options = 7
	};
	
	assert(rules_ProcessRule(&r, ACTION_LEFT, 4, 7) == 4);
	assert(rules_ProcessRule(&r, ACTION_LEFT, 3, 7) == -1);
	assert(rules_ProcessRule(&r, ACTION_LEFT, 4, 8) == -1);
}

void test_2(void)
{
	rule r = {
		.action = ACTION_LEFT,
		.target = TARGET_NEXT,
		.result = RESULT_MODULUS,
		.value = -1,
		.options = 10
	};
	
	assert(rules_ProcessRule(&r, ACTION_LEFT, 9, 10) == 0);
	assert(rules_ProcessRule(&r, ACTION_LEFT, 4, 5) == 5);
	assert(rules_ProcessRule(&r, ACTION_LEFT, 4, 6) == -1);
	assert(rules_ProcessRule(&r, ACTION_LEFT, 0, 1) == 1);
}


void rules_test(void)
{
	test_1();
	test_2();
}