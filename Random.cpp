#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <algorithm>
#include <windows.h>

#define MAX 256
#define MAXIMUM 32767
#define DEFAULT_N 51
#define DEFAULT_L 1
#define DEFAULT_R 51

int nums[MAX];
int excs[MAX];
char cmd[MAX];

void init()
{
	memset(nums, 0, sizeof(nums));
	memset(excs, 0, sizeof(excs));
	memset(cmd, '\0', sizeof(cmd));
	srand(time(NULL));
}

int generate(int n, int l, int r, int excn, int* exc, int* des)
{
	if (l > r)	return -1;
	if (n + excn > r - l + 1)	return -2;
	if (l < 0 || r > MAXIMUM)	return -3;
	for (int i = 0; i < excn; i ++)
		for (int j = 0; j < i; j ++)
			if (exc[i] == exc[j])	return -4;
	int l0 = l - l / (r - l + 1) * (r - l + 1), r0 = r + (MAXIMUM - r) / (r - l + 1) * (r - l + 1), t = 0;
	for (int i = 0; i < n; i ++) {
		bool isexist = false;
		t = rand();
		if (t < l0 || t > r0) {
			i --;
			continue;
		}
		t = (t - l0) % (r - l + 1) + l;
		for (int j = 0; j < i; j ++) {
			if (des[j] == t) {
				isexist = true;
				break;
			}
		}
		for (int j = 0; j < excn; j ++) {
			if (excs[j] == t) {
				isexist = true;
				break;
			}
		}
		if (isexist == true) {
			i --;
			continue;
		}
		des[i] = t;
	}
	return 0;
}

int main()
{
	init();
	int n = DEFAULT_N, l = DEFAULT_L, r = DEFAULT_R, excn = 0, status = 0;
	bool isSingle = false, isRing = false;
	char t = '\0';
	scanf("%d", &n);
	for (int i = 0; ; i ++) {
		t = getchar();
		if (t == ' ' && i == 0) {
			i --;
			continue;
		}
		if ((t == ' ' || t == '\n') && i != 0) {
			if (!strcmp(cmd, "-e")) {
				scanf("%d", &excn);
				for (int j = 0; j < excn; j ++)
					scanf("%d", &excs[j]);
				memset(cmd, '\0', sizeof(cmd));
			}
			if (!strcmp(cmd, "-z")) {
				scanf("%d %d", &l, &r);
				memset(cmd, '\0', sizeof(cmd));
			}
			if (!strcmp(cmd, "-s")) {
				isSingle = true;
				memset(cmd, '\0', sizeof(cmd));
			}
			if (!strcmp(cmd, "-r")){
				isRing = true;
				memset(cmd, '\0', sizeof(cmd));
			}
			i = -1;
			continue;
		}
		if (t == '\n')	break;
		cmd[i] = t;
	}
	status = generate(n, l, r, excn, excs, nums);
	if (status != 0) {
		switch (status) {
			case -1:
				printf("Border Error: Left Larger Than Right\n");
				break;
			case -2:
				printf("Number Error: Required Numbers Larger Than Available\n");
				break;
			case -3:
				printf("Border Error: Border Numbers Go Over Available\n");
				break;
			case -4:
				printf("Number Error: Exceptions Repeat\n");
				break;
		}
		printf("Press any key to continue...");
		getch();
		return status;
	}
	std::sort(nums, nums + n);
	for (int i = 0; i < n; i ++) {
		printf("%d ", nums[i]);
		if (isSingle == true) {
			getch();
			if (isRing == true)	printf("\7");
		}
	}
	printf("\nPress any key to continue...");
	getch();
	return 0;
}

