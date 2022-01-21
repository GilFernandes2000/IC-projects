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
    /**
     * Calculates a probability using a Laplace formula for a event.
     * @param n the event occurrence
     * @param total the total occurrences
     * @param alphab_size the size of the alphabet under consideration
     * @param smoothing a smoothing parameter as to handle 0-value position (default: 0)
     * @return the probability of the event
     */
    inline float probability(int n, int total, int alphab_size, int smoothing = 0) {
        return ((0.0 + n + smoothing) / ( 0.0+total + smoothing * alphab_size));
    }

    /**
     * Calculates a cell's entropy based on its probability
     * @param prob cell's probability
     * @return cell's entropy
     */
    inline float cell_entropy(float prob) {
        return prob * log2(prob);
    }

    /**
     *  given a list of probabilities calculates their joined entropy
     * @param probs a vector containing probabilities
     * @return the list's entropy
     */
    inline float list_entropy(std::vector<float> probs) {
        return 0.0 - std::accumulate(probs.begin(), probs.end(), 0.0, [](const float &accumalator, const float &current) {
                                         return accumalator + cell_entropy(current);
                                     }
        );
    }
}
#endif //PROJECT3_MATH_UTILS_H
