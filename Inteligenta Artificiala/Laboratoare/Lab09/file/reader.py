from sklearn.datasets import load_iris


def read():
    data = load_iris()
    inputs = data['data']
    outputs = data['target']
    feature_names = list(data['feature_names'])

    feature1 = [feature[feature_names.index('sepal length (cm)')] for feature in inputs]
    feature2 = [feature[feature_names.index('sepal width (cm)')] for feature in inputs]
    feature3 = [feature[feature_names.index('petal length (cm)')] for feature in inputs]
    feature4 = [feature[feature_names.index('petal width (cm)')] for feature in inputs]
    inputs = [[feature[feature_names.index('sepal length (cm)')], feature[feature_names.index('sepal width (cm)')], feature[feature_names.index('petal length (cm)')], feature[feature_names.index('petal width (cm)')]] for feature in inputs]

    return inputs, feature1, feature2, feature3, feature4, outputs
