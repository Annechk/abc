!pip install numpy pandas scikit-learn matplotlib tensorflow -q

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import warnings
warnings.filterwarnings('ignore')

# LSTM КЛАСС


class TimeSeriesPredictor:
    def __init__(self, window_size=60):
        self.window_size = window_size
        self.model = None
        self.scaler = MinMaxScaler(feature_range=(0, 1))
        self.history = None

    def build_model(self):
        self.model = keras.Sequential([
            layers.LSTM(50, activation='relu', return_sequences=True,
                       input_shape=(self.window_size, 1)),
            layers.Dropout(0.2),
            layers.LSTM(50, activation='relu', return_sequences=False),
            layers.Dropout(0.2),
            layers.Dense(25, activation='relu'),
            layers.Dense(1)
        ])
        self.model.compile(
            optimizer=keras.optimizers.Adam(learning_rate=0.001),
            loss='mse',
            metrics=['mae']
        )

    def normalize(self, data):
        return self.scaler.fit_transform(data.reshape(-1, 1)).flatten()

    def denormalize(self, data):
        return self.scaler.inverse_transform(data.reshape(-1, 1)).flatten()

    def prepare_data(self, data):
        X, y = [], []
        for i in range(len(data) - self.window_size):
            X.append(data[i:i + self.window_size])
            y.append(data[i + self.window_size])
        return np.array(X).reshape(-1, self.window_size, 1), np.array(y)

    def train(self, data, epochs=50, validation_split=0.2, batch_size=32):
        normalized_data = self.normalize(data)
        X, y = self.prepare_data(normalized_data)

        split_idx = int(len(X) * (1 - validation_split))
        X_train, X_val = X[:split_idx], X[split_idx:]
        y_train, y_val = y[:split_idx], y[split_idx:]

        self.history = self.model.fit(
            X_train, y_train,
            validation_data=(X_val, y_val),
            epochs=epochs,
            batch_size=batch_size,
            verbose=1
        )

        return {
            'history': self.history.history,
            'X_val': X_val,
            'y_val': y_val,
            'normalized_data': normalized_data
        }

    def predict(self, last_window):
        last_window = last_window.reshape(1, self.window_size, 1)
        return self.model.predict(last_window, verbose=0)[0, 0]

    def make_predictions(self, normalized_data, num_steps=30):
        predictions = []
        current_window = normalized_data[-self.window_size:].copy()

        for _ in range(num_steps):
            pred = self.predict(current_window)
            predictions.append(pred)
            current_window = np.append(current_window[1:], pred)

        return np.array(predictions)

    def plot_training_history(self):
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

        epochs_range = np.arange(len(self.history.history['loss']))

        # Точность (возрастающая)
        train_acc = 1 / (1 + np.array(self.history.history['loss']))
        val_acc = 1 / (1 + np.array(self.history.history['val_loss']))

        ax1.plot(epochs_range, train_acc, color='#1f77b4', linewidth=2.5, label='Обучающая точность')
        ax1.plot(epochs_range, val_acc, color='#ff7f0e', linewidth=2.5, label='Валидационная точность')
        ax1.set_xlabel('Эпоха', fontsize=11)
        ax1.set_ylabel('Точность', fontsize=11)
        ax1.set_title('Точность обучения и валидации', fontsize=11, fontweight='bold', loc='left')
        ax1.grid(True, alpha=0.2)
        ax1.legend(loc='lower right', fontsize=10)

        # Потери (убывающие)
        ax2.plot(epochs_range, self.history.history['loss'], color='#1f77b4', linewidth=2.5, label='Обучающая функция потерь')
        ax2.plot(epochs_range, self.history.history['val_loss'], color='#ff7f0e', linewidth=2.5, label='Валидирующая функция потерь')
        ax2.set_xlabel('Эпоха', fontsize=11)
        ax2.set_ylabel('Функция потерь', fontsize=11)
        ax2.set_title('Функция потерь обучения и валидации', fontsize=11, fontweight='bold', loc='left')
        ax2.grid(True, alpha=0.2)
        ax2.legend(loc='upper right', fontsize=10)

        plt.tight_layout()
        plt.show()


# ГЕНЕРИРОВАНИЕ И ОБУЧЕНИЕ


np.random.seed(42)
trend = np.linspace(100, 150, 500)
noise = np.random.normal(0, 2, 500)
prices = trend + noise
prices = np.maximum(prices, 50)

predictor = TimeSeriesPredictor(window_size=60)
predictor.build_model()
results = predictor.train(prices, epochs=50, batch_size=32, validation_split=0.2)

# Графики обучения
predictor.plot_training_history()

predictions = predictor.make_predictions(results['normalized_data'], num_steps=30)
predictions_denorm = predictor.denormalize(predictions)

fig, ax = plt.subplots(figsize=(12, 6))

historical = prices[-100:]
future_days = np.arange(len(historical), len(historical) + len(predictions_denorm))

ax.plot(range(len(historical)), historical, color='#1f77b4', linewidth=2.5, label='Историческая цена')
ax.plot(future_days, predictions_denorm, color='#ff7f0e', linewidth=2.5, linestyle='--', label='Прогноз')
ax.axvline(x=len(historical)-1, color='red', linestyle=':', linewidth=1.5, alpha=0.7)

ax.set_xlabel('День', fontsize=11)
ax.set_ylabel('Цена ($)', fontsize=11)
ax.set_title('Прогнозирование цены акций с LSTM', fontsize=12, fontweight='bold', loc='left')
ax.grid(True, alpha=0.2)
ax.legend(fontsize=10)

plt.tight_layout()
plt.show()

# ОЦЕНКА КАЧЕСТВА


X_val = results['X_val']
y_val = results['y_val']

predictions_val = []
for i in range(len(X_val)):
    pred = predictor.predict(X_val[i].flatten())
    predictions_val.append(pred)

predictions_val = np.array(predictions_val)

mse = mean_squared_error(y_val, predictions_val)
mae = mean_absolute_error(y_val, predictions_val)
rmse = np.sqrt(mse)
r2 = r2_score(y_val, predictions_val)

print("\nМЕТРИКИ КАЧЕСТВА:")
print(f"MSE:  {mse:.6f}")
print(f"RMSE: {rmse:.6f}")
print(f"MAE:  {mae:.6f}")
print(f"R²:   {r2:.6f}")
