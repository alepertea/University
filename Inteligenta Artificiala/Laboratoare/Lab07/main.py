import os
import numpy as np
from sklearn.metrics import mean_squared_error

from sklearn_tool import regression
from developed_code import my_regression
from file import reader
from sklearn import linear_model


def main():
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, 'data', 'world-happiness-report-2017.csv')

    gdp_per_capita, freedom, outputs = reader.load_data(filePath, 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')
    print('GRP per Capita: ', gdp_per_capita)
    print('Freedom: ', freedom)
    print('Outputs: ', outputs)

    print('\nUsing sklearn:')
    regression.model(gdp_per_capita, freedom, outputs)

    print('\nUsing my code:')
    my_regression.my_linear_regression(gdp_per_capita, freedom, outputs)

    indexes = [i for i in range(len(gdp_per_capita))]
    train_sample = np.random.choice(indexes, int(0.8 * len(gdp_per_capita)), replace=False)
    validation_sample = [i for i in indexes if not i in train_sample]

    validation_inputs = [[gdp_per_capita[i], freedom[i]] for i in validation_sample]
    validation_outputs = [outputs[i] for i in validation_sample]

    linear_model.LinearRegression().fit(validation_inputs, outputs)
    computed_validation_outputs = linear_model.LinearRegression().predict([[x] for x in validation_inputs])

    error = 0.0
    for t1, t2 in zip(computed_validation_outputs, outputs):
        error += (t1 - t2) ** 2
    error = error / len(validation_outputs)
    print('Prediction error (manual): ', error)

    error = mean_squared_error(computed_validation_outputs, outputs)
    print('Prediction error (using sklearn):  ', error)


main()
