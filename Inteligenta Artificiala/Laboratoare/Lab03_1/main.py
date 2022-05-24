from communityDetection import readNet, modularity
import os
import warnings
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx
from GA import GA


def main():
    # load a network
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, 'files', 'adjnoun.gml')
    network = readNet(filePath)

    # plot the network
    warnings.simplefilter('ignore')

    # initialise de GA parameters
    ga_param = {'popSize': 100, 'noGen': 50}
    # problem parameters
    problem_param = {'min': 1, 'max': 50, 'function': modularity, 'network': network, 'noNodes': network['noNodes']}

    ga = GA(ga_param, problem_param)
    ga.initialisation()
    ga.evaluation()

    for g in range(ga_param['noGen']):
        # ga.oneGeneration()
        # ga.oneGenerationElitism()
        ga.oneGenerationSteadyState()

        bestChromosome = ga.bestChromosome()

        communities = {}
        for i in range(len(bestChromosome.repres)):
            if bestChromosome.repres[i] in communities.keys():
                communities[bestChromosome.repres[i]].append(i)
            else:
                communities[bestChromosome.repres[i]] = [i]

        print('Best solution in generation ' + str(g) + ' is: ' + str(bestChromosome) + ' no. of communities = ' + str(len(communities)) + ' f(x) = ' + str(bestChromosome.fitness))

    chromosome = ga.bestChromosome()

    A = np.matrix(network["mat"])
    G = nx.from_numpy_matrix(A)
    pos = nx.spring_layout(G)  # compute graph layout
    plt.figure(figsize=(20, 20))  # image is 8 x 8 inches
    nx.draw_networkx_nodes(G, pos, node_size=800, cmap=plt.cm.RdYlBu, node_color=chromosome.repres)
    nx.draw_networkx_edges(G, pos, alpha=0.3)
    plt.show()

    communities = {}
    for i in range(len(chromosome.repres)):
        if chromosome.repres[i] in communities.keys():
            communities[chromosome.repres[i]].append(i)
        else:
            communities[chromosome.repres[i]] = [i]

    print("\nNumber of communities: " + str(len(communities)) + "\n")

    for k in communities:
        print("Community " + str(k) + ": " + str(communities[k]))


main()
