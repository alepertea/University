from math import sqrt


def compute_error(realOutputs, computedOutputs):
    mae = 0
    rmse = 0
    for real, computed in zip(realOutputs, computedOutputs):
        mae += (sum(abs(r - c) for r, c in zip(real, computed)) / len(real))
        rmse += sqrt(sum((r - c) ** 2 for r, c in zip(real, computed)) / len(real))
    return mae / len(realOutputs), rmse / len(realOutputs)
