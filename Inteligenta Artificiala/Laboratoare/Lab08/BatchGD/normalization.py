import numpy as np


# Min-Max Scaling: x_scaled = (x - min(x)) / (max(x) - min(x))
def normalize(first_train_inputs, second_train_inputs, first_test_inputs, second_test_inputs, train_outputs, test_outputs):
    length = len(first_train_inputs)
    for i in range(length):
        minimum = np.min(first_train_inputs)
        maximum = np.max(first_train_inputs)
        first_train_inputs[i] = (first_train_inputs[i] - minimum) / (maximum - minimum)

        minimum = np.min(second_train_inputs)
        maximum = np.max(second_train_inputs)
        second_train_inputs[i] = (second_train_inputs[i] - minimum) / (maximum - minimum)

        minimum = np.min(train_outputs)
        maximum = np.max(train_outputs)
        train_outputs[i] = (train_outputs[i] - minimum) / (maximum - minimum)

    length = len(first_test_inputs)
    for i in range(length):
        minimum = np.min(first_test_inputs)
        maximum = np.max(first_test_inputs)
        first_test_inputs[i] = (first_test_inputs[i] - minimum) / (maximum - minimum)

        minimum = np.min(second_test_inputs)
        maximum = np.max(second_test_inputs)
        second_test_inputs[i] = (second_test_inputs[i] - minimum) / (maximum - minimum)

        minimum = np.min(test_outputs)
        maximum = np.max(test_outputs)
        test_outputs[i] = (test_outputs[i] - minimum) / (maximum - minimum)
