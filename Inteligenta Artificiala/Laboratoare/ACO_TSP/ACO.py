import random
import math


def distance(start, end):
    x_distance = abs(start[0] - end[0])
    y_distance = abs(start[1] - end[1])
    return math.sqrt(pow(x_distance, 2) + pow(y_distance, 2))


class Graph(object):
    def __init__(self, cost_matrix: list, rank: int):
        """
        :param cost_matrix: matricea costurilor
        :param rank: rang-ul matricii
        """
        self.matrix = cost_matrix
        self.rank = rank
        self.pheromone = [[1 / (rank * rank) for _ in range(rank)] for _ in range(rank)]


class ACO(object):
    def __init__(self, ant_count: int, iterations: int, alpha: float, beta: float, rho: float, q: int):
        """
        :param ant_count: numarul de furnici
        :param iterations: numarul de iteratii
        :param alpha: controleaza influenta feromonilor
        :param beta: controleaza influenta distantei
        :param rho: coeficientul de degradare
        :param q: intensitatea feromonului
        """
        self.Q = q
        self.rho = rho
        self.beta = beta
        self.alpha = alpha
        self.ant_count = ant_count
        self.iterations = iterations

    def _update_pheromone(self, graph: Graph, ants: list):
        for i, row in enumerate(graph.pheromone):
            for j, col in enumerate(row):
                graph.pheromone[i][j] *= self.rho
                for ant in ants:
                    graph.pheromone[i][j] += ant.pheromone_delta[i][j]

    def solve(self, graph: Graph):
        best_cost = float('inf')
        best_solution = []
        for _ in range(self.iterations):
            ants = [_Ant(self, graph) for _ in range(self.ant_count)]
            for ant in ants:
                for i in range(graph.rank - 1):
                    ant.select_next()
                ant.total_cost += graph.matrix[ant.tabu[-1]][ant.tabu[0]]
                if ant.total_cost < best_cost:
                    best_cost = ant.total_cost
                    best_solution = [] + ant.tabu
                ant.update_pheromone_delta()
            self._update_pheromone(graph, ants)
        return best_solution, best_cost


class _Ant(object):
    def __init__(self, aco: ACO, graph: Graph):
        self.colony = aco
        self.graph = graph
        self.total_cost = 0.0
        self.tabu = []                                                          # tabu list - ruta facuta de o furnica
        self.pheromone_delta = []                                               # cresterea locala a feromonului
        self.possible_locations = [i for i in range(graph.rank)]                # lista posibilelor locatii pe care le poate vizita furnica
        self.eta = [[0 if i == j else 1 / graph.matrix[i][j]
                     for j in range(graph.rank)] for i in range(graph.rank)]    # informatia euristica
        start = random.randint(0, graph.rank - 1)                               # incep de la un nod aleator
        self.tabu.append(start)
        self.current = start
        self.possible_locations.remove(start)

    def select_next(self):
        denominator = 0
        for possible_location in self.possible_locations:
            # feromon^alpha * distanta^beta
            denominator += self.graph.pheromone[self.current][possible_location] ** self.colony.alpha * self.eta[self.current][possible_location] ** self.colony.beta

        probabilities = [0 for _ in range(self.graph.rank)]
        for i in range(self.graph.rank):
            try:
                self.possible_locations.index(i)
                # (feromon^alpha * distanta^beta) / denominator
                probabilities[i] = self.graph.pheromone[self.current][i] ** self.colony.alpha * self.eta[self.current][i] ** self.colony.beta / denominator
            except ValueError:
                pass

        selected = 0
        rand = random.random()
        for i, probability in enumerate(probabilities):
            rand -= probability
            if rand <= 0:
                selected = i
                break
        self.possible_locations.remove(selected)
        self.tabu.append(selected)
        self.total_cost += self.graph.matrix[self.current][selected]
        self.current = selected

    def update_pheromone_delta(self):
        self.pheromone_delta = [[0 for _ in range(self.graph.rank)] for _ in range(self.graph.rank)]
        for _ in range(1, len(self.tabu)):
            i = self.tabu[_ - 1]
            j = self.tabu[_]
            self.pheromone_delta[i][j] = self.colony.Q
