from file import reader, writer
from GA import GA, route_length
from math import factorial


def main():
    n, tsp = reader.read("data/easy_02_tsp.txt")
    ga_param = {'popSize': factorial(n), 'noGen': 1}
    problem_param = {'noNodes': n, 'cities': tsp, 'function': route_length}

    ga = GA(ga_param, problem_param)
    ga.initialisation()
    ga.evaluation()

    solution = None
    for g in range(ga_param['noGen']):
        ga.oneGeneration()
        bestChromosome = ga.bestChromosome()
        print('Best solution in generation ' + str(g + 1) + ' is: ' + str(bestChromosome))
        solution = bestChromosome

    writer.write(n, solution.representation, route_length(solution.representation, tsp), 'output.txt')


main()
