from math import exp
import numpy as np
import random


def sigmoid(x):
    return 1 / (1 + exp(-x))


def evaluate(xi, coef):
    yi = coef[0]
    for j in range(len(xi)):
        yi += coef[j + 1] * xi[j]
    return yi


class MyLogisticRegression:
    def __init__(self):
        self.intercept_ = []
        self.coef_ = []

    def fit(self, x, y, learning_rate=0.001, no_epochs=1000):
        self.coef_ = []
        labels = np.unique(y)
        no_labels = len(labels)
        for label in range(no_labels):
            self.coef_.append([random.random() for _ in range(len(x[0]) + 1)])
            appearances = []
            for elem in y:
                if elem == label:
                    appearances.append(1)
                else:
                    appearances.append(0)
            for _ in range(no_epochs):
                for _ in range(len(x)):
                    y_computed = sigmoid(evaluate(x[_], self.coef_[label]))
                    crt_error = y_computed - appearances[_]
                    for i in range(0, len(x[0])):
                        self.coef_[label][i + 1] = self.coef_[label][i + 1] - learning_rate * crt_error * x[_][i]
                    self.coef_[label][0] = self.coef_[label][0] - learning_rate * crt_error * 1

        self.intercept_ = [_[0] for _ in self.coef_]
        self.coef_ = [_[1:] for _ in self.coef_]

    def predict_one_sample(self, sample_features):
        labels = []
        for _ in range(len(self.intercept_)):
            coefficients = [self.intercept_[_]] + [coef for coef in self.coef_[_]]
            computed_float_value = evaluate(sample_features, coefficients)
            labels.append(sigmoid(computed_float_value))
        computed_label = np.argmax(labels)
        return computed_label

    def predict(self, inTest):
        computed_labels = [self.predict_one_sample(sample) for sample in inTest]
        return computed_labels
