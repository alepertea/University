
def read(filename):
    file = open(filename, 'r')

    name = file.readline().strip().split(':')[1]                # NAME
    comment = file.readline().strip().split(':')[1]             # COMMENT
    type = file.readline().strip().split(':')[1]                # TYPE
    dimension = file.readline().strip().split(':')[1]           # DIMENSION
    edge_weight_type = file.readline().strip().split(':')[1]    # EDGE_WEIGHT_TYPE
    node_coord_section = dict()                                 # NODE_COORD_SECTION
    file.readline()

    for i in range(int(dimension)):
        line = file.readline().strip().split(' ')
        node, x, y = int(line[0]), float(line[1]), float(line[2])
        node_coord_section[node - 1] = [x, y]

    file.close()

    return {
        'NAME': name,
        'COMMENT': comment,
        'TYPE': type,
        'DIMENSION': dimension,
        'EDGE_WEIGHT_TYPE': edge_weight_type,
        'NODE_COORD_SECTION': node_coord_section
    }
