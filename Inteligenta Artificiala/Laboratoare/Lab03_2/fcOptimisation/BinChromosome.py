from random import randint
from fcOptimisGA.utils import generateNewValue, binToInt


# Binary representation
class Chromosome:
    def __init__(self, problemParam = None):
        self.__problemParam = problemParam
        self.__repress = []
        for _ in range(problemParam['noDim']):
            gene = [randint(0, 1) for _ in range(problemParam['noBits'])]
            self.__repress.append(gene)
        self.__fitness = 0.0

    @property
    def repress(self):
        # convert the binary matrix to a list of real values
        realRepress = []
        maxint = 2 ** self.__problemParam['noBits']
        for gene in self.__repress:
            intValue = binToInt(gene)
            realValue = self.__problemParam['min'] + intValue / maxint * (
                        self.__problemParam['max'] - self.__problemParam['min'])
            realRepress.append(realValue)
        return realRepress

    @property
    def fitness(self):
        return self.__fitness

    @repress.setter
    def repress(self, l = []):
        self.__repress = l

    @fitness.setter
    def fitness(self, fit=0.0):
        self.__fitness = fit

    def crossover(self, c):
        noBits = self.__problemParam['noBits']
        newrepress = []
        for geneM, geneF in zip(self.__repress, c.__repres):
            cuttingPoint = randint(0, noBits - 1)
            newGene = [geneM[i] if i < cuttingPoint else geneF[i] for i in range(noBits)]
            newrepress.append(newGene)
        offspring = Chromosome(self.__problemParam)
        offspring.repress = newrepress
        return offspring

    def mutation(self):
        gene = randint(0, len(self.__repress) - 1)
        bit = randint(0, len(self.__repress[0]) - 1)
        self.__repress[gene][bit] = 1 - self.__repress[gene][bit]

    def __str__(self):
        return '\nChromo: ' + str(self.__repress) + ' has fit: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__repress == c.__repres and self.__fitness == c.__fitness
