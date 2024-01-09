from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np

AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'green', "BERKMAN_VISHKIN": 'red'} 

def plotRunningTimeAllInputTypes(Es, P, logscale):
    for inputType in ["RANDOM", "SORTED", "MERGE"]:
        plotRunningTime(Es, inputType, P, "Running times (all inputs, all algorithms, blocksize = 8192, P = " + str(P), logscale)

def plotRunningTime(NTs_, inputType, p, title, logScale):
    NTs = [(e.n, e.averageTime, e.algorithmType, e.numberOfCores) for e in NTs_ if (e.inputType == inputType and e.numberOfCores == p)]
    Cmap = {a:AtoC[a] for a in set([e[2] for e in NTs]) } 

    _, ax = plt.subplots()
    N = np.array([n for n, _, _, _ in NTs])
    T = np.array([t for _, t, _, _ in NTs])
    C = np.array([Cmap[a] for _, _, a, _ in NTs])

    for algorithmType, color in Cmap.items():
        ix = np.where(C == color)
        ax.scatter(N[ix], T[ix], c=color, label=algorithmType + " " + inputType, s=25)
        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('n')
    ax.set_ylabel('Running time in seconds')
    ax.set_title(title)
    ax.legend()
    plt.show()

Es = parseFile("runningTime.txt")
plotRunningTimeAllInputTypes(Es, 1, False)
plotRunningTimeAllInputTypes(Es, 48, False)

# Without sequential for P = 48
Es = [e for e in parseFile("runningTime.txt") if e.algorithmType != "SEQUENTIAL"]
plotRunningTimeAllInputTypes(Es, 48, False)