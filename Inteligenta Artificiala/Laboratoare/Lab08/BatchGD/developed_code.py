import numpy as np
from sklearn.metrics import mean_squared_error


def univariate_regression(train_inputs, test_inputs, train_outputs, test_outputs, learning_rate, epochs):
    m = 124
    x = np.c_[np.ones((124, 1)), train_inputs]
    x_transpose = x.transpose()
    beta = np.array([0, 0])

    for _ in range(epochs):
        hypothesis = np.dot(x, beta)
        loss = hypothesis - train_outputs
        gradient = np.dot(x_transpose, loss) / m
        beta = beta - learning_rate * gradient

    computed_outputs = [beta[0] + test_inputs[i] * beta[1] for i in range(len(test_inputs))]
    print('Outputs: ', test_outputs)
    print('Computed outputs: ', computed_outputs)

    error = mean_squared_error(test_outputs, computed_outputs)
    print('Error: ', error)
