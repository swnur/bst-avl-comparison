import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("results_avl_insert.txt", delimiter=' ')
data = data.set_index("Size")

print("Loaded data:")
print(data.head())

data[["AVL-IterInsert", "AVL-RecurInsert"]].plot(linewidth=4)
plt.title("Insertion time(AVL)")
plt.savefig("avl_insertion.png")
