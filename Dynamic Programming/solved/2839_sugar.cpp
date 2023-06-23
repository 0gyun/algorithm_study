/**
 * 2023.06.19
 * 
 * 백준 2839번 문제 (https://www.acmicpc.net/problem/2839)
 * 
 * 상근이는 요즘 설탕공장에서 설탕을 배달하고 있다. 상근이는 지금 사탕가게에 설탕을 정확하게 N킬로그램을 배달해야 한다. 설탕공장에서 만드는 설탕은 봉지에 담겨져 있다. 
 * 봉지는 3킬로그램 봉지와 5킬로그램 봉지가 있다.
 * 상근이는 귀찮기 때문에, 최대한 적은 봉지를 들고 가려고 한다. 예를 들어, 18킬로그램 설탕을 배달해야 할 때, 3킬로그램 봉지 6개를 가져가도 되지만, 5킬로그램 3개와 3킬로그램 1개를 배달하면, 더 적은 개수의 봉지를 배달할 수 있다.
 * 상근이가 설탕을 정확하게 N킬로그램 배달해야 할 때, 봉지 몇 개를 가져가면 되는지 그 수를 구하는 프로그램을 작성하시오.
 * 
 * 입력
 * 
 * 첫째 줄에 N이 주어진다. (3 ≤ N ≤ 5000)
 * 
 * 출력
 * 
 * 상근이가 배달하는 봉지의 최소 개수를 출력한다. 만약, 정확하게 N킬로그램을 만들 수 없다면 -1을 출력한다.
*/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n; // 상근이가 배달해야할 설탕 무게
    scanf("%d", &n);

    /**
     * 이번 문제의 핵심 부분으로 DP를 사용한다.
     * 
     * 행 : 3kg, 5kg 봉지를 추가할 수 있는지? 있다면 추가했을 때 봉지의 개수
     * 열 : 현재 총 봉지의 무게
     * 
     * 예)
     *       1   2   3   4   5   6   7   8   9  10
     * 3kg  -1  -1   1  -1  -1   2  -1   2   3  -1
     * 5kg  -1  -1  -1  -1   1  -1  -1   2  -1  -1
     * 
     * 풀이법)
     * 임의의 m 무게일 때, 3kg를 들었을 때 m이 된 경우와 5kg를 들었을 때 m이 된 경우로 나눠서 생각한다.
     * 따라서 m-3 열의 값들을 비교해서 둘 다 -1이면 3kg를 들었을 때 m을 만들 수 없다는 뜻이 된다.
     * m-3 열의 값들 중 하나라도 양수가 있다면 3kg를 들었을 때 m을 만들 수 있다는 것이고 두 값이 모두 양수라면 둘 중 적은 수에 +1을 한다.
     * m-5의 경우도 동일하게 한 다음 최종적으로 N 무게에 해당하는 열의 값들을 비교해서 풀이할 수 있다.
     * 
    */

    vector< vector<int> > numbers(2, vector<int>(n+1, -1)); // 2 x n+1 2차원 벡터를 선언하고 -1로 초기화 한다.

    numbers[0][3] = 1; // 3kg은 한 봉지로 초기화
    numbers[1][5] = 1; // 5kg은 한 봉지로 초기화
    for(int i = 6; i <= n; i++)
    {
        // 3kg를 추가했다고 가정한 경우
        int firstRowAdd3 = numbers[0][i-3];
        int secondRowAdd3 = numbers[1][i-3];

        // 5kg를 추가했다고 가정한 경우
        int firstRowAdd5 = numbers[0][i-5];
        int secondRowAdd5 = numbers[1][i-5];

        int *add3 = &(numbers[0][i]);
        int *add5 = &(numbers[1][i]);

        if(!firstRowAdd3 && !secondRowAdd3) *add3 = -1; // 둘 다 -1인 경우
        else if(firstRowAdd3 > 0 && secondRowAdd3 > 0) *add3 = min(firstRowAdd3, secondRowAdd3) + 1; // 둘 다 양수인 경우
        else if(firstRowAdd3 * secondRowAdd3 < 0) *add3 = max(firstRowAdd3, secondRowAdd3) + 1; // 둘 중 하나만 양수인 경우

        if(!firstRowAdd5 && !secondRowAdd5) *add5 = -1;// 둘 다 -1인 경우
        else if(firstRowAdd5 > 0 && secondRowAdd5 > 0) *add5 = min(firstRowAdd5, secondRowAdd5) + 1;// 둘 다 양수인 경우
        else if(firstRowAdd5 * secondRowAdd5 < 0) *add5 = max(firstRowAdd5, secondRowAdd5) + 1;// 둘 중 하나만 양수인 경우
        
    }
    int answer;
    if(!numbers[0][n] && !numbers[1][n]) answer = -1; // 둘 다 -1인 경우
    else{
        int add3 = (numbers[0][n]) ? numbers[0][n] : 0;
        int add5 = (numbers[1][n]) ? numbers[1][n] : 0;
        answer = (add3 * add5 > 0) ? min(add3, add5) : max(add3, add5);
    }
    printf("%d\n", answer);
}