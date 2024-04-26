import matplotlib.pyplot as plt
import numpy as np

b = []
with open(f'../data/resultsv0.dat', 'r') as f:
    for line in f:
        b += [[float(num) for num in line.split()]]

b = np.array(b)

fig, ax = plt.subplots()
ax.plot(b[:,0], b[:,1], marker='*')
ax.set_xlabel("Nombre de processus")
ax.set_ylabel("Temps d'exécution (en s)")
ax.grid(True)
# ax.set_title("Évolution du temps d'exécution en fonction du nombre de processus")

plt.savefig(f'benchmarkv0.png')

b = []
with open(f'../data/resultsv1.dat', 'r') as f:
    for line in f:
        b += [[float(num) for num in line.split()]]

b = np.array(b)

fig, ax = plt.subplots()
ax.plot(b[:,0], b[:,1], marker='*')
ax.set_xlabel("Nombre de processus")
ax.set_ylabel("Temps d'exécution (en s)")
ax.grid(True)
# ax.set_title("Évolution du temps d'exécution en fonction du nombre de processus")

plt.savefig(f'benchmarkv1.png')