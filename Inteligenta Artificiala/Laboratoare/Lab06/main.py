from classification import evaluate_classification
from regression import compute_error


def main():
    realOutputs = [[1.2, 4, 1, 10.76, 2, 3.5], [5, 2, 4.6, 76.3, 2.4, 4.4]]
    computedOutputs = [[1.2, 4, 2, 10.76, 1, 3.5], [2.4, 5, 4.6, 76.3, 2, 4.4]]

    labelNames = ['apple', 'pear', 'orange', 'banana']
    realLabels = ['apple', 'apple', 'orange', 'apple', 'banana', 'pear', 'banana']
    computedLabels = ['apple', 'apple', 'apple', 'orange', 'banana', 'pear', 'banana']

    mae, rmse = compute_error(realOutputs, computedOutputs)
    accuracy, precisionPos, precisionNeg, recallPos, recallNeg = evaluate_classification(realLabels, computedLabels, labelNames)
    print('Regression:')
    print('MAE: ', mae, '\nRMSE: ', rmse)
    print('\nClassification:')
    print('Accuracy: ', accuracy, '\nPrecision (positive): ', precisionPos, '\nPrecision (negative): ', precisionNeg, '\nRecall (positive): ', recallPos, '\nRecall (negative): ', recallNeg)


main()
