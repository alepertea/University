from sklearn import neural_network
import Iris
import Pictures


def main():
    # inputs, outputs, output_names = ANN_Iris.load_iris_data()
    # train_inputs, train_outputs, test_inputs, test_outputs = ANN_Iris.split_data(inputs, outputs)
    # train_inputs, test_inputs = ANN_Iris.normalize(train_inputs, test_inputs)
    #
    # classifier = neural_network.MLPClassifier(hidden_layer_sizes=(5,), activation='relu', max_iter=100, solver='sgd', verbose=10, random_state=1, learning_rate_init=.1)
    # ANN_Iris.train(classifier, train_inputs, train_outputs)
    # computed_test_outputs = ANN_Iris.classification(classifier, test_inputs)
    #
    # print(test_outputs)
    # print(computed_test_outputs)

    inputs, outputs = Pictures.load_picture_data()
    train_inputs, train_outputs, test_inputs, test_outputs = Pictures.split_data(inputs, outputs)
    train_inputs = [Pictures.flatten(el) for el in train_inputs]
    test_inputs = [Pictures.flatten(el) for el in test_inputs]

    train_inputs = Pictures.normalize(train_inputs)
    test_inputs = Pictures.normalize(test_inputs)

    classifier = neural_network.MLPClassifier(hidden_layer_sizes=(5, ), activation='relu', max_iter=100, solver='sgd', verbose=10, random_state=1, learning_rate_init=.1)

    Pictures.train(classifier, train_inputs, train_outputs)

    computed_test_outputs = Pictures.classification(classifier, test_inputs)
    acc, precision, recall, conf_matrix = Pictures.evaluate(test_outputs, computed_test_outputs)
    print("Accuracy = ", acc)
    print("Precision = ", precision)
    print("Recall = ", recall)


main()
