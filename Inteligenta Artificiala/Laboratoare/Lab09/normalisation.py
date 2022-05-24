from sklearn.preprocessing import StandardScaler


def normalize(train_data, test_data):
    scaler = StandardScaler()
    if not isinstance(train_data[0], list):
        train_data = [[data] for data in train_data]
        test_data = [[data] for data in test_data]

        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_test_data = scaler.transform(test_data)

        normalised_train_data = [el[0] for el in normalised_train_data]
        normalised_test_data = [el[0] for el in normalised_test_data]
    else:
        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_test_data = scaler.transform(test_data)

    return normalised_train_data, normalised_test_data
