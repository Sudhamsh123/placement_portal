#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void print_yes() {
    cout << "YES" << endl;
}

void print_no() {
    cout << "NO" << endl;
}

vector<vector<bool>>isPalindrome;
vector<vector<int>>dp;

vector<int>prefix,suffix;

int n;

int findPoss(int i,int count,string s){
    if(i == s.size()){
        return count == 3 ? 1 : 0;
    }
    if(dp[i][count] != -1){
        return dp[i][count];
    }
    int allPoss1 = 0;
    int allPoss2 = 0;
    for(int len = 1;len <= s.size() - i;len++){
        if(isPalindrome[i][i + len - 1]){
            allPoss1 += findPoss(i + len,count + 1,s);
        }
        allPoss2 += findPoss(i + len,count,s);
    }
    return dp[i][count] = allPoss1 + allPoss2;
}

void checkPalindromes(string &s){
    int ind = 0;
    while(ind < s.size()){
        int left = ind ;
        int right = ind;
        while(left >= 0 && right < s.size() && s[left] == s[right]){
            isPalindrome[left][right] = true;
            left--;
            right++;
        }
        left = ind;
        right = ind + 1;
        while(left >= 0 && right < s.size() && s[left] == s[right]){
            isPalindrome[left][right] = true;
            left--;
            right++;
        }
        ind++;
    }
}

void buildPrefixSuffix() {
    prefix.assign(n, 0);
    suffix.assign(n, 0);

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (isPalindrome[l][r]) {
                prefix[r]++;
                suffix[l]++;
            }
        }
    }

    for (int i = 1; i < n; ++i)
        prefix[i] += prefix[i - 1];

    for (int i = n - 2; i >= 0; --i)
        suffix[i] += suffix[i + 1];
}

ll countTriplets() {
    ll total = 0;

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (!isPalindrome[l][r]) continue;

            int before = (l > 0) ? prefix[l - 1] : 0;
            int after = (r + 1 < n) ? suffix[r + 1] : 0;

            total += 1LL * before * after;
        }
    }

    return total;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin>>s;

    n = s.size();

    dp.resize(n,vector<int>(n,-1));

    isPalindrome.resize(n,vector<bool>(n,false));

    checkPalindromes(s);

    buildPrefixSuffix();



    cout<<countTriplets()<<"\n";
    
    return 0;
}

/*

Great — you're now asking the right performance question:

❓ How can we optimize your current O(n³) approach to run in O(n²)?

📌 Problem Recap (Target: O(n²)):
Given a string s of length n, count the number of triplets of non-overlapping palindromic substrings (S1, S2, S3) such that:

Each Si is a palindromic substring.

Substrings are non-overlapping and in order.

❗ Your Current Approach: O(n³)
For every index i, you're trying all substring lengths len → O(n)

For each valid palindrome, you recursively call findPoss(i + len, count + 1) → depth 3

Total complexity: roughly O(n³) in worst case.

✅ How to Reduce to O(n²)
We can precompute all palindromic substrings and then use prefix counting ideas to efficiently build triplets.

⚙️ High-Level Optimized Strategy (O(n²)):
Precompute all palindromic substrings using center expansion → O(n²)

For each position i, maintain:

prefix[i]: number of palindromic substrings ending at or before index i

suffix[i]: number of palindromic substrings starting at or after index i

Then:

For each possible middle palindrome (l, r):

Count how many palindromes end before l → from prefix[l-1]

Count how many palindromes start after r → from suffix[r+1]

Total triplets: prefix[l-1] * suffix[r+1]

🧠 Why This Is O(n²)
Total palindromic substrings: O(n²)

For each one (the middle one), we do O(1) lookup in prefix/suffix → O(n²) total

✅ C++ Code Sketch (Optimized)
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 5005;
vector<vector<bool>> isPalindrome;
vector<int> prefix, suffix;
int n;

void computePalindromes(const string &s) {
    isPalindrome.assign(n, vector<bool>(n, false));

    for (int center = 0; center < n; ++center) {
        // odd-length
        int l = center, r = center;
        while (l >= 0 && r < n && s[l] == s[r]) {
            isPalindrome[l][r] = true;
            l--; r++;
        }

        // even-length
        l = center, r = center + 1;
        while (l >= 0 && r < n && s[l] == s[r]) {
            isPalindrome[l][r] = true;
            l--; r++;
        }
    }
}

void buildPrefixSuffix() {
    prefix.assign(n, 0);
    suffix.assign(n, 0);

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (isPalindrome[l][r]) {
                prefix[r]++;
                suffix[l]++;
            }
        }
    }

    // Build prefix sum
    for (int i = 1; i < n; ++i)
        prefix[i] += prefix[i - 1];

    // Build suffix sum
    for (int i = n - 2; i >= 0; --i)
        suffix[i] += suffix[i + 1];
}

ll countTriplets() {
    ll total = 0;

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (!isPalindrome[l][r]) continue;

            int before = (l > 0) ? prefix[l - 1] : 0;
            int after = (r + 1 < n) ? suffix[r + 1] : 0;

            total += 1LL * before * after;
        }
    }

    return total;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    n = s.size();

    computePalindromes(s);
    buildPrefixSuffix();
    cout << countTriplets() << "\n";

    return 0;
}
✅ Output for "abaa":
Copy code
5
📌 Summary
Step	Description	Time
1	Find all palindromes (center expand)	O(n²)
2	Build prefix/suffix arrays	O(n²)
3	Count valid triplets	O(n²)
✅	Total	O(n²)

Would you like this converted to Python or integrated into your current codebase?

*/