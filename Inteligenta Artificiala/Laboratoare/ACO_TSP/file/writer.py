
def write(n, route, route_length, filename):
    file = open(filename, 'w')

    solution = []
    for i in route:
        solution.append(i + 1)

    file.write(str(n) + '\n')
    routeString = ''
    for i in range(len(solution) - 1):
        routeString += str(solution[i]) + ','
    routeString += str(solution[n - 1]) + '\n'

    file.write(str(routeString))
    file.write(str(route_length) + '\n')

    file.close()
