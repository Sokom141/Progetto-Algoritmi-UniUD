import csv
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# apro il file csv e creo una lista con il nome delle colonne e una con i risultati
with open("tempi.csv", "r", encoding='utf-8-sig') as f:
    lettore = csv.reader(f, delimiter=",")
    col_names = next(lettore)
    results = []
    for line in lettore:
        results.append(line)
        print(line)

# creo un dataframe
data = pd.DataFrame()

data[col_names[0]] = [item[0] for item in results]
data[col_names[1]] = [item[1] for item in results]

print(data)

sns.lineplot(x="N", y="TIME", data=data)

plt.title("Test Plot")
plt.grid()
plt.gca().invert_yaxis()
plt.savefig("image.png")
