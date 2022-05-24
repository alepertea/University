from sklearn import linear_model
from sklearn.metrics import mean_squared_error


def univariate_regression_tool(train_inputs, train_outputs, test_inputs, test_outputs):
    regressor = linear_model.SGDRegressor()
    regressor.average = True

    xx = [[i] for i in train_inputs]
    regressor.fit(xx, train_outputs)

    w0, w1 = regressor.intercept_[0], regressor.coef_[0]
    computed_outputs = [w0 + test_inputs[i] * w1 for i in range(len(test_inputs))]
    print('Outputs: ', test_outputs)
    print('Computed outputs: ', computed_outputs)

    error = mean_squared_error(test_outputs, computed_outputs)
    print('Error: ', error)


def multivariate_regression_tool(first_train_inputs, second_train_inputs, first_test_inputs, second_test_inputs, train_outputs, test_outputs):
    regressor = linear_model.SGDRegressor()
    regressor.average = True

    xx = [[i, j] for i, j in zip(first_train_inputs, second_train_inputs)]
    regressor.fit(xx, train_outputs)

    w0, w1, w2 = regressor.intercept_[0], regressor.coef_[0], regressor.coef_[1]
    computed_outputs = [w0 + first_test_inputs[i] * w1 + second_test_inputs[i] * w2 for i in range(len(first_test_inputs))]
    print('Outputs: ', test_outputs)
    print('Computed outputs: ', computed_outputs)

    error = mean_squared_error(test_outputs, computed_outputs)
    print('Error: ', error)
