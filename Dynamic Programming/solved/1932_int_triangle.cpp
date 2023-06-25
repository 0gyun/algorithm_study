/**
 * 2023.06.23
 * 
 * 백준 1932번 문제 (https://www.acmicpc.net/problem/1932)
 * 
 *         7
 *       3   8
 *     8   1   0
 *   2   7   4   4
 * 4   5   2   6   5
 * 
 * 위 그림은 크기가 5인 정수 삼각형의 한 모습이다.
 * 
 * 맨 위층 7부터 시작해서 아래에 있는 수 중 하나를 선택하여 아래층으로 내려올 때, 이제까지 선택된 수의 합이 최대가 되는 경로를 구하는 프로그램을 작성하라. 아래층에 있는 수는 현재 층에서 선택된 수의 대각선 왼쪽 또는 대각선 오른쪽에 있는 것 중에서만 선택할 수 있다.
 * 
 * 삼각형의 크기는 1 이상 500 이하이다. 삼각형을 이루고 있는 각 수는 모두 정수이며, 범위는 0 이상 9999 이하이다.
 * 
 * 입력
 * 
 * 첫째 줄에 삼각형의 크기 n(1 ≤ n ≤ 500)이 주어지고, 둘째 줄부터 n+1번째 줄까지 정수 삼각형이 주어진다.
 * 
 * 출력
 * 
 * 첫째 줄에 합이 최대가 되는 경로에 있는 수의 합을 출력한다.
*/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);

    int total_len = n*(n+1)/2;
    
    // 0행 : 해당 node의 값 / 1행 : 선택할 자식 node의 인덱스 / 2행 : 자신까지 더했을 때 누적 합
    vector< vector<int> > table(3, (vector<int>(total_len+1,0))); 

    /**
     * 이번 문제는 트리의 밑에서부터 생각한다.
     * 각 node는 3가지 정보를 가지고 있다. 
     * 1. 자신의 값, 2. 선택할 자식 node의 index, 3. 자신부터 leaf까지 경로를 따라서 더했을 때의 합
     * 
     * 부모는 각 자식 node의 합 정보를 보고 어느 node를 골라야 최대 값이 나오는지 알 수 있게 된다.
    */
    for(int i = 1; i <= total_len; i++)
    {
        int x;
        scanf("%d", &x);

        table[0][i] = x;
        if(i > total_len - n) table[2][i] = x;
    }

    int k = n-1; // k는 각 Level에서 돌아야 하는 개수를 나타내는 역할
    int i = total_len - n; // 총 돌아야 하는 반복문은 leaf를 뺀 나머지여서 total_len에서 n을 뺀다.
    for(; i > 0; i--)
    {
        if(k == 0)
        {
            n--;
            k = n-1;
        }
        int left_sum = table[2][i + n-1];
        int right_sum = table[2][i + n];
        table[1][i] = (left_sum > right_sum) ? i + n - 1 : i + n;
        table[2][i] = max(left_sum, right_sum) + table[0][i];

        k--;
    }

    printf("%d\n", table[2][1]);
}