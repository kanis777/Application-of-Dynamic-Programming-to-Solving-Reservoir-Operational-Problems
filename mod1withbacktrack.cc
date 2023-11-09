#include<iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;

struct DPEntry{
    int maxBenefit;
    vector<int> selectedReleases;
};

void printDP(const vector<vector<DPEntry>>& dp,int maxCapacity,int timePeriod) {
    cout<< "DP Matrix:" << endl;
    cout<< "    ";
    for (int t = 0; t <= timePeriod; t++) {
        cout << "T" << t << "   ";
    }
    cout << endl;

    for (int st=0;st<=maxCapacity;st++) {
        cout<<"S"<<st<<"|";
        for(int t=0;t<=timePeriod;t++) {
            cout << "Max Benefit: " << dp[st][t].maxBenefit<<" ";
            for (int release : dp[st][t].selectedReleases) {
                cout << release << " ";
            }
            cout << " | ";
        }
        cout << endl;
    }
}

DPEntry maxBenefit(vector<vector<DPEntry>>& dp,int maxCapacity, int timePeriod, vector<int> inflow, vector<vector<int>> benefitRelease, int inflow_max)
{
    //vector<vector<DPEntry>> dp(maxCapacity + 1, vector<DPEntry>(timePeriod + 1, {0, {}}));

    for (int t = timePeriod; t > 0; t--)
    {
        for (int st = 0; st <= maxCapacity; st++)
        {
            for (int rt = 0; rt <= st + inflow[t - 1]; rt++)
            {
                if (st + inflow[t - 1] - rt <= maxCapacity)
                {
                    int a = st + inflow[t - 1] - rt;
                    int newBenefit = benefitRelease[rt][1] + dp[a][t].maxBenefit;

                    if (newBenefit > dp[st][t - 1].maxBenefit)
                    {
                        dp[st][t - 1].maxBenefit = newBenefit;
                        dp[st][t - 1].selectedReleases = dp[a][t].selectedReleases;
                        dp[st][t-1].selectedReleases.clear();
                        dp[st][t - 1].selectedReleases.push_back(rt);
                    }
                    else if (newBenefit == dp[st][t - 1].maxBenefit)
                    {
                        //dp[st][t - 1].selectedReleases = dp[a][t].selectedReleases;
                        dp[st][t - 1].selectedReleases.push_back(rt);
                    }
                }
            }
        }
    }

    printDP(dp, maxCapacity, timePeriod);
    return dp[maxCapacity][0];
}

int main()
{
    // Input parameters
    int maxCapacity = 3;
    int timePeriod = 3;
    vector<int> inflow = {2, 1, 3};
    int inflow_max = *max_element(inflow.begin(), inflow.end());
    vector<vector<int>> benefitRelease = {{0, -100},
                                          {1, 200},
                                          {2, 340},
                                          {3, 450},
                                          {4, 650},
                                          {5, 650},
                                          {6, 420}};

    // Calculate the maximum benefit
    vector<vector<DPEntry>> dp(maxCapacity + 1, vector<DPEntry>(timePeriod + 1, {0, {}}));
    DPEntry maxB = maxBenefit(dp,maxCapacity, timePeriod, inflow, benefitRelease, inflow_max);

    // Print the maximum benefit
    cout << "\nMaximum benefit = " << maxB.maxBenefit << endl;

    vector<int> selectedReleases;
    int st = maxCapacity;
    cout<<"Max benefited release sequence:\n";
    for (int t = 0; t < timePeriod; t++) {
        for (int rt : dp[st][t].selectedReleases) {
            selectedReleases.push_back(rt);
            st = st + inflow[t] - rt;
            cout<<selectedReleases.back()<<" ";
        }
    }
    return 0;
}
