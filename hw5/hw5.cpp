#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
void debug_out(){cerr<<"]\n"<<flush;}
template<typename Head,typename... Tail>void debug_out(Head H,Tail... T){cerr << H;if(sizeof...(T))cerr<<", ";debug_out(T...);}
#define debug(...) cerr<<"LINE("<<__LINE__<<") : ["<<#__VA_ARGS__<<"] = [";debug_out(__VA_ARGS__)
//#define endl '\n'
// #define int long long

vector<int> KMP(string str, string substr) {
    int pos, now;
    vector<int> ff(substr.size()), ans;
    ff[0] = pos = -1;
    //build fail function
    for (int i = 1; i < substr.size(); i++) {
        while (pos != -1 && substr[pos+1] != substr[i]) pos = ff[pos];
        if (substr[pos+1] == substr[i]) pos++;
        ff[i] = pos;
    }
    now = -1;
    for (int i = 0; i < str.size(); i++) {
        while (now != -1 && substr[now+1] != str[i]) now = ff[now]; 
        if (substr[now+1] == str[i]) now++;
        if (now+1 == substr.size()) {
            ans.emplace_back(i-substr.size()+2);//match index
            now = ff[now];
        }
    }
    return ans;
}

// Function to split a string into words
vector<string> split_corpus(const string &text) {
     vector<string> words;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        string cleaned_word = "";
        for (char c : word) {
            if (isalpha(c)) {
                cleaned_word += tolower(c);
            }
        }
        words.push_back(cleaned_word);
    }
    
    return words;
}

vector<string> split_query(const string &text) {
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }
    return words;
}

int32_t main(int32_t argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ifstream corpus_file(argv[1]);
    ifstream query_file(argv[2]);

    unordered_map<string, vector<int>> index;
    string line;
    while (getline(corpus_file, line)) {
        int s_id;
        string context;

        size_t pos = line.find(',');
        if (pos != string::npos) {
            s_id = stoi(line.substr(0, pos));
            context = line.substr(pos + 1);
        } else {
            continue;
        }

        // Remove double quotation marks
        context.erase(remove(context.begin(), context.end(), '\"'), context.end());
        // cout << s_id << ": ";

        vector<string> words = split_corpus(context);
        for (const string &word : words) {
            // index[word].push_back(s_id);
            // cout << word << " ";
        }
        // cout << endl;
        for (const string &word : words) {
            index[word].push_back(s_id);
        }
    }
    

    while (getline(query_file, line)) {
        vector<string> query_words = split_query(line);
        unordered_set<int> results;

        for (size_t i = 0; i < query_words.size(); i++) {
            const string &word = query_words[i];
            if (i == 0) {
                results.insert(index[word].begin(), index[word].end());
            } else {
                unordered_set<int> tmp_results;
                for (int s_id : index[word]) {
                    if (results.count(s_id)) {
                        tmp_results.insert(s_id);
                    }
                }
                // cout << word << ": ";
                // for (auto item : tmp_results) {
                //     cout << item << " ";
                // }
                // cout << endl;
                results.swap(tmp_results);
            }
        }

        if (results.empty()) {
            cout << -1 << endl;
        } else {
            vector<int> sorted_results(results.begin(), results.end());
            sort(sorted_results.begin(), sorted_results.end());
            for (int index = 0; index < sorted_results.size(); index++) {
                cout << sorted_results[index] << (index == sorted_results.size() - 1 ? "\n" : " ");
            }
        }
    }

    return 0;
}