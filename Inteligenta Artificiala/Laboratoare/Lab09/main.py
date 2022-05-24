import numpy as np
from sklearn import linear_model
from sklearn.metrics import accuracy_score
from file import reader
from normalisation import normalize
from MyLogisticRegression import MyLogisticRegression


def main():
    inputs, feature1, feature2, feature3, feature4, outputs = reader.read()

    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    train_sample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    test_sample = [i for i in indexes if not i in train_sample]

    train_inputs = [inputs[i] for i in train_sample]
    train_outputs = [outputs[i] for i in train_sample]
    test_inputs = [inputs[i] for i in test_sample]
    test_outputs = [outputs[i] for i in test_sample]

    train_inputs, test_inputs = normalize(train_inputs, test_inputs)

    labels = [label for label in set(outputs)]
    classifier = linear_model.LogisticRegression()
    classifier.fit(train_inputs, train_outputs)
    w0 = classifier.intercept_
    w1, w2, w3, w4 = [classifier.coef_[_][0] for _ in range(len(labels))], [classifier.coef_[_][1] for _ in range(len(labels))], [classifier.coef_[_][2] for _ in range(len(labels))], [classifier.coef_[_][3] for _ in range(len(labels))]
    print('Classification models: (using tool)\n')
    for _ in range(len(labels)):
        print('y' + str(_ + 1) + '(feat1, feat2, feat3, feat4) = ', w0[_], ' + ', w1[_], ' * feat1 + ', w2[_], ' * feat2 + ', w3[_], ' * feat3 + ', w4[_], ' * feat4\n')

    classifier = MyLogisticRegression()
    classifier.fit(train_inputs, train_outputs)
    w0 = classifier.intercept_
    w1, w2, w3, w4 = [classifier.coef_[i][0] for i in range(len(labels))], [classifier.coef_[i][1] for i in range(len(labels))], [classifier.coef_[i][2] for i in range(len(labels))], [classifier.coef_[i][3] for i in range(len(labels))]
    print('Classification models: (using developed code)\n')
    for _ in range(len(labels)):
        print('y' + str(_ + 1) + '(feat1, feat2, feat3, feat4) = ', w0[_], ' + ', w1[_], ' * feat1 + ', w2[_],
              ' * feat2 + ', w3[_], ' * feat3 + ', w4[_], ' * feat4\n')

    computed_test_outputs = classifier.predict(test_inputs)
    error = 0.0
    for t1, t2 in zip(computed_test_outputs, test_outputs):
        if t1 != t2:
            error += 1
    error = error / len(test_outputs)
    print("Classification error (using developed code): ", error)

    error = 1 - accuracy_score(test_outputs, computed_test_outputs)
    print("Classification error (using tool): ", error)


main()
