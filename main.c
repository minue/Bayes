#include <stdio.h>
#include <stdlib.h>

typedef struct _balls {
	int choosePer;
	int chooseNum;
	int accPer;
	int redBall;
	int orangeBall;
	double perO;
	double perR;
	double chooseRate;
	char ballName[31];

	int finalO;
	int finalR;
} balls;

void clear() {
	while (getchar() != '\n');
}

int main() {
	int boxNum = 0, roll = 0;
	int totalBoxper= 0;
	double orange = 0.0, red = 0.0;
	int orangePick = 0, redPick = 0, totalCount;
	balls* Boxes;
	int boxChPer = 0;
	balls currentBox;

	while (boxNum <= 0){
		printf("만들 상자의 개수를 입력해 주세요: ");
		scanf_s("%d", &boxNum);
		clear();
	}

	Boxes = (balls*)malloc(sizeof(balls) * boxNum);

	for (int i = 0; i < 120; i++) {
		printf("=");
	}
	printf("\n");

	for (int i = 0; i < boxNum; i++) {
		
		Boxes[i].choosePer = -1;
		Boxes[i].orangeBall = -1;
		Boxes[i].redBall = -1;

		printf("%d번째 상자의 이름을 30바이트 이내로 입력해 주세요: ", i + 1);
		scanf_s("%s", Boxes[i].ballName, sizeof(char) * 31);

		while (Boxes[i].choosePer <= 0) {
			printf("해당 상자가 나올 확률 비를 양수로 입력하세요: ");
			scanf_s("%d", &Boxes[i].choosePer);
			boxChPer += Boxes[i].choosePer;
			Boxes[i].accPer = boxChPer;
			Boxes[i].chooseNum = 0;
			Boxes[i].finalR = 0;
			Boxes[i].finalO = 0;
			clear();
		}

		while (Boxes[i].orangeBall < 0) {
			printf("해당 상자안에 있을 오렌지색 공의 개수를 입력하세요: ");
			scanf_s("%d", &Boxes[i].orangeBall);
			clear();
		}

		while (Boxes[i].redBall < 0) {
			printf("해당 상자안에 있을 빨간색 공의 개수를 입력하세요: ");
			scanf_s("%d", &Boxes[i].redBall);
			clear();
		}

		for (int i = 0; i < 120; i++) {
			printf("=");
		}
		printf("\n");

		Boxes[i].perO = (double)Boxes[i].orangeBall / (Boxes[i].orangeBall + Boxes[i].redBall);
		Boxes[i].perR = 1 - Boxes[i].perO;
		totalBoxper += Boxes[i].choosePer;
	}

	for (int i = 0; i < boxNum; i++) {
		Boxes[i].chooseRate = (double)Boxes[i].choosePer / totalBoxper;
		orange += Boxes[i].perO * Boxes[i].chooseRate;
		red += Boxes[i].perR * Boxes[i].chooseRate;
	}
	printf("\n주어진 데이터는 다음과 같습니다.\n\n");
	printf("\n(B는 상자 종류, C는 뽑힌 공의 색)\n");

	for (int i = 0; i < 120; i++) {
		printf("=");
	}

	printf("\n");
	printf("\n");
	printf("%31s||%10s||%10s||%10s||\n", "박스 이름", "선택 확률", "오렌지 색", "빨간 공");

	for (int i = 0; i < 120; i++) {
		printf("=");
	}
	
	printf("\n");

	double tempPer;
	
	for (int i = 0; i < boxNum; i++) {
		printf("%31s||%10d||%10d||%10d\n", Boxes[i].ballName, Boxes[i].choosePer, Boxes[i].orangeBall, Boxes[i].redBall);
		
		printf("%31s||%9.2f%%||%9.2f%%||%9.2f%%\n", "", Boxes[i].chooseRate * 100, Boxes[i].perO * 100, Boxes[i].perR * 100);
		for (int i = 0; i < 120; i++) {
			printf("-");
		}

		for (int i = 0; i < 30; i++) {
			printf(" ");
		}
		printf("- P(C = red | B = %s)    = %10.2lf%%\n", Boxes[i].ballName, Boxes[i].perR * 100);
		

		for (int i = 0; i < 30; i++) {
			printf(" ");
		}
		printf("- P(C = orange | B = %s) = %10.2lf%%\n", Boxes[i].ballName, Boxes[i].perO * 100);
		

		for (int i = 0; i < 30; i++) {
			printf(" ");
		}
		tempPer = Boxes[i].perR * red / Boxes[i].chooseRate;
		printf("- P(B = %s | C = red)    = %10.2lf%%\n", Boxes[i].ballName, tempPer * 100);
		

		for (int i = 0; i < 30; i++) {
			printf(" ");
		}
		tempPer = Boxes[i].perO * orange / Boxes[i].chooseRate;
		printf("- P(B = %s | C = orange) = %10.2lf%%\n", Boxes[i].ballName, tempPer * 100);

		for (int i = 0; i < 120; i++) {
			printf("=");
		}
		printf("\n");
	}

	printf("예상 결과: red %10.2f%% / orange %10.2f%%\n", orange * 100, red * 100);

	while (roll <= 0) {
		printf("예측 횟수를 입력해 주세요: ");
		scanf_s("%d", &roll);
		clear();
	}

	int k = 0;

	printf("\n");
	for (int i = 0; i < 100; i++) {
		printf("=");
	}
	printf("\n");

	int ch;
	int index = 0;

	for (int i = 0; i < roll; i++) {
		ch = rand() % totalBoxper;

		while (ch + 1 > Boxes[index].accPer) {
			index++;
		}

		currentBox = Boxes[index];
		totalCount = currentBox.orangeBall + currentBox.redBall;
		if (rand() % totalCount < currentBox.orangeBall) {
			orangePick++;
			printf("\r| O (%s) |\n", currentBox.ballName);
			Boxes[index].finalO++;
		}
		else {
			redPick++;
			printf("\r| R (%s) |\n", currentBox.ballName);
			Boxes[index].finalR++;
		}
		if (i % 20 == 19) {
			printf("\n");
			for (int i = 0; i < 100; i++) {
				printf("=");
			}
			printf("\n");
		}

		Boxes[index].chooseNum++;
		index = 0;
	}
	printf("\n예측 최종 결과: red %10.2f%% / orange %10.2f%%\n", (double)redPick * 100 / roll, (double)orangePick * 100 / roll);
	printf("빨간 공 나온 수: %d / 오렌지색 공 나온 수: %d\n", redPick, orangePick);

	for (int i = 0; i < boxNum; i++) {
		printf("\n");
		
		for (int i = 0; i < 100; i++) {
			printf("=");
		}
		printf("\n");

		printf("%s 상자의 선택 횟수: %d / 확률: %.2f%%\n", Boxes[i].ballName, Boxes[i].chooseNum, (double)Boxes[i].chooseNum / roll * 100);
		printf("- P(C = red | B = %s) = %.2f%%, %d / %d\n", Boxes[i].ballName, (double)Boxes[i].finalR / Boxes[i].chooseNum * 100,
			Boxes[i].finalR, Boxes[i].chooseNum);
		printf("- P(C = orange | B = %s) = %.2f%%, %d / %d\n", Boxes[i].ballName, (double)Boxes[i].finalO / Boxes[i].chooseNum * 100,
			Boxes[i].finalO, Boxes[i].chooseNum);
		printf("- P(B = %s | C = red) = %.2f%%, %d / %d\n", Boxes[i].ballName, (double)Boxes[i].finalR / redPick * 100,
			Boxes[i].finalR, redPick);
		printf("- P(B = %s | C = orange) = %.2f%%, %d / %d\n", Boxes[i].ballName, (double)Boxes[i].finalO / orangePick * 100,
			Boxes[i].finalO, orangePick);
	}


	for (int i = 0; i < 100; i++) {
		printf("=");
	}

	system("pause > nul");
	return 0;
}