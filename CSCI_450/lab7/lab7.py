import numpy

from keras.models import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from keras.utils import np_utils
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import KFold
from sklearn.preprocessing import LabelEncoder
from sklearn.pipeline import Pipeline

def get_model():
	# create model
	model = Sequential()
	model.add(Dense(3, input_dim=13, activation='relu'))
	model.add(Dense(8, activation='relu'))
	model.add(Dense(3, activation='softmax'))
	# compile model
	model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
	return model




# fix random seed for reproducibility
seed = 7
numpy.random.seed(seed)
"""
dataframe = pandas.read_csv("wine_train.csv", header=None)
dataset = dataframe.values
"""
dataset = numpy.loadtxt("wine_train.csv", delimiter=",")

X = dataset[:,1:14].astype(float)
Y = dataset[:,0]
# encode class values as integers
encoder = LabelEncoder()
encoder.fit(Y)
encoded_Y = encoder.transform(Y)
# convert integers to dummy variables (one hot encoded)
dummy_y = np_utils.to_categorical(encoded_Y)

# get the neural network model
model = get_model()
# use the model with the data
model.fit(X, dummy_y, epochs=150, batch_size=10)
# evaluate the model
scores = model.evaluate(X, dummy_y)
# print the accuracy percentage
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))
























