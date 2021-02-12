import csv
import seaborn as sns
import pandas as pd
import math
import matplotlib.pyplot as plt


def plotta_risultati(percorsoSmart, percorsoNaive):
    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati

    with open(percorsoSmart, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo un dataframe
    dataSmart = pd.DataFrame()

    dataSmart[col_names[0]] = [item[0] for item in results]

    dataSmart[col_names[1]] = [item[1] for item in results]

    dataSmart["TIME"] = pd.to_numeric(dataSmart["TIME"])

    dataSmart["N"] = pd.to_numeric(dataSmart["N"])

    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati
    with open(percorsoNaive, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo  un dataframe
    data = pd.DataFrame()

    data[col_names[0]] = [item[0] for item in results]

    data[col_names[1]] = [item[1] for item in results]

    data["TIME"] = pd.to_numeric(data["TIME"])

    data["N"] = pd.to_numeric(data["N"])
    plt.figure(figsize=(20, 10))
    ax1 = sns.lineplot(data.N, data.TIME)
    ax2 = sns.lineplot(dataSmart.N, dataSmart.TIME)
    scatter1 = sns.scatterplot(data.N, data.TIME)
    scatter2 = sns.scatterplot(dataSmart.N, dataSmart.TIME)
    ax1.set(xlabel="LUNGHEZZA STRINGA")

    ax1.set(ylabel="TEMPO MEDIO")

    plt.legend(title="Legenda", title_fontsize="xx-large", loc='upper right', labels=['Naive', 'Smart'],
               fontsize="xx-large", facecolor="lightgrey")

    plt.title("Tempi di computazione dei due algoritmi", fontdict={"fontsize": "xx-large", "color": "black"})
    plt.show()


def plotta_risultati_scala_logaritmica(percorsoSmart, percorsoNaive):
    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati

    with open(percorsoSmart, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo un dataframe
    dataSmart = pd.DataFrame()

    dataSmart[col_names[0]] = [item[0] for item in results]

    dataSmart[col_names[1]] = [item[1] for item in results]

    dataSmart["TIME"] = pd.to_numeric(dataSmart["TIME"])

    dataSmart["N"] = pd.to_numeric(dataSmart["N"])

    # apro il file csv e creo una lista con il nome delle colonne e una con i risultati
    with open(percorsoNaive, "r", encoding='utf-8-sig') as f:
        lettore = csv.reader(f, delimiter=",")
        col_names = next(lettore)
        results = []
        for line in lettore:
            results.append(line)

    # creo  un dataframe
    data = pd.DataFrame()

    data[col_names[0]] = [item[0] for item in results]

    data[col_names[1]] = [item[1] for item in results]

    data["TIME"] = pd.to_numeric(data["TIME"])

    data["N"] = pd.to_numeric(data["N"])

    plt.figure(figsize=(20, 10))
    ax1 = sns.lineplot(data.N, data.TIME)
    ax2 = sns.lineplot(dataSmart.N, dataSmart.TIME)

    ax1.set(xscale="log", xlabel="LUNGHEZZA STRINGA")

    ax1.set(yscale="log", ylabel="TEMPO MEDIO")

    sns.scatterplot(data.N, data.TIME, )
    sns.scatterplot(dataSmart.N, dataSmart.TIME)

    plt.legend(title="Legenda", title_fontsize="xx-large", loc='upper right', labels=['Naive', 'Smart'],
               fontsize="xx-large", facecolor="lightgrey")

    plt.title("Tempi di computazione dei due algoritmi con scala logaritmica",
              fontdict={"fontsize": "xx-large", "color": "black"})
    plt.show()




