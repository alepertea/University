from random import randint
from fcOptimisGA.utils import generateNewValue


class Chromosome:
    def __init__(self, problemParam=None):
        self.__problemParam = problemParam
        self.__repress = [generateNewValue(problemParam['min'], problemParam['max']) for _ in range(problemParam['noDim'])]
        self.__fitness = 0.0

    @property
    def repress(self):
        return self.__repress

    @property
    def fitness(self):
        return self.__fitness

    @repress.setter
    def repress(self, l = []):
        self.__repress = l

    @fitness.setter
    def fitness(self, fit = 0.0):
        self.__fitness = fit

    def crossover(self, c):
        r = randint(0, len(self.__repress) - 1)
        newrepress = []
        for i in range(r):
            newrepress.append(self.__repress[i])
        for i in range(r, len(self.__repress)):
            newrepress.append(c.__repress[i])
        offspring = Chromosome(c.__problemParam)
        offspring.repress = newrepress
        return offspring

    def mutation(self):
        pos = randint(0, len(self.__repress) - 1)
        self.__repress[pos] = generateNewValue(self.__problemParam['min'], self.__problemParam['max'])

    def __str__(self):
        return '\nChromo: ' + str(self.__repress) + ' has fit: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__repress == c.__repress and self.__fitness == c.__fitness
