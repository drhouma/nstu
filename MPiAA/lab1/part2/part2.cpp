#include <vector>
#include <algorithm>

auto has_duplicates(std::vector<int> array) -> bool {
    if (array.size() == 0) return false;
    bool res = false;
    std::sort(array.begin(), array.end());
    for (int i = 0; i < array.size() - 1; i++) {
        if (array[i] == array[i+1]) res = true;
    }
    return res;
}

auto has_duplicates_naive(std::vector<int> array) -> bool {
    bool res = false;
    for (int i = 0; i < array.size() - 1; i++) {
        for (int j = i + 1; j < array.size(); j++) {
            if (array[i] == array[j]) res = true;
        }
    }
    return res;
}


auto get_duplicates(std::vector<int> array) -> std::vector<int> {
    std::vector<int> ret;
    if (array.size() == 0) return ret;
    std::sort(array.begin(), array.end());
    for (int i = 0; i < array.size() - 1; i++) {
        if (array[i] == array[i+1]) {
            ret.emplace_back(array[i]);
            while (array[i] == array[i + 1]) i++;
        }
    }
    return ret;
}


auto get_duplicates_naive(std::vector<int> array) -> std::vector<int> {
    std::vector<int> ret;
    for (int i = 0; i < array.size() - 1; i++) {
        for (int j = i + 1; j < array.size(); j++) {
            if (array[i] == array[j] && std::find(ret.begin(), ret.end(), array[i]) == ret.end()) {
                ret.emplace_back(array[i]);
            }
        }
    }

    return ret;
}

