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

// Function to calculate IDF
double idf(int totalDocs, int docsWithTerm) {
    return log10((double)totalDocs / docsWithTerm);
}

// Function to split a string into words
vector<string> split(const string &text) {
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

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string corpus_file_name = argv[1];
    string query_file_name = argv[2];
    int k = stoi(argv[3]);

    ifstream corpus_file(corpus_file_name);
    ifstream query_file(query_file_name);
    string line;
    unordered_map<string, unordered_map<int, double>> tfValues;
    unordered_map<int, int> docLength;
    int totalDocs = 0;

    while (getline(corpus_file, line)) {
        int s_id;
        string context;

        size_t pos = line.find(',');
        s_id = stoi(line.substr(0, pos));
        context = line.substr(pos + 2);
        context.erase(remove(context.begin(), context.end(), '\"'), context.end());

        vector<string> words = split(context);
        for (const string &word : words) {
            tfValues[word][s_id]++;
        }
        unordered_set<string> unique_words(words.begin(), words.end());
        for (const string &word : unique_words) {
            tfValues[word][s_id] /= (double)words.size();
        }
        totalDocs++;
    }
    unordered_map<string, double> idfValues;
    for (auto const &[word, id_set] : tfValues) {
        idfValues[word] = idf(totalDocs, id_set.size());
    }
    while (getline(query_file, line)) {
        vector<string> query_words = split(line);
        unordered_map<int, double> docScores;
        //3, 14, 31
        for (const string &word : query_words) {
            for (const auto &[docId, new_tf] : tfValues[word]) {
                docScores[docId] += idfValues[word] * new_tf;
            }
        }
        vector<pair<int, double>> docScoresVec(docScores.begin(), docScores.end());
        sort(docScoresVec.begin(), docScoresVec.end(), [](pair<int, double> a, pair<int, double> b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        });

        for (int i = 0; i < k; i++) {
            if (i < docScoresVec.size()) {
                cout << docScoresVec[i].first;
            } 
            else {
                cout << "-1";
            }
            cout << ((i != k-1) ? " " : "\n");
        }
    }

    return 0;
}
