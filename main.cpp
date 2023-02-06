#include <iostream>
#include <map>
#include <cmath>

using namespace std;

long long int euclids_algorithm(const long long int& i1, const long long int& i2) {
    if (i1 % i2 == 0) return i2;
    if (i2 % i1 == 0) return i1;
    if (i1 > i2) return euclids_algorithm(i1 % i2, i2);
    return euclids_algorithm(i1, i2 % i1);
}

map<long long int, int> multipliers(const long long int& i) {
    map<long long int, int> result = {{1, 1}};
    bool one = true;
    int div = 2;
    long long int n = i;
    while (n > 1) {
        while (n % div == 0) {
            if (one) {
                one = false;
                result.erase(result.begin());
            }
            result[div]++;
            n = n / div;
        }
        div++;
    }

    return result;
}

bool is_simple(const long long int& l) {
    for (int i = 2; i <= sqrt(l); i++) {
        if (l % i == 0) return false;
    }
    return true;
}

long long int max_simple(const map<long long int, int>& v, const map<long long int, int>& comparison) {
    long long int result = 1;
    for (auto [multiply, counter] : comparison) {
        if (((v.find(multiply) != v.end() && v.at(multiply) < counter) || v.find(multiply) == v.end()) && multiply > result) result = multiply;
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        long long int A, B;
        cin >> A >> B;
        map<long long int, int> multipliers_a = multipliers(A);
        map<long long int, int> multipliers_b = multipliers(B);
        long long int NOD = euclids_algorithm(A, B);
        long long int for_a = euclids_algorithm(A * max_simple(multipliers_a, multipliers_b), B);
        long long int for_b = euclids_algorithm(A, B * max_simple(multipliers_b, multipliers_a));
        //cout << NOD << "\\/" << for_a << "\\/" << for_b << endl;
        cout << max(NOD, max(for_a, for_b)) << endl;
    }

    return 0;
}

