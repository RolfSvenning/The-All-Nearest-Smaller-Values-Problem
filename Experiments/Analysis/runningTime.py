from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np
from math import log2

AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'orange', "BERKMAN_VISHKIN": 'black'} 
AtoM = {"SEQUENTIAL": 'x', "SHUN_ZHAO": 'o', "BERKMAN_VISHKIN": '^'} 

def plotRunningTimeAllInputTypes(Es, P, logscale):
    for inputType in ["MERGE", "SHUFFLED_MERGE", "RANDOM", "SORTED"]:
        plotRunningTime(Es, inputType, P, "Running times (All algorithms, blocksize = 256 * log2(n), P = " + str(P), logscale)

def plotRunningTime(E, inputType, p, title, logScale):
    E = [e for e in E if (e.inputType == inputType and e.numberOfCores == p and e.n >= 100)] # TODO: excluding small n
    Cmap = {a:AtoC[a] for a in set([e.algorithmType for e in E]) } 
    Mmap = {a:AtoM[a] for a in set([e.algorithmType for e in E]) } 

    _, ax = plt.subplots()
    # N = np.array([e.n for e in NTs])
    # T = np.array([e.times for e in NTs])
    N = np.array([e.n for e in E])
    Tnorm = np.array([e.averageTime / (e.n)for e in E])

    # Tavg = np.array([e.averageTime for e in E])
    # Ttimes = np.array([e.times for e in E])
    # Terr = np.hstack([[max(0, (e.averageTime - e.minTimes) / e.n), max(0, (e.maxTime - e.averageTime) / e.n)] for e in E])
    C = np.array([Cmap[e.algorithmType] for e in E])

    for algorithmType, color in Cmap.items():
        ix = np.where(C == color)
        N2 = N[ix]
        Tnorm2 = Tnorm[ix]

        Nall, Tall = zip(*[(e.n, t / e.n) for e in np.array(E)[ix] for t in e.times])
        ax.scatter(Nall, Tall, c=color, s=10, marker=Mmap[algorithmType])
        
        # ax.scatter(N2, Tnorm2, c=color, label=algorithmType + " " + inputType, s=20, marker=Mmap[algorithmType])
        
        N2, Tnorm2 = zip(*[(n, t) for n, t in sorted(list(zip(N2, Tnorm2)), key=lambda x: x[0])])
        ax.plot(N2, Tnorm2, c=color, label=algorithmType + " " + inputType)



        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('n')
    ax.set_ylabel('Running time in seconds')
    ax.set_title(title)
    ax.legend()
    plt.savefig('Experiments/Analysis/runningTimePlots/' + inputType + f"_{p}.pdf", bbox_inches='tight') #"Experiments/Results/" + fileName
    plt.show()

Es = parseFile("runningTime.txt")
plotRunningTimeAllInputTypes(Es, 1, True)
plotRunningTimeAllInputTypes(Es, 48, True)

# Without sequential for P = 48
# Es = [e for e in parseFile("runningTime.txt") if e.algorithmType != "SEQUENTIAL"]
# plotRunningTimeAllInputTypes(Es, 48, True)