#include <iostream>
#include "src/Region.h"

//struct htm {
//    std::vector<std::vector<bool>> colsActivity;
//    std::vector<std::vector<bool>> colsPrediction;
//    std::vector<std::vector<bool>> colsLearning;
//    std::vector<std::vector<std::vector<std::vector<double>>>> synapses;
//
//    explicit htm(int h);
//
//    std::vector<std::pair<bool, int>> learningCells;
//
//    void activate(bool col);
//
//    void activate_all_neurons(bool col);
//
//    std::vector<int> predict(bool col) const;
//
//};
//
//htm::htm(int h) :
//        colsActivity(2, std::vector<bool>(h)),
//        colsPrediction(2, std::vector<bool>(h)),
//        colsLearning(2, std::vector<bool>(h)),
//        synapses(2,
//                 std::vector<
//                         std::vector<
//                                 std::vector<double>>>(h,
//                                                       std::vector<
//                                                               std::vector<double>>(2,
//                                                                                    std::vector<double>(h)))) {}
//
//void htm::activate(bool col) {
//    auto pred = predict(col);
//    if (pred.empty()) {
//        activate_all_neurons(col);
//    }
//}
//
//std::vector<int> htm::predict(bool col) const {
//    std::vector<int> res;
//    for (int i = 0; i < colsPrediction[col].size(); ++i) {
//        if (colsPrediction[col][i]) {
//            res.push_back(i);
//        }
//    }
//    return res;
//}
//
//void htm::activate_all_neurons(bool col) {
//    for (auto i : colsActivity[col]) {
//        i = true;
//    }
//}


int main() {
//    Region region(2, 1, 5);
}
