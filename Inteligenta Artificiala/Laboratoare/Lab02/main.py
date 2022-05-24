import random
from file import reader, writer
from queue import PriorityQueue


def bfs(tsp, source, destination):
    solution = []

    queue = PriorityQueue()
    queue.put((0, source))

    visited = [False] * len(tsp)
    visited[source] = True

    while not queue.empty():
        node = queue.get()[1]
        solution.append(node)

        for neighbour in range(len(tsp)):
            if not visited[neighbour]:
                visited[neighbour] = True
                queue.put((tsp[node][neighbour], neighbour))

        if node == destination:
            break

    return solution


def compute_route_length(tsp, route):
    length = 0
    for i in range(len(tsp) - 1):
        length += tsp[route[i]][route[i + 1]]
    return length


def random_solution(tsp):
    cities = list(range(len(tsp)))
    solution = [0]

    for i in range(len(cities)):
        randomCity = cities[random.randint(0, len(cities) - 1)]
        if randomCity != 0:
            solution.append(randomCity)
        cities.remove(randomCity)

    return solution


def route_length(tsp, solution):
    length = 0
    for i in range(len(solution)):
        length += tsp[solution[i - 1]][solution[i]]
    return length


def get_neighbours(solution):
    neighbours = []
    for i in range(1, len(solution)):
        for j in range(i + 1, len(solution)):
            neighbour = solution.copy()
            neighbour[i] = solution[j]
            neighbour[j] = solution[i]
            neighbours.append(neighbour)
    return neighbours


def get_best_neighbour(tsp, neighbours):
    best_route_length = route_length(tsp, neighbours[0])
    best_neighbour = neighbours[0]
    for neighbour in neighbours:
        current_route_length = route_length(tsp, neighbour)
        if current_route_length < best_route_length:
            best_route_length = current_route_length
            best_neighbour = neighbour
    return best_neighbour, best_route_length


def hill_climbing(tsp):
    current_solution = random_solution(tsp)
    current_route_length = route_length(tsp, current_solution)
    neighbours = get_neighbours(current_solution)
    best_neighbour, best_route_length = get_best_neighbour(tsp, neighbours)

    while best_route_length < current_route_length:
        current_solution = best_neighbour
        current_route_length = best_route_length
        neighbours = get_neighbours(current_solution)
        best_neighbour, best_route_length = get_best_neighbour(tsp, neighbours)

    return current_solution, current_route_length


def main():
    n, tsp, source, destination = reader.read("hard_01_tsp.txt")

    solution, routeLength = hill_climbing(tsp)
    writer.write_first_solution(n, solution, routeLength, "output.txt")

    solution2 = bfs(tsp, source - 1, destination - 1)
    length = compute_route_length(tsp, solution2)
    writer.write_second_solution(tsp, solution2, length, "output.txt")


if __name__ == "__main__":
    main()
