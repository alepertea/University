import random
from random import randint
from utils import generateNewValue
import numpy


class Chromosome:
    def __init__(self, problemParam=None):
        self.__problemParam = problemParam
        self.__repres = [generateNewValue(problemParam['min'], problemParam['max']) for _ in range(problemParam['noNodes'])]
        self.__fitness = 0.0

    @property
    def repres(self):
        return self.__repres

    @property
    def fitness(self):
        return self.__fitness

    @repres.setter
    def repres(self, l=[]):
        self.__repres = l

    @fitness.setter
    def fitness(self, fit=0.0):
        self.__fitness = fit

    def crossover(self, c):
        # Standard uniform crossover
        mask = numpy.random.randint(2, size=len(self.__repres))
        new_representation = []
        for i in range(len(self.__repres)):
            if mask[i] == 0:
                new_representation.append(self.__repres[i])
            else:
                new_representation.append(c.__repres[i])
        offspring = Chromosome(c.__problemParam)
        offspring.repres = new_representation
        return offspring

    def mutation(self):
        # Scramble mutation
        pos1 = randint(0, len(self.__repres) - 1)
        pos2 = randint(0, len(self.__repres) - 1)
        if pos1 > pos2:
            aux = pos1
            pos1 = pos2
            pos2 = aux
        sequence = [self.__repres[i] for i in range(pos1, pos2)]
        random.shuffle(sequence)
        j = 0
        for i in range(pos1, pos2):
            self.__repres[i] = sequence[j]
            j += 1

    def __str__(self):
        return '\nChromo: ' + str(self.__repres) + ' has fit: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__repres == c.__repres and self.__fitness == c.__fitness
