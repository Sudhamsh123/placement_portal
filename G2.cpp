
/*

📘 Problem Statement:
You are given an array arr of length n. You can perform the following two types of operations:

Decrement Operation: You can reduce any element of the array by 1. You are allowed to perform this operation at most x times total (not per element).

Zeroing Operation: You can instantly make any element 0. You are allowed to perform this operation at most y times total.

🧠 Goal:
Find the maximum length of a contiguous subarray such that all its elements can be made 0 by applying at most x decrement operations and at most y zeroing operations.



*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void print_yes() {
    cout << "YES" << endl;
}

void print_no() {
    cout << "NO" << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;
    while (t--)
    {
        ll n,x,y;
        cin>>n>>x>>y;

        vector<ll>arr(n);

        for(ll i = 0;i < n;i++){
            cin>>arr[i];
        }

        ll left = 0,right = 0;
        ll presSum = 0;
        ll count = 0;

        while(right < n){
            presSum += arr[right];

            if(presSum > x){
                while(presSum > x){
                    presSum -= arr[left];
                    left++;
                }
            }

            count = max(count,(right - left + 1));

            right++;

        }

        ll ans = min(n,count + y);

        cout<<ans<<endl;

    }
    return 0;
}