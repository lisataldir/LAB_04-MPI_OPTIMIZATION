import numpy as np
import matplotlib.pyplot as plt

num = 32*np.arange(1, 31, 1)

# Récupération des données
sb = []
with open(f'../pingpongv1.dat', 'r') as f:
    for line in f:
        sb += [float(num) for num in line.split()]


b = []
with open(f'../pingpongv2.dat', 'r') as f:
    for line in f:
        b += [float(num) for num in line.split()]


# Plot : Comparaison avec vs sans barrière
fig, ax = plt.subplots(1,1)

ax.plot(num, b, marker='*', color='#cb3717', label='Médiane avec barrière')
ax.plot(num, sb, marker='*', color='navy', label='Médiane sans barrière')

ax.grid(True, which='both', linestyle='-', alpha=0.5)
ax.set_xlabel('Taille du message (en octects)')
ax.set_ylabel('Temps (en s)')
ax.set_title("Comparaison avec et sans barrière")


plt.legend(loc = 'lower center', ncol=2, bbox_to_anchor = (0.05, -0.01, 1, 1),
        bbox_transform = plt.gcf().transFigure, edgecolor='black')
plt.subplots_adjust(bottom=0.3)
fig.tight_layout()

plt.savefig(f'pingpongv1_v2.png')

# Plot : Temps d'exécution sans barriere
fig, ax = plt.subplots(1,1)

ax.plot(num, sb, marker='*', color='navy', label='Médiane')
ax.grid(True, which='both', linestyle='-', alpha=0.5)
ax.set_xlabel('Taille du message (en octects)')
ax.set_ylabel('Temps (en s)')


plt.legend(loc = 'lower center', ncol=2, bbox_to_anchor = (0.05, -0.01, 1, 1),
        bbox_transform = plt.gcf().transFigure, edgecolor='black')
plt.subplots_adjust(bottom=0.3)
fig.tight_layout()

plt.savefig(f'pingpongv1.png')

# Plot : Temps d'exécution avec barrière
fig, ax = plt.subplots(1,1)

ax.plot(num, b, marker='*', color='#cb3717', label='Médiane')
ax.grid(True, which='both', linestyle='-', alpha=0.5)
ax.set_xlabel('Taille du message (en octects)')
ax.set_ylabel('Temps (en s)')


plt.legend(loc = 'lower center', ncol=2, bbox_to_anchor = (0.05, -0.01, 1, 1),
        bbox_transform = plt.gcf().transFigure, edgecolor='black')
plt.subplots_adjust(bottom=0.3)
fig.tight_layout()

plt.savefig(f'pingpongv2.png')