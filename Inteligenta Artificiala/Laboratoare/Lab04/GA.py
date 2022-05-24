from random import randint


def route_length(route, param):
    length = 0
    for i in range(len(route) - 1):
        length += param[route[i]][route[i + 1]]
    length += param[route[0]][route[len(route) - 1]]
    return length


def generate_random_permutation(n):
    perm = [i for i in range(n)]
    pos1 = randint(1, n - 1)
    pos2 = randint(1, n - 1)
    perm[pos1], perm[pos2] = perm[pos2], perm[pos1]
    return perm


class Chromosome:
    def __init__(self, problemParam=None):
        self.__problemParam = problemParam
        self.__representation = generate_random_permutation(self.__problemParam['noNodes'])
        self.__fitness = 0.0

    @property
    def representation(self):
        return self.__representation

    @property
    def fitness(self):
        return self.__fitness

    @representation.setter
    def representation(self, l=[]):
        self.__representation = l

    @fitness.setter
    def fitness(self, fit=0.0):
        self.__fitness = fit

    def crossover(self, c):
        pos1 = randint(1, self.__problemParam['noNodes'] - 1)
        pos2 = randint(pos1, self.__problemParam['noNodes'] - 1)

        repres1 = [0]
        for i in range(pos1, pos2):
            repres1.append(c.__representation[i])

        repres2 = [el for el in self.__representation if el not in repres1]

        new_representation = repres1 + repres2

        offspring = Chromosome(self.__problemParam)
        offspring.representation = new_representation
        return offspring

    def mutation(self):
        pos1 = randint(1, self.__problemParam['noNodes'] - 1)
        pos2 = randint(1, self.__problemParam['noNodes'] - 1)
        self.__representation[pos1], self.__representation[pos2] = self.__representation[pos2], self.__representation[pos1]

    def __str__(self):
        return "\nChromosome " + str(self.__representation) + " has fit " + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__representation == c.__representation and self.__fitness == c.__fitness


class GA:
    def __init__(self, param=None, problemParam=None):
        self.__param = param
        self.__problemParam = problemParam
        self.__population = []

    @property
    def population(self):
        return self.__population

    def initialisation(self):
        for _ in range(0, self.__param['popSize']):
            c = Chromosome(self.__problemParam)
            self.__population.append(c)

    def evaluation(self):
        for c in self.__population:
            c.fitness = self.__problemParam['function'](c.representation, self.__problemParam['cities'])
            print(c)

    def bestChromosome(self):
        best = self.__population[0]
        for c in self.__population:
            if c.fitness < best.fitness:
                best = c
        return best

    def worstChromosome(self):
        best = self.__population[0]
        for c in self.__population:
            if c.fitness > best.fitness:
                best = c
        return best

    def selection(self):
        pos1 = randint(0, self.__param['popSize'] - 1)
        pos2 = randint(0, self.__param['popSize'] - 1)
        if self.__population[pos1].fitness < self.__population[pos2].fitness:
            return pos1
        else:
            return pos2

    def oneGeneration(self):
        newPop = []
        for _ in range(self.__param['popSize']):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            off = p1.crossover(p2)
            off.mutation()
            newPop.append(off)
        self.__population = newPop
        self.evaluation()
