# Grapicas a generar
# Realizado por Jaime Lorenzo Sanchez

# Eje x -> Muestras
# Eje Y -> Voltaje

import matplotlib.pyplot as plt

muestras = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]

senoidal_1hz = [4.06,4.07,4.07,4.07,4.08,4.08,4.09,4.09,4.09,4.10,4.10,4.10,4.11,4.12,4.12,4.12,4.12,4.13,4.13,4.13]
triangular_1hz = [2.59, 2.59, 2.59, 2.60, 2.60, 2.61, 2.61, 2.61, 2.61, 2.61, 2.61, 2.61, 2.61, 2.62, 2.62, 2.62, 2.62, 2.63, 2.63, 2.63]

senoidal_50hz = [1.70,1.83,1.97,2.12,2.27,2.41,2.57,2.73,2.89,3.05,3.22,3.38,3.55,3.72,3.90,4.07,4.25,4.42,4.60,4.78]
triangular_50hz = [5.00, 5.00, 5.00, 5.00, 4.98, 4.86, 4.74, 4.63, 4.53, 4.41, 4.30, 4.19, 4.08, 3.96, 3.85, 3.73, 3.62, 3.51, 3.40, 3.28]

senoidal_100hz = [1.96, 2.25, 2.56,2.87,3.20,3.54,3.89,4.23,4.58,4.94,5.00,5.00,5.00,5.00,5.00,5.00,5.00,5.00,5.00,5.00]
triangular_100hz = [5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00, 5.00]

senoidal_1000hz = [3.64,5.00,5.00,5.00,5.00,4.45,1.35,0.00,0.97,3.85,5.00,5.00,5.00,5.00,4.21,1.18,0.00,1.12,4.09,5.00]
triangular_1000hz = [5.00, 5.00, 5.00, 2.91, 0.57, 1.66, 3.90, 5.00, 5.00, 5.00, 4.88, 2.65, 0.41, 1.82, 4.06, 5.00, 5.00, 5.00, 5.00,5.00]

senoidal_1500hz = [2.62,5.00,5.00,5.00,2.17,0.00,2.85,5.00,5.00,5.00,1.96,0.00,3.06,5.00,5.00,5.00,1.77,0.12,3.68,5.00]
triangular_1500hz = [3.91, 5.00, 5.00, 5.00, 2.62, 0.73, 4.07, 5.00, 5.00, 5.00, 2.45, 0.89, 4.23, 5.00, 5.00, 5.00, 2.30, 1.05, 4.39, 5.00]

senoidal_3000hz = [ 5.00,5.00,0.04,5.00,5,0.00,5.00,5.00,0.00,5.00,5.00,0.00,5.00,5.00,0.00,5.00,5.00,0.00,5.00,5.00]
triangular_3000hz = [0.72, 5.00, 5.00, 0.88, 5.00, 5.00, 1.04, 5.00, 5.00, 1.19, 5.00, 5.00, 1.37, 5.00, 5.00, 1.52, 5.00, 5.00, 1.68, 5.00]

senoidal_5000hz = [5,00,5.00,1.27,5.00,4.63,3.40,5.00,0.55,5.00,0.08,5.00,2.27,5.00,5.00,2.26,5.00,0.08,5.00,0.55 ]
triangular_5000hz = [ 5.00, 3.29, 5.00, 5.00, 3.04, 5.00, 0.63, 5.00, 1.72, 5.00, 4.08, 4.64, 5.00, 2.24, 5.00, 0.09, 5.00, 2.51, 5.00, 4.87]

senoidal_10000hz = [5.00, 5.00, 5.00, 3.14, 0.41, 0.11, 2.46, 5.00, 5.00, 5.00, 5.00, 4.38, 1.11, 0.00, 1.44, 4.89, 5.00, 5.00, 5.00, 3.14]
triangular_10000hz = [1.88, 0.43, 2.85, 5.00, 5.00, 5.00, 5.00, 2.66, 0.25, 2.07, 4.47, 5.00, 5.00, 4.47, 5.00, 5.00, 3.45, 1.03, 1.27, 3.67]

# Generamos la graficas para 1 hz

# plt.plot(muestras,senoidal_1hz,label='Senal senoidal');plt.plot(muestras, triangular_1hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 1hz'); plt.legend(); plt.show()

# Generamos la grafica para 50 hz

# plt.plot(muestras,senoidal_50hz,label='Senal senoidal');plt.plot(muestras, triangular_50hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 50hz'); plt.legend(); plt.show()

# Generamos la grafica para 100 hz

# plt.plot(muestras,senoidal_100hz,label='Senal senoidal');plt.plot(muestras, triangular_100hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 100hz'); plt.legend(); plt.show()

# Generamos la grafica para 1000 hz

# plt.plot(muestras,senoidal_1000hz,label='Senal senoidal');plt.plot(muestras, triangular_1000hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 1000hz'); plt.legend(); plt.show()

# Generamos la grafica para 1500 hz

# plt.plot(muestras,senoidal_1500hz,label='Senal senoidal');plt.plot(muestras, triangular_1500hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 1500hz'); plt.legend(); plt.show()

# Generamos la grafica de 3000 hz

# plt.plot(muestras,senoidal_3000hz,label='Senal senoidal');plt.plot(muestras, triangular_3000hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 3000hz'); plt.legend(); plt.show()

# Generamos la grafica de 5000 hz

# plt.plot(muestras,senoidal_5000hz,label='Senal senoidal');plt.plot(muestras, triangular_5000hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 5000hz'); plt.legend(); plt.show()

# Generamos la grafica de 10000 hz

plt.plot(muestras,senoidal_10000hz,label='Senal senoidal');plt.plot(muestras, triangular_10000hz, label = 'Senal triangular');plt.xlabel('Numero de muestras'); plt.ylabel('Amplitud en voltios'); plt.title ('Frecuencia de 10000hz'); plt.legend(); plt.show()
