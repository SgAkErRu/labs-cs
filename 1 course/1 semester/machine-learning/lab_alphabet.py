# Модель, которая прогнозирует последующую букву алфавита по заданной последовательности.
# Примеры:
# {A -> B, B -> C, C -> D} для последовательности с длиной = 1
# {[A, B, C] -> D, [B, C, D] -> E} для последовательности с длиной = 3.

import numpy
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.utils import np_utils

numpy.random.seed(7)

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

# Словари для преобразования числа в букву и наоборот.
char_to_int = dict((c, i) for i, c in enumerate(alphabet))
int_to_char = dict((i, c) for i, c in enumerate(alphabet))

# Длина последовательности из букв алфавита.
seq_length = 3

# Подготавливаем выборки.
dataX = []
dataY = []
for i in range(0, len(alphabet) - seq_length, 1):
    seq_in = alphabet[i: i + seq_length]
    out = alphabet[i + seq_length]
    dataX.append([char_to_int[char] for char in seq_in])
    dataY.append(char_to_int[out])
    print(seq_in, '->', out)

# Меняем форму входных данных для соответствия блоку LSTM
# [количество объектов, размер временного ряда из объектов, количество признаков каждого объекта]
X = numpy.reshape(dataX, (len(dataX), 1, seq_length))

# Нормализация данных.
X = X / float(len(alphabet))
Y = np_utils.to_categorical(dataY)

print(Y.shape)

# Создание модели сети.
model = Sequential()
model.add(LSTM(32, input_shape=(X.shape[1], X.shape[2])))
model.add(Dense(Y.shape[1], activation='softmax'))

# Компиляция модели.
model.compile(
    loss='categorical_crossentropy',
    optimizer='adam',
    metrics=['accuracy'])

# Обучение модели.
model.fit(X, Y, epochs=500, batch_size=1, verbose=2)

# Вычисление точности модели.
scores = model.evaluate(X, Y, verbose=0)
print("Model Accuracy: %.2f%%" % (scores[1] * 100))

# Выведем результат - предсказание буквы алфавита для каждой последовательности в dataX
for pattern in dataX:
    x = numpy.reshape(pattern, (1, 1, len(pattern)))
    x = x / float(len(alphabet))
    prediction = model.predict(x, verbose=0)
    index = numpy.argmax(prediction)
    result = int_to_char[index]
    seq_in = [int_to_char[value] for value in pattern]
    print(seq_in, "->", result)
