from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np


AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'orange', "BERKMAN_VISHKIN": 'black'} 
AtoM = {"SEQUENTIAL": 'x', "SHUN_ZHAO": 'o', "BERKMAN_VISHKIN": '^'} 


def plotSpeedup(E, title, logScale):
    _, ax = plt.subplots()
    P = np.array([e.numberOfCores for e in E])

    assert E[0].numberOfCores == 1
    T1 = E[0].averageTime

    Tnorm = np.array([T1 / e.averageTime for e in E])
    # else: Tnorm = np.array([e.averageTime / e.n for e in E])

    C = np.array([AtoC[e.algorithmType] for e in E])

    for algorithmType, color in AtoC.items():
        ix = np.where(C == color)
        P2 = P[ix]
        Tnorm2 = Tnorm[ix]

        Pall, Tall = zip(*[(e.numberOfCores, T1 / t) for e in np.array(E)[ix] for t in e.times])
        # else: Pall, Tall = zip(*[(e.numberOfCores, t / e.n) for e in np.array(E)[ix] for t in e.times])
        
        ax.scatter(Pall, Tall, c=color, s=10, marker=AtoM[algorithmType])
                
        P2, Tnorm2 = zip(*[(n, t) for n, t in sorted(list(zip(P2, Tnorm2)), key=lambda x: x[0])])
        ax.plot(P2, Tnorm2, c=color, label=algorithmType)

        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('P')
    ax.set_ylabel('T_1 / T_P')
    ax.set_title(title)
    ax.legend()
    plt.savefig('Experiments/Analysis/speedupPlots/speedup.pdf', bbox_inches='tight') 
    plt.show()


Es = parseFile("speedup.txt")

# P = 1
# plotSpeedup(Es, "Number of Processors vs. Average Running Time (blocksize = 256 * log2(n))", logScale=False)
plotSpeedup(Es, "Speedup\n(blocksize = 256 * log2(n))", logScale=False)

# P = 48
# plotBlocksize(Es, 12, "Block Size vs. Average Running Time (n = xxx, P = 48)", logScale=True)