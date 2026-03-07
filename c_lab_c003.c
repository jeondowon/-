/*
Programming Studio C003
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5]); // 5개의 호실 중 빈 베드가 있는 방을 찾아낸다. (리턴값 1~5)
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc); // 배정 결과를 출력한다.

int main(){
	char mnames[10][20]; // 남학생명단(최대 10명)
	int mroom[10];		// 남학생명단별 호실 배정 목록
	char wnames[10][20]; // 여학생명단(최대 10명)
	int wroom[10];		// 여학생명단별 호실 배정 목록
	int person[2][5]={0};   // 2개 층별 5개 호실의 배정 인원 수 
	int mcount=0, wcount=0; // 인원 합계 (남, 여)
	int menu;

	srand(time(0));
	printf("===========================================\n");
	printf("생활관 호실 배정 프로그램\n");
	printf("===========================================\n");
	while(1){
		printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
		scanf("%d", &menu);
		if(menu==0) break;
		else if(menu==1) {
			if(mcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", mnames[mcount]);
			int roomno = findRoom(person[0]);
			mroom[mcount] = 100+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount], mroom[mcount]);
			mcount++;
		}
		else if(menu==2) {
			if(wcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				continue;
			}
			printf("학생 이름은? > ");
			scanf("%s", wnames[wcount]);
			int roomno = findRoom(person[1]);
			wroom[wcount] = 200+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount], wroom[wcount]);
			wcount++;
		}
	}

	printf("===========================================\n");
	printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
	printf("===========================================\n");
	printReport(mnames, mroom, mcount, wnames, wroom, wcount);

	return 0;
}

int findRoom(int persons[5]){ 

    /*남자/여자 방 다섯개를 뜻하는 persons배열을 파라미터로 받음.
    인원 추가가 가능한 방을 찾아내고 랜덤으로 방을 지정해야함. */

    int joinable[5]; // 추가배정 가능한 방들을 찾아서 담아둘 배열
	int count = 0;  //가능한 방 갯수

	// 인원이 2명 미만인 방만 저장
	for(int i = 0; i < 5; i++){
		if(persons[i] < 2){
			joinable[count] = i;    // 배정가능한 방 번호 i 저장
			count++;
		}
	}

	// 모든 방이 가득 찬 경우
	if(count == 0){
		return -1;
	}

	// 후보 방들 중 랜덤 선택
	int num = rand() % count;   // 가능한 방 갯수만큼의 경우의 수 안에서 랜덤숫자 만들기
	int roomnum = joinable[num];  // '랜덤숫자'번째 방을 입실할 방으로 선택

	// 선택된 방의 인원 1명 증가
	persons[roomnum]++;

	// 호실 번호 1~5를 반환 후 이 값을 100에 더하여 출력해야함. 
	return roomnum + 1; // rumnum이 0~4이기 때문에 1~5를 반환하기 위해 +1

}

void printReport(char mn[10][20], int mr[10], int mc, // 남학생 명단, 배정호실번호, 인원
    char wn[10][20], int wr[10], int wc){   // 여학생 명단, 배정호실번호, 인원

    int room;

	// 남학생
	printf("남학생 명단 (%d명)\n", mc);
	for(int i = 0; i < mc; i++){    // 저장된 남학생 인원만큼 반복문실행
		printf("%d. %s [%d호]\n", i+1, mn[i], mr[i]);   // 저장된 순서대로 출력
	}
	printf("\n");

	// 여학생
	printf("여학생 명단 (%d명)\n", wc); // 저장된 여학생 인원만큼 반복문 실행
    for(int i = 0; i < wc; i++){
        printf("%d. %s [%d호]\n",i+1, wn[i], wr[i]);    // 저장된 순서대로 출력
    }
	printf("\n");

	printf("호실별 배정 명단\n");

	// 남학생방
	for(room = 101; room <= 105; room++){
		printf("%d호 : ", room);
		int assigned = 0;   // 배정된 학생이 있는지 판별하기 위한 변수 선언

		for(int i = 0; i < mc; i++){    //등록된 남학생 수만큼 반복
			if(mr[i] == room){  // i번째 학생의 배정 호실이 현재 검사중인 room과 같은지 확인
				printf("%s ", mn[i]);
				assigned = 1;   //방에 학생이 있음
			}
		}

		if(assigned == 0){  //배정된 학생이 없는 경우 아무것도 출력하지 않음
			printf("");
		}
		printf("\n");
	}

	// 여학생방, 남학생방 코드와 동일하게 구동
	for(room = 201; room <= 205; room++){
		printf("%d호 : ", room);
		int assigned = 0;

		for(int i = 0; i < wc; i++){
			if(wr[i] == room){
				printf("%s ", wn[i]);
				assigned = 1;
			}
		}

		if(assigned == 0){
			printf("");
		}
		printf("\n");
	}
}
