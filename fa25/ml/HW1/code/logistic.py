import numpy as np

def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))

def logistic(X, y):
    '''
    LR Logistic Regression.

    INPUT:  X: training sample features, P-by-N matrix.
            y: training sample labels, 1-by-N row vector.

    OUTPUT: w: learned parameters, (P+1)-by-1 column vector.
    '''
    P, N = X.shape
    w = np.zeros((P + 1, 1)) # (P+1,1)
    # YOUR CODE HERE
    # begin answer
    #TODO
    X = np.vstack((np.ones((1, N)), X)) # (P+1,N)
    learning_rate = 0.1
    n_iter = 1000
    for i in range(n_iter):
        z = w.T @ X # (1,N)
        p = sigmoid(-y * z) #  compute sigmoid probability,y in {-1,1}
        # optimization target: log(1 + exp{-y_i w.T x_i})
        grad = -X @ (y * p).T / N # (P+1,1),divide N for avg loss
        w = w - learning_rate * grad
    # end answer
    
    return w
