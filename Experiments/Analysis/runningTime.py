from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np

AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'green', "BERKMAN_VISHKIN": 'red'} 

def plotRunningTimeAllInputTypes(Es, P, logscale):
    for inputType in ["MERGE", "SHUFFLED_MERGE", "RANDOM", "SORTED"]:
        plotRunningTime(Es, inputType, P, "Running times (all inputs, all algorithms, blocksize = 8192, P = " + str(P), logscale)

def plotRunningTime(NTs_, inputType, p, title, logScale):
    # NTs = [(e.n, e.times, e.algorithmType, e.numberOfCores) for e in NTs_ if (e.inputType == inputType and e.numberOfCores == p)]
    E = [e for e in NTs_ if (e.inputType == inputType and e.numberOfCores == p and e.n >= 64)]
    Cmap = {a:AtoC[a] for a in set([e.algorithmType for e in E]) } 

    _, ax = plt.subplots()
    # N = np.array([e.n for e in NTs])
    # T = np.array([e.times for e in NTs])
    N = np.array([e.n for e in E])
    Tnorm = np.array([e.averageTime / e.n for e in E])
    Terr = np.hstack([[max(0, (e.averageTime - e.minTimes) / e.n), max(0, (e.maxTime - e.averageTime) / e.n)] for e in E])
    C = np.array([Cmap[e.algorithmType] for e in E])

    for algorithmType, color in Cmap.items():
        ix = np.where(C == color)
        N2 = N[ix]
        Tnorm2 = Tnorm[ix]
        Terr2 = Terr[ix]
        # ax.scatter(N[ix], T[ix] / N[ix], c=color, label=algorithmType + " " + inputType, s=10)
        ax.errorbar(N2, Tnorm2, Terr2, fmt='o', c=color, label=algorithmType + " " + inputType, ms=2)
        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('n')
    ax.set_ylabel('Running time in seconds')
    ax.set_title(title)
    ax.legend()
    plt.show()

Es = parseFile("runningTime.txt")
plotRunningTimeAllInputTypes(Es, 1, True)
# plotRunningTimeAllInputTypes(Es, 48, True)

# Without sequential for P = 48
# Es = [e for e in parseFile("runningTime.txt") if e.algorithmType != "SEQUENTIAL"]
# plotRunningTimeAllInputTypes(Es, 48, False)