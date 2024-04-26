import numpy as np

def get_file(filename):
    with open(filename, 'r') as f:
        content = np.array([float(line.strip()) for line in f.readlines() if line.strip()])

    print(f"{np.median(content):.5e}")


for i in range (1, 31):
    get_file(f"data_v2/data{i}.dat")