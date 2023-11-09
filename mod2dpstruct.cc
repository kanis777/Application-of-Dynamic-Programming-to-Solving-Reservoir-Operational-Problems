#include <iostream>
#include<iomanip>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

struct DPstruct
{
    int value;
    vector<int> release;
};

void printDP(vector<vector<DPstruct>>& dp, int max_cap, int com_no) {
    // Determine the maximum width for each column
    vector<int> columnWidths(com_no, 0);

    for (int j = 0; j < com_no; j++) {
        for (int i = 0; i <= max_cap; i++) {
            int valueWidth = to_string(dp[i][j].value).length();
            columnWidths[j] = max(columnWidths[j], valueWidth);

            for (int x : dp[i][j].release) {
                int releaseWidth = to_string(x).length();
                columnWidths[j] = max(columnWidths[j], releaseWidth);
            }
        }
    }

    // Print the table header
    cout << setw(columnWidths[0]) << "Value";
    for (int j = 0; j < com_no; j++) {
        cout << setw(columnWidths[j]) << "x";
    }
    cout << endl;

    // Print the table data
    for (int i = 0; i <= max_cap; i++) {
        for (int j = 0; j < com_no; j++) {
            cout << setw(columnWidths[j]) << dp[i][j].value << " (x = ";
            for (int x_idx = 0; x_idx < dp[i][j].release.size(); x_idx++) {
                cout << setw(columnWidths[j]) << dp[i][j].release[x_idx];
                if (x_idx < dp[i][j].release.size() - 1) {
                    cout << ",";
                }
            }
            cout << ")";
        }
        cout << endl;
    }
}


/*void backtrack(vector<vector<int> >& inp, vector<vector<DPstruct> >& dp, int max_cap, int com_no)
{
    int water=10;
    int stage=0;
    vector <int> val;
    cout<<endl<<"Com 1 "<<setw(10)<<"Com 2 "<<setw(10)<<"Com 3 ";
    for(int x_idx=0;x_idx<dp[max_cap][stage].release.size();x_idx++)
    {
        water=10;
        stage=0;
        //cout<<"Hi";
        while(water!=0)
        {
            for(int in=0;in<dp[max_cap][stage].release.size();in++)
            {
                val.push_back(dp[water][stage].release[in]);
                cout<<endl;
                /*for(int i=0;i<val.size();i++)
                {
                    cout<<val[i]<<setw(10);
                }*/
                /*water=water-val[stage];
                stage++;
            }
        }
        cout<<endl;
        for(int i=0;i<val.size();i++)
        {
            cout<<val[i]<<setw(10);
        }
        val.clear();
    }

}
*/

int maximum(vector<vector<int> >& inp, vector<vector<DPstruct> >& dp, int max_cap, int com_no)
{
    for(int i=0;i<=max_cap;i++)
    {
        for(int j=0;j<com_no;j++)
        {
            dp[i][j].value=0;
            dp[i][j].release.clear();
        }
    }

    for(int i=0;i<=max_cap;i++)
    {
        dp[i][com_no-1].value=inp[i][com_no-1];
        dp[i][com_no-1].release.push_back(i);
    }

    for(int c=com_no-2;c>= 0;c--)
    {
        for(int s=0;s<=max_cap;s++)
         {
            for(int x=0;x<=max_cap;x++)
            {
                if((s - x)>=0)
                {
                    int new_value=inp[x][c]+dp[s - x][c + 1].value;
                    if (new_value>dp[s][c].value)
                    {
                        dp[s][c].value = new_value;
                        dp[s][c].release=dp[s-x][c+1].release;
                        dp[s][c].release.clear();
                        dp[s][c].release.push_back(x);
                    }
                    else if(new_value==dp[s][c].value)
                    {
                        dp[s][c].release.push_back(x);
                    }
                }
            }
        }
    }

    // Print the entire dp matrix with corresponding x values
    cout << "DP : " << endl;
    printDP(dp,max_cap,com_no);
    return dp[max_cap][0].value;
}


void backtrack(vector<vector<int> >& inp, vector<vector<DPstruct> >& dp, int max_cap, int com_no, int current_capacity, int current_community, vector<int>& allocation)
{
    if (current_community==com_no) // A complete allocation is found
    {
        cout << "Allocation: ";
        for (int i=0;i<com_no;i++)
        {
            cout<<"Community "<<(i + 1)<<": "<<allocation[i]<<" units ";
        }
        cout<<endl;
        return;
    }

    for(int i=0;i<dp[current_capacity][current_community].release.size();i++)
    {
        int selected_x=dp[current_capacity][current_community].release[i];
        allocation[current_community]=selected_x;
        backtrack(inp,dp,max_cap,com_no,current_capacity-selected_x,current_community+1,allocation);
    }
}

void findAllocations(vector<vector<int> >& inp, vector<vector<DPstruct> >& dp, int max_cap, int com_no)
{
    vector<int> allocation(com_no,0); // To store the current allocation
    backtrack(inp,dp,max_cap,com_no,max_cap,0,allocation);
}


int main() {
    int com_no;
    int max_cap;
    cout<<"Enter maximum units of water to be allocated: ";
    cin >> max_cap;
    cout<<"Enter the number of communities: ";
    cin >>com_no;

    vector<vector<int> > inp(max_cap + 1, vector<int>(com_no, 0));
    vector<vector<DPstruct> > dp(max_cap + 1, vector<DPstruct>(com_no));//2D VECTOR WHICH HAS STRUCT VALUES

    for(int i=0;i<=max_cap;i++)
    {
        int community1=12*i-i*i;
        int community2=8*i-i*i;
        int community3=18*i-3*i*i;

        inp[i][0]=community1;
        inp[i][1]=community2;
        inp[i][2]=community3;
    }

    //input matrix
    cout << "Input Matrix:" << endl;
    for(int i=0;i<=max_cap;i++)
    {
        for(int j=0; j<com_no;j++)
        {
            cout<<inp[i][j]<< " ";
        }
        cout<<endl;
    }

    int result=maximum(inp,dp,max_cap,com_no);
    cout<<"Maximum value: " <<result<<endl;
    //backtrack(dp,max_cap,com_no);
    cout << "All Possible Allocations:" << endl;
    findAllocations(inp, dp, max_cap, com_no);
}
