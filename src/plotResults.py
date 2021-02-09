import csv
import seaborn as sns
import pandas as pd

# apro il file csv e creo una lista con il nome delle colonne e una con i risultati
with open("/content/tempi.csv", "r", encoding='utf-8-sig') as f:
    lettore = csv.reader(f, delimiter=";")
    col_names = next(lettore)
    results = []
    for line in lettore:
        results.append(line)

# creo un dataframe
data = pd.DataFrame()

data[col_names[0]] = [item[0] for item in results]

data[col_names[1]] = [item[1] for item in results]

sns.scatterplot(data.diversi_n, data.tempi)

