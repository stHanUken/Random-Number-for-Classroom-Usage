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

bool fromCmd;
int nums[MAX];
int excs[MAX];
char cmd[MAX];

void init(int argc)
{
	memset(nums, 0, sizeof(nums));
	memset(excs, 0, sizeof(excs));
	memset(cmd, '\0', sizeof(cmd));
	srand(time(NULL));
	fromCmd = false;
	if (argc != 1)	fromCmd = true;
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

int main(int argc, char const *argv[])
{
	init(argc);
	int n = DEFAULT_N, l = DEFAULT_L, r = DEFAULT_R, excn = 0, status = 0;
	bool isSingle = false, isRing = false;
	char t = '\0';
	if (fromCmd == false) {
		scanf("%d", &n);
		for (int i = 0; ; i ++) {
			t = getchar();
			if ((t == ' ') && i == 0) {
				i --;
				continue;
			}
			if ((t == ' ' && i != 0) || t == '\n') {
				if (strcmp(cmd, "-e") == 0 || strcmp(cmd, "/e") == 0) {
					scanf("%d", &excn);
					for (int j = 0; j < excn; j ++)
						scanf("%d", &excs[j]);
				}
				else if (strcmp(cmd, "-z") == 0 || strcmp(cmd, "/z") == 0)	scanf("%d%d", &l, &r);
				else if (strcmp(cmd, "-s") == 0 || strcmp(cmd, "/s") == 0)	isSingle = true;
				else if (strcmp(cmd, "-r") == 0 || strcmp(cmd, "/r") == 0)	isRing = true;
				memset(cmd, '\0', sizeof(cmd));
				if (t == '\n')	break;
				i = -1;
				continue;
			}
			cmd[i] = t;
		}
	} else {
		sscanf(argv[1], "%d", &n);
		for (int i = 2; i < argc; i ++) {
			if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "/e") == 0) {
				sscanf(argv[++i], "%d", &excn);
				for (int j = 0; j < excn; j ++)
					sscanf(argv[++i], "%d", &excs[j]);
			}
			if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "/z") == 0) {
				sscanf(argv[++i], "%d", &l);
				sscanf(argv[++i], "%d", &r);
			}
			else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "/s") == 0)	isSingle = true;
			else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "/r") == 0)	isRing = true;
		}
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
		if (isSingle == true)	getch();
		printf("%d ", nums[i]);
		if (isSingle == true && isRing == true)	printf("\7");
	}
	printf("\nPress any key to continue...");
	getch();
	return 0;
}
