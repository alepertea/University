from sklearn import linear_model


def model(gdp, freedom, outputs):
    x = [[el1, el2] for el1, el2 in zip(gdp, freedom)]
    regressor = linear_model.LinearRegression()
    regressor.fit(x, outputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    print('The learnt model: f(x) = ', w2, ' * x^2 + ', w1, ' * x + ', w0)
