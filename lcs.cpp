#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;

class source{
    public:
        int x;
        int y;
        source(){
            x=-1;
            y=-1;
        };
        void get_lastUsed(int a, int b){
            x=a;
            y=b;
        };
};

int main (){
    string seq1, seq2;
    cout << "Enter the fisrt sequence: " << endl;
    cin >> seq1;
    cout << "Enter the second sequence:" << endl;
    cin >> seq2;

    int seq1_len = strlen(seq1.c_str());
    int seq2_len = strlen(seq2.c_str());

    vector<vector<int>> dp(seq1_len + 1, vector<int>(seq2_len + 1, 0));
    vector<vector<source>> record(seq1_len, vector<source>(seq2_len, source()));

    for(int i=0; i < seq1_len + 1; i++)
    {
        for(int j=0; j < seq2_len + 1; j++)
        {
            if(i==0 || j==0)
            {
                dp[i][j] = 0;
            }
            else if(seq1[i-1] == seq2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
                record[i-1][j-1].get_lastUsed(i-2, j-2);
            }
            else if(seq1[i-1] != seq2[j-1])
            {
                if(dp[i-1][j] > dp[i][j-1])
                {
                    dp[i][j] = dp[i-1][j];
                    record[i-1][j-1].get_lastUsed(i-2, j-1);
                }
                else if(dp[i-1][j] <= dp[i][j-1])
                {
                    dp[i][j] = dp[i][j-1];
                    record[i-1][j-1].get_lastUsed(i-1, j-2);
                }
            }
        }
    }

    vector<char> lcs;
    int row = seq1_len - 1;
    int col = seq2_len - 1;

    while((record[row][col].x != -1) && (record[row][col].y != -1))
    {
        int length = dp[row][col];
        int x = record[row][col].x;
        int y = record[row][col].y;

        if((x == row-1) && (y == col-1))
            lcs.push_back(seq1[row]);

        row = x;
        col = y;
        
    }
    lcs.push_back(seq1[row]);

    cout << "The longest common subsequence is ";
    for (vector<char>::reverse_iterator i = lcs.rbegin(); 
        i != lcs.rend(); ++i ) { 
            cout << *i;
    } 

    cout << "\nlcs's length is "<< dp[seq1_len][seq2_len] << endl;
    /*for (int i = 0; i < record.size(); i++)
    {
        for (int j = 0; j < record[i].size(); j++)
        {
            cout << setw(10) << "x = " << setw(3) << record[i][j].x << " y = " << setw(3) << record[i][j].y << " ";
        }
        cout << endl;
    }*/
}