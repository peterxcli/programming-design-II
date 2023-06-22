#include <bits/stdc++.h>

#define int long long
using namespace std;


struct Workday {
    int employee_id;
    int continuous_workdays;
    string from_day;
    string end_day;
};

bool compare_workdays(const Workday &a, const Workday &b) {
    if (a.continuous_workdays == b.continuous_workdays) {
        return a.employee_id < b.employee_id;
    }
    return a.continuous_workdays > b.continuous_workdays;
}

int32_t main(int32_t argc, char *argv[]) {

    string csv_file = argv[1];
    ifstream input_file(csv_file);

    map<int, map<string, bool>> employee_workdays;
    string line;

    while (getline(input_file, line)) {
        stringstream ss(line);
        string employee_id_str, signing_type, signing_time;

        getline(ss, employee_id_str, ',');
        getline(ss, signing_type, ',');
        getline(ss, signing_time, ',');

        int employee_id = stoi(employee_id_str);
        string date = signing_time.substr(0, 8);

        if (date > "20230426") {
            continue;
        }

        employee_workdays[employee_id][date] = true;
    }

    vector<Workday> longest_workdays;

    for (const auto &employee : employee_workdays) {
        int continuous_workdays = 0;
        int max_continuous_workdays = 0;
        string from_day, end_day, current_work_day, prev_work_day;
        string longest_from_day, longest_end_day;

        for (const auto &workday : employee.second) {
            current_work_day = workday.first;

            if (workday.second) {
                if (continuous_workdays == 0) {
                    from_day = current_work_day;
                    continuous_workdays++;
                } else {
                    istringstream ss_current(current_work_day);
                    istringstream ss_prev(prev_work_day);
                    tm tm_current = {}, tm_prev = {};
                    ss_current >> get_time(&tm_current, "%Y%m%d");
                    ss_prev >> get_time(&tm_prev, "%Y%m%d");

                    auto tp_current = chrono::system_clock::from_time_t(mktime(&tm_current));
                    auto tp_prev = chrono::system_clock::from_time_t(mktime(&tm_prev));
                    auto duration = chrono::duration_cast<chrono::hours>(tp_current - tp_prev).count();

                    if (duration == 24) {
                        continuous_workdays++;
                        end_day = current_work_day;
                    } else {
                        continuous_workdays = 1;
                        from_day = current_work_day;
                    }
                }

                if (continuous_workdays >= max_continuous_workdays) {
                    max_continuous_workdays = continuous_workdays;
                    longest_from_day = from_day;
                    longest_end_day = end_day;
                }
            } else {
                continuous_workdays = 0;
            }
            prev_work_day = current_work_day;
        }

        longest_workdays.push_back({employee.first, max_continuous_workdays, longest_from_day, longest_end_day});
    }

    sort(longest_workdays.begin(), longest_workdays.end(), compare_workdays);

    for (int i = 0; i < 3 && i < longest_workdays.size(); i++) {
        cout << longest_workdays[i].employee_id << ","
                  << longest_workdays[i].continuous_workdays << ","
                  << longest_workdays[i].from_day << ","
                  << longest_workdays[i].end_day << endl;
    }

    return 0;
}
