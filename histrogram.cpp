#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

int main() {
    int n, num_threads;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter number of threads: ";
    cin >> num_threads;

    vector<int> data(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> data[i];

    // Find min and max
    int min_val = *min_element(data.begin(), data.end());
    int max_val = *max_element(data.begin(), data.end());

    int range = max_val - min_val + 1;
    int bucket_size = (range + num_threads - 1) / num_threads;

    vector<vector<int>> buckets(num_threads);

    // Distribute elements to appropriate buckets (serial)
    for (int i = 0; i < n; ++i) {
        int b = (data[i] - min_val) / bucket_size;
        if (b >= num_threads) b = num_threads - 1;
        buckets[b].push_back(data[i]);
    }

    // Sort each bucket in parallel
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < num_threads; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Merge all buckets
    vector<int> sorted_data;
    for (int i = 0; i < num_threads; ++i) {
        sorted_data.insert(sorted_data.end(), buckets[i].begin(), buckets[i].end());
    }

    // Output
    cout << "Sorted data:\n";
    for (int num : sorted_data)
        cout << num << " ";
    cout << endl;

    return 0;
}
