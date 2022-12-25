#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"
using namespace std;
#include "activities.h"

bool comp(Activity a, Activity b) { return (a.finish < b.finish); }

std::vector<Activity> get_sorted_activities(const std::vector<Activity>& inp) {
  std::vector<Activity> activities = inp;
  sort(activities.begin(), activities.end(), comp);
  int i = 0, min = activities[0].finish;
  std::vector<Activity> answ = {};
  while (i < activities.size()) {
    while (activities[i].start < min) {
      i++;
      if (i == activities.size()) return answ;
    }
    answ.push_back(activities[i]);
    min = activities[i].finish;
  }
  return answ;
}

std::vector<Activity> Naiv(const std::vector<Activity>& inp) {
  std::vector<Activity> activities = inp;
  sort(activities.begin(), activities.end(), comp);
  std::vector<vector<Activity>> Soch = {};
  int i, j;
  for (i = 0; i < activities.size(); i++) {
    for (j = 0; j < Soch.size(); j++)
      if (activities[i].start > Soch[j][Soch[j].size() - 1].finish)
        Soch[j].push_back(activities[i]);
    Soch.push_back({activities[i]});
  }
  int max = 0, maxi;
  for (i = 0; i < Soch.size(); i++)
    if (Soch[i].size() > max) {
      max = Soch[i].size();
      maxi = i;
    }
  return Soch[maxi];
}

int main(int argc, char* argv[]) {
  srand(time(0));
  int N, i;
  // setlocale(LC_ALL, "Russian");
  cout << "Введите количество процессов: ";
  cin >> N;
  std::vector<Activity> Proc = {};
  Activity A;
  for (i = 0; i < N; i++) {
    A.start = rand() % 100;
    A.finish = (rand() % (100 - A.start)) + A.start + 1;
    Proc.push_back(A);
  }

  auto t1 = chrono::high_resolution_clock::now();
  get_max_activities(Proc);
  auto t2 = chrono::high_resolution_clock::now();
  auto seconds = chrono::duration<double>(t2 - t1).count();
  cout << "------- greed -------";
  cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  get_sorted_activities(Proc);
  t2 = chrono::high_resolution_clock::now();
  seconds = chrono::duration<double>(t2 - t1).count();
  cout << "------- greed with sort -------";
  cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  Naiv(Proc);
  t2 = chrono::high_resolution_clock::now();
  seconds = chrono::duration<double>(t2 - t1).count();
  cout << "------- naiv -------";
  cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

  int result = Catch::Session().run(argc, argv);
  return result;
}