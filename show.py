import matplotlib.pyplot as plt

with open("result.txt","r") as f:
    arr = f.read().split("\n")

arr = arr[:2000]
arr = [int(x) for x in arr]

plt.figure()
plt.plot(arr)
plt.show()
