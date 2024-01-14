from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np


AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'orange', "BERKMAN_VISHKIN": 'black'} 
AtoM = {"SEQUENTIAL": 'x', "SHUN_ZHAO": 'o', "BERKMAN_VISHKIN": '^'} 


def plotBlocksize(E, p, title, logScale):
    E = [e for e in E if e.numberOfCores == p]
    _, ax = plt.subplots()
    B = np.array([e.blockSize for e in E])
    Tnorm = np.array([e.averageTime / e.n for e in E])

    C = np.array([AtoC[e.algorithmType] for e in E])

    for algorithmType, color in AtoC.items():
        ix = np.where(C == color)
        N2 = B[ix]
        Tnorm2 = Tnorm[ix]

        Nall, Tall = zip(*[(e.blockSize, t / e.n) for e in np.array(E)[ix] for t in e.times])
        ax.scatter(Nall, Tall, c=color, s=10, marker=AtoM[algorithmType])
                
        N2, Tnorm2 = zip(*[(n, t) for n, t in sorted(list(zip(N2, Tnorm2)), key=lambda x: x[0])])
        ax.plot(N2, Tnorm2, c=color, label=algorithmType + " " + algorithmType)

        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('block size')
    ax.set_ylabel('Running time in seconds')
    ax.set_title(title)
    ax.legend()
    plt.show()


Es = parseFile("blockSize.txt")

# P = 1
plotBlocksize(Es, 1, "Block Size vs. Average Running Time (n = xxx, P = 1)", logScale=True)

# P = 48
plotBlocksize(Es, 48, "Block Size vs. Average Running Time (n = xxx, P = 48)", logScale=True)