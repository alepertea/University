
def evaluate_classification(realLabels, computedLabels, labelNames):
    accuracy = sum([1 if realLabels[i] == computedLabels[i] else 0 for i in range(len(realLabels))]) / len(realLabels)

    TP, FP, TN, FN = 0, 0, 0, 0
    for label in labelNames:
        TP += sum([1 if (realLabels[i] == label and computedLabels[i] == label) else 0 for i in range(len(realLabels))])
        FP += sum([1 if (realLabels[i] != label and computedLabels[i] == label) else 0 for i in range(len(realLabels))])
        TN += sum([1 if (realLabels[i] != label and computedLabels[i] != label) else 0 for i in range(len(realLabels))])
        FN += sum([1 if (realLabels[i] == label and computedLabels[i] != label) else 0 for i in range(len(realLabels))])

    precisionPos = TP / (TP + FP)
    recallPos = TP / (TP + FN)
    precisionNeg = TN / (TN + FN)
    recallNeg = TN / (TN + FP)

    return accuracy, precisionPos, precisionNeg, recallPos, recallNeg
