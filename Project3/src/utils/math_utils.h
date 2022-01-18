//
// Created by jfngsea on 18/01/22.
//

#ifndef PROJECT3_MATH_UTILS_H
#define PROJECT3_MATH_UTILS_H

#include <cmath>
#include <numeric>
#include "vector"

namespace utils {
    inline int sigma_summation(int i, int n, int (*f)(int)) {
        int sum = 0;
        for (; i <= n; i++) {
            sum += f(i);
        }
        return sum;
    }

    inline float probability(int n, int total, int alphab_size, int smoothing = 0) {
        return ((n + smoothing) / (total + smoothing * alphab_size));
    }

    inline float cell_entropy(float prob) {
        return prob * log2(prob);
    }

    inline float list_entropy(std::vector<float> probs) {
        return std::accumulate(probs.begin(), probs.end(), 0.0, [](const float &accumalator, const float &current) {
                                   return accumalator + cell_entropy(current);
                               }
        );
    }
}
#endif //PROJECT3_MATH_UTILS_H
