#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int MaxX = 100;
const int MaxY = 100;
const int MaxC = 10;

int sky[MaxX+5][MaxY+5];
LL sum[MaxC+1][MaxX+5][MaxY+5];

void calcSum(int t)
{
    for (int x = MaxX+1; x >= 0; x--)
        for (int y = MaxY+1; y >= 0; y--)
            sum[t][x][y] = 0;

    sum[t][1][1] = sky[1][1];
    for (int y = 2; y <=  MaxY; y++)
        sum[t][1][y] = sum[t][1][y-1] + sky[1][y];

    for (int x = 2; x <= MaxX; x++)
        for (int y = 1; y <= MaxY; y++)
            sum[t][x][y] = sum[t][x-1][y] + sum[t][x][y-1] + sky[x][y] - sum[t][x-1][y-1];
}

LL getSum(int t, int x1, int y1, int x2, int y2)
{
    //cout << "sum: " << sum[t][x2][y2] << " " <<  sum[t][x1-1][y2] << " " <<  sum[t][x2][y1-1] << " " <<  sum[t][x1-1][y1-1] << endl;
    return sum[t][x2][y2] - sum[t][x1-1][y2] - sum[t][x2][y1-1] + sum[t][x1-1][y1-1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    for (int x = MaxX+1; x >= 0; x--)
        for (int y = MaxY+1; y >= 0; y--)
            sky[x][y] = 0;

    int n, q, c;
    cin >> n >> q >> c;
    vector<pair<pii, int>> stars;
    for (int i = 0; i < n; i++)
    {
        int x,y,s;
        cin >> x >> y >> s;
        sky[x][y] += s;
        stars.push_back({{x, y}, s});
    }

    calcSum(0);
    for (int i = 1; i <= c; i++)
    {
        for (int x = MaxX+1; x >= 0; x--)
            for (int y = MaxY+1; y >= 0; y--)
                sky[x][y] = 0;

        for (pair<pii, int> tmp : stars)
        {
            pii star = tmp.first;
            sky[star.first][star.second] += (tmp.second + i) % (c + 1);
        }
        calcSum(i);

        /*
        cout << i << endl;
        for (int y = 0; y <= 5; y++)
        {
            for (int x = 0; x <= 5; x++)
                cout << sum[i][x][y] << " ";
            cout << endl;
        }
        cout << endl;
*/
    }

    vector<LL> ans;
    int t, x1, x2, y1, y2;
    for (int i = 0; i < q; i++)
    {
        cin >> t >> x1 >> y1 >> x2 >> y2;
        ans.push_back(getSum(t % (c + 1), x1, y1, x2, y2));
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << endl;

	return 0;
}
