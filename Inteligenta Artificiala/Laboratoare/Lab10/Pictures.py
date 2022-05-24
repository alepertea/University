import glob
from PIL import Image
import numpy as np
from sklearn.metrics import confusion_matrix


def load_picture_data():
    inputs, outputs = [], []
    size = (10, 10)
    for f in glob.iglob("D:\Facultate\Anul_2\Semestrul_2\Inteligenta_Artificiala\Laboratoare\lab10\ANN\images\withSepia\*"):
        inputs.append(np.asarray(Image.open(f).resize(size)))
        outputs.append(1)

    for f in glob.iglob("D:\Facultate\Anul_2\Semestrul_2\Inteligenta_Artificiala\Laboratoare\lab10\ANN\images\withoutSepia\*"):
        inputs.append(np.asarray(Image.open(f).resize(size)))
        outputs.append(0)

    inputs = np.array(inputs)
    outputs = np.array(outputs)

    no_data = len(inputs)
    permutation = np.random.permutation(no_data)
    inputs, outputs = inputs[permutation], outputs[permutation]

    return inputs, outputs


def split_data(inputs, outputs):
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    train_sample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    test_sample = [i for i in indexes if not i in train_sample]

    train_inputs = [inputs[i] for i in train_sample]
    train_outputs = [outputs[i] for i in train_sample]
    test_inputs = [inputs[i] for i in test_sample]
    test_outputs = [outputs[i] for i in test_sample]

    train_inputs = np.array(train_inputs)
    train_outputs = np.array(train_outputs)
    test_inputs = np.array(test_inputs)
    test_outputs = np.array(test_outputs)

    return train_inputs, train_outputs, test_inputs, test_outputs


def flatten(mat):
    x = []
    for line in mat:
        for el in line:
            for k in el:
                x.append(k)
    return x


def train(classifier, train_inputs, train_outputs):
    classifier.fit(train_inputs, train_outputs)


def classification(classifier, test_inputs):
    computed_test_outputs = classifier.predict(test_inputs)
    return computed_test_outputs


def evaluate(test_outputs, computed_labels):
    real_labels = np.array(test_outputs)
    label_names = ["WithSepia", "WithoutSepia"]
    conf_matrix = confusion_matrix(real_labels, computed_labels)
    acc = sum([conf_matrix[i][i] for i in range(len(label_names))]) / len(real_labels)

    precision, recall = {}, {}
    for i in range(len(label_names)):
        precision[label_names[i]] = conf_matrix[i][i] / sum([conf_matrix[j][i] for j in range(len(label_names))])
        recall[label_names[i]] = conf_matrix[i][i] / sum([conf_matrix[i][j] for j in range(len(label_names))])
    return acc, precision, recall, conf_matrix


def scale(features):
    min_feat = min(features)
    max_feat = max(features)
    scaled_features = [(feat - min_feat) / (max_feat - min_feat) for feat in features]
    return scaled_features


def normalize(list):
    normalized_list = []
    for i in range(len(list)):
        scalar = scale(list[i])
        normalized_list.append(scalar)
    return normalized_list
