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

// using namespace std;

int32_t main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    register std::vector<std::tuple<int, int64_t>> v;
    v.reserve(10000000);
    FILE* fp = fopen(argv[1], "r");
    
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char* employee_id_str = strtok(line, ",");
        int employee_id = atoi(employee_id_str);

        char* sign_type = strtok(NULL, ",");
        
        char* time_str = strtok(NULL, ",");
        int64_t time = atoll(time_str);

        v.push_back({employee_id, time});
    }
    // // auto start_time = std::chrono::high_resolution_clock::now();


    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    // std::cout << "read time: " << duration.count() << "us" << "\n";

    // start_time = std::chrono::high_resolution_clock::now();
    stable_sort(v.begin(), v.end());
    // end_time = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    // std::cout << "sort time: " << duration.count() << "us" << "\n";

    // start_time = std::chrono::high_resolution_clock::now();
    register int len(v.size());
    for (register int i = 0; i < len;) {
        register int j(i);
        register int overloading_days(0);
        register int sign_forget_days(0);
        register int employee_id(std::get<0>(v[i]));
        while (j < v.size() && std::get<0>(v[i]) == std::get<0>(v[j])) {
            j++;
        }
        for (register int k(i); k < j; k++) {
            //print employee_id, overloading_days, sign_forget_days
            // std::cout << k << " " << employee_id << "," << overloading_days << "," << sign_forget_days << "\n";
            if (k >= j-1) {
                sign_forget_days++;
                break;
            }
            if (std::get<1>(v[k+1]) / 10000 == std::get<1>(v[k]) / 10000) {
                if (std::get<1>(v[k+1]) - ((std::get<1>(v[k+1]) / 10000 * 10000)) - (std::get<1>(v[k]) - ((std::get<1>(v[k]) / 10000 * 10000))) > 800) {
                    overloading_days++;
                }
                k++;
            }
            else {
                sign_forget_days++;
            }
        }
        i = j;
        std::cout << employee_id << "," << overloading_days << "," << sign_forget_days << "\n";
    }
    // end_time = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    // std::cout << "calculation time: " << duration.count() << "us" << "\n";
    return 0;
}