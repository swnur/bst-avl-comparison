import matplotlib.pyplot as plt
import pandas as pd

# with open("final_results.txt", "r") as file:
#    for _ in range(5):  # Print the first 5 lines
#        print(file.readline())

# Graph of sorted data

data_sorted = pd.read_csv("results_sorted_size10k.txt", delimiter=' ')
data_sorted = data_sorted.set_index("Size")

print("Loaded data:")
print(data_sorted.head())

data_sorted[["BST-Insert", "AVL-Insert"]].plot(linewidth=4)
plt.title("Insertion time(Sorted data)")
plt.savefig("sorted_insertion_size10k.png")

data_sorted[["BST-Find", "AVL-Find"]].plot(linewidth=4)
plt.title("Search time(Sorted data)")
plt.savefig("sorted_search_size10k.png")

# Graph of partially sorted data

data_part_sorted = pd.read_csv("results_part_sorted_size10k.txt", delimiter=' ')
data_part_sorted = data_part_sorted.set_index("Size")

print("Loaded data:")
print(data_part_sorted.head())

data_part_sorted[["BST-Insert", "AVL-Insert"]].plot(linewidth=4)
plt.title("Insertion time(Partially Sorted data)")
plt.savefig("partially_sorted_insertion_size10k.png")

data_part_sorted[["BST-Find", "AVL-Find"]].plot(linewidth=4)
plt.title("Search time(Sorted data)")
plt.savefig("partially_sorted_search_size10k.png")

# Graph of random data

data_rand = pd.read_csv("results_rand_size10k.txt", delimiter=' ')
data_rand = data_rand.set_index("Size")

print("Loaded data:")
print(data_rand.head())

data_rand[["BST-Insert", "AVL-Insert"]].plot(linewidth=4)
plt.title("Insertion time(Random data)")
plt.savefig("random_insertion_size10k.png")

data_rand[["BST-Find", "AVL-Find"]].plot(linewidth=4)
plt.title("Search time(Random data)")
plt.savefig("random_search_size10k.png")

