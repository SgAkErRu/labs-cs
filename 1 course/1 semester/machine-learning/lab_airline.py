import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import tensorflow as tf
from tensorflow import keras

from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM

from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error


# Функция для создания выборки из исходного массива данных.
def create_dataset(dataset, look_back=1):

    dataX, dataY = [], []
    for i in range(len(dataset) - look_back - 1):
        a = dataset[i:(i + look_back), 0]
        dataX.append(a)
        dataY.append(dataset[i + look_back, 0])
    return np.array(dataX), np.array(dataY)


# Фиксация состояния рандома для получения повторяемого результата.
tf.random.set_seed(7)

# Загрузка данных.
dataframe: pd.DataFrame = pd.read_csv('airline-passengers.csv',
                                      usecols=[1],
                                      engine='python')
dataset = dataframe.values
dataset = dataset.astype('float32')

# Нормализация данных в диапазоне от 0 до 1.
scaler = MinMaxScaler(feature_range=(0, 1))
dataset = scaler.fit_transform(dataset)

# Ручное разделение данных на обучающую и тестовую выборку.
# 67% данных используются для обучения, а оставшиеся 33% для тестирования модели.
train_size = int(len(dataset) * 0.67)
test_size = len(dataset) - train_size
train = dataset[0:train_size, :]
test = dataset[train_size:len(dataset), :]

# Изменение исходного набора данных для того, чтобы в каждой строке X оказался
# временной ряд размером look_back, начиная от момента времени t0.
# А в Y временной ряд единичного размера от момента времени t0 + look_back.
# Например, для look_back = 4,
# X[0] будет состоять из объектов: Data[t0], Data[t1], Data[t2], Data[t3], а Y[0] из объектов: Data[t4].
# X[1] начнется с элемента Data[t1] и т.д.
look_back = 3
trainX, trainY = create_dataset(train, look_back)
testX, testY = create_dataset(test, look_back)

# Изменение формы входных данных и приведение их к виду
# [Количество объектов, размер временного ряда из объектов, количество признаков объекта].
# [samples, time steps, features]
trainX = np.reshape(trainX, (trainX.shape[0], trainX.shape[1], 1))
testX = np.reshape(testX, (testX.shape[0], testX.shape[1], 1))

# Параметры сети.
batch_size = 10
epoch_count = 1000

# Создание графа вычислений (некоторой абстрактной модели).
model = Sequential()

# 4 – это количество блоков LSTM, input_shape - это форма вектора входа.
lstm_block_count = 16
# model.add(LSTM(lstm_block_count, input_shape=(look_back, 1), return_sequences=True))
model.add(LSTM(lstm_block_count, input_shape=(look_back, 1)))
model.add(Dense(1))

# Компиляция модели
model.compile(loss='mean_squared_error', optimizer='adam')

# Обучение модели
model.fit(trainX, trainY, epochs=epoch_count, batch_size=batch_size, verbose=2)

# Выполнение предсказания.
trainPredict = model.predict(trainX)
testPredict = model.predict(testX)

# Так как прогнозное значение нормализовано, то необходимо его восстановление
# (под восстановлением понимается приведение к исходному масштабу данных).
trainPredict = scaler.inverse_transform(trainPredict)
trainY = scaler.inverse_transform([trainY])
testPredict = scaler.inverse_transform(testPredict)
testY = scaler.inverse_transform([testY])

# Вычисление ошибки прогноза.
trainScore = np.sqrt(mean_squared_error(trainY[0], trainPredict[:, 0]))
print('Train Score: %.2f RMSE' % (trainScore))
testScore = np.sqrt(mean_squared_error(testY[0], testPredict[:, 0]))
print('Test Score: %.2f RMSE' % (testScore))

# Подготовка данных для отрисовки.
trainPredictPlot = np.empty_like(dataset)
trainPredictPlot[:, :] = np.nan
trainPredictPlot[look_back:len(trainPredict) + look_back, :] = trainPredict

testPredictPlot = np.empty_like(dataset)
testPredictPlot[:, :] = np.nan
testPredictPlot[len(trainPredict) + (look_back * 2) + 1:len(dataset) -
                1, :] = testPredict

# Построение графика
plt.plot(scaler.inverse_transform(dataset))
plt.plot(trainPredictPlot)
plt.plot(testPredictPlot)
plt.show()
