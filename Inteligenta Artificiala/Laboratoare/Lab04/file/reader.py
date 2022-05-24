
def read(filename):
    file = open(filename, 'r')
    n = int(file.readline())
    tsp = []
    for i in range(n):
        line = file.readline().split(",")
        numbers = []
        for arg in line:
            numbers.append(int(arg))
        tsp.append(numbers)

    file.close()

    return n, tsp
