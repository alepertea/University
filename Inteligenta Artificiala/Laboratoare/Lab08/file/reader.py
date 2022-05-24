import csv


def load_data(filename, first_feature, second_feature, output):
    data = []
    data_names = []

    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                data_names = row
            else:
                data.append(row)
            line_count += 1

    selected_variable = data_names.index(first_feature)
    gdp_per_capita = [float(data[i][selected_variable]) for i in range(len(data))]

    selected_variable = data_names.index(second_feature)
    freedom = [float(data[i][selected_variable]) for i in range(len(data))]

    selected_output = data_names.index(output)
    outputs = [float(data[i][selected_output]) for i in range(len(data))]

    return gdp_per_capita, freedom, outputs
