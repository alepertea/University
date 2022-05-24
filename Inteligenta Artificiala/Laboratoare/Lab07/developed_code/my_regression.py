def initialise(rows, cols):
    matrix = []
    for _ in range(rows):
        matrix.append([0 for _ in range(cols)])
    return matrix


def multiplication(first_matrix, second_matrix):
    result = initialise(len(first_matrix), len(second_matrix[0]))
    for i in range(len(first_matrix)):
        for j in range(len(second_matrix[0])):
            for k in range(len(second_matrix)):
                result[i][j] += first_matrix[i][k] * second_matrix[k][j]
    return result


def inverted(matrix):
    det = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[2][1] * matrix[0][2] + matrix[0][1] * \
          matrix[1][2] * matrix[2][0] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[1][2] * matrix[2][1] * \
          matrix[0][0] - matrix[1][0] * matrix[0][1] * matrix[2][2]
    transpose = [[el1, el2, el3] for el1, el2, el3 in zip(matrix[0], matrix[1], matrix[2])]
    inverted_matrix = []
    for i in range(3):
        row = []
        for j in range(3):
            M = []
            for ii in range(3):
                r = []
                for jj in range(3):
                    if ii != i and jj != j:
                        r.append(transpose[ii][jj])
                if r:
                    M.append(r)
            d = M[0][0] * M[1][1] - M[0][1] * M[1][0]
            put = (-1) ** (i + j + 2)
            row.append(put * d * (1 / det))
        inverted_matrix.append(row)
    return inverted_matrix


def my_linear_regression(gdp, freedom, outputs):
    x = [[1, el1, el2] for el1, el2 in zip(gdp, freedom)]
    ones = []
    for _ in range(len(gdp)):
        ones.append(1)
    x_transpose = [ones, gdp, freedom]

    m = multiplication(x_transpose, x)
    m_inv = inverted(m)

    res = multiplication(m_inv, x_transpose)

    outputs_transpose = [[el] for el in outputs]
    final_res = multiplication(res, outputs_transpose)

    w0, w1, w2 = final_res[0][0], final_res[1][0], final_res[2][0]
    print('The learnt model: f(x) = ', w2, ' * x^2 + ', w1, ' * x + ', w0)
