from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
import numpy as np


def load_iris_data():
    data = load_iris()
    inputs = data['data']
    outputs = data['target']
    output_names = data['target_names']
    feature_names = list(data['feature_names'])
    inputs = [[feat[feature_names.index('sepal length (cm)')], feat[feature_names.index('sepal width (cm)')], feat[feature_names.index('petal length (cm)')], feat[feature_names.index('petal width (cm)')]] for feat in inputs]
    return inputs, outputs, output_names


def split_data(inputs, outputs):
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    train_sample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    test_sample = [i for i in indexes if not i in train_sample]

    train_inputs = [inputs[i] for i in train_sample]
    train_outputs = [outputs[i] for i in train_sample]
    test_inputs = [inputs[i] for i in test_sample]
    test_outputs = [outputs[i] for i in test_sample]

    return train_inputs, train_outputs, test_inputs, test_outputs


def normalize(train_data, test_data):
    scaler = StandardScaler()
    if not isinstance(train_data[0], list):
        train_data = [[data] for data in train_data]
        test_data = [[data] for data in test_data]

        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_test_data = scaler.transform(test_data)

        normalised_train_data = [el[0] for el in normalised_train_data]
        normalised_test_data = [el[0] for el in normalised_test_data]
    else:
        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_test_data = scaler.transform(test_data)
    return normalised_train_data, normalised_test_data


def train(classifier, train_inputs, train_outputs):
    classifier.fit(train_inputs, train_outputs)


def classification(classifier, test_inputs):
    computed_test_outputs = classifier.predict(test_inputs)
    return computed_test_outputs


def evaluate(real_labels, computed_labels, label_names):
    from sklearn.metrics import confusion_matrix

    conf_matrix = confusion_matrix(real_labels, computed_labels)
    acc = sum([conf_matrix[i][i] for i in range(len(label_names))]) / len(real_labels)
    precision, recall = {}, {}
    for i in range(len(label_names)):
        precision[label_names[i]] = conf_matrix[i][i] / sum([conf_matrix[j][i] for j in range(len(label_names))])
        recall[label_names[i]] = conf_matrix[i][i] / sum([conf_matrix[i][j] for j in range(len(label_names))])
    return acc, precision, recall, conf_matrix
