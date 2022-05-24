import numpy
import networkx


def readNet(fileName):
    network = {}

    # for karate.gml:
    # graph = networkx.read_gml(fileName, label='id')

    # for the rest:
    graph = networkx.read_gml(fileName)
    matrix = networkx.adjacency_matrix(graph).todense()
    array = numpy.squeeze(numpy.asarray(matrix))

    matrix = []
    for i in array:
        elements = []
        for j in i:
            elements.append(int(j))
        matrix.append(elements)

    n = len(matrix)
    network['noNodes'] = n
    network["mat"] = matrix

    degrees = []
    noEdges = 0
    for i in range(n):
        d = 0
        for j in range(n):
            if matrix[i][j] == 1:
                d += 1
            if j > i:
                noEdges += matrix[i][j]
        degrees.append(d)
    network["noEdges"] = noEdges
    network["degrees"] = degrees

    return network


def modularity(communities, param):
    noNodes = param['noNodes']
    mat = param['mat']
    degrees = param['degrees']
    noEdges = param['noEdges']

    M = 2 * noEdges
    Q = 0.0

    for i in range(0, noNodes):
        for j in range(0, noNodes):
            if communities[i] == communities[j]:
                Q += (mat[i][j] - degrees[i] * degrees[j] / M)

    return Q * 1 / M
