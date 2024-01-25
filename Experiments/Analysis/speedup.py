from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np
# from matplotlib.ticker import FuncFormatter


AtoC = {"SHUN_ZHAO": 'orange', "BERKMAN_VISHKIN": 'black'} 
AtoM = {"SHUN_ZHAO": 'o', "BERKMAN_VISHKIN": '^'} 
AtoL = {"SHUN_ZHAO": "BSZ", "BERKMAN_VISHKIN": "BSV"}
AtoS = {"SHUN_ZHAO": (0, (3, 1, 1)), "BERKMAN_VISHKIN": (0, (5, 1))} 


def plotSpeedup(E, title, logScale):
    fig, ax = plt.subplots(figsize=(7,5))
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
        ax.plot(P2, Tnorm2, c=color, label=AtoL[algorithmType], linestyle=AtoS[algorithmType])

        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('Number of threads P')
    #ax.set_ylabel('T_1 / T_P') #ax.set_ylabel('$\\frac{T_1}{T_P}$')
    ax.set_ylabel('Speedup $\\frac{T_1}{T_P}$')#, fontsize = 13)
    #ax.set_title(title)
    ax.legend()
    # plt.rcParams["figure.figsize"] = (20,30)
    
   
    fig.set_size_inches(7, 5)
    plt.savefig('Experiments/Analysis/speedupPlots/speedup.pdf', bbox_inches='tight') 
    # plt.show()


Es = [e for e in parseFile("PAPER_speedup.txt") if e.algorithmType != "SEQUENTIAL"]

# P = 1
# plotSpeedup(Es, "Number of Processors vs. Average Running Time (blocksize = 256 * log2(n))", logScale=False)
plotSpeedup(Es, "Speedup\n(blocksize = 256 * log2(n))", logScale=False)

# P = 48
# plotBlocksize(Es, 12, "Block Size vs. Average Running Time (n = xxx, P = 48)", logScale=True)

def printSpeedup(E):
    E1s =  [e for e in E if e.numberOfCores == 1]
    E12s =  [e for e in E if e.numberOfCores == 12]
    E24s =  [e for e in E if e.numberOfCores == 24]
    E48s = [e for e in E if e.numberOfCores == 48]

    def speedupAlgorithm(algorithmType):
        t1 =  [e for e in E1s  if e.algorithmType == algorithmType][0].averageTime
        t12 =  [e for e in E12s  if e.algorithmType == algorithmType][0].averageTime
        t24 =  [e for e in E24s  if e.algorithmType == algorithmType][0].averageTime
        t48 = [e for e in E48s if e.algorithmType == algorithmType][0].averageTime
        print(algorithmType + f"t1: {t1} and 12: {t12} and speedup t1/t12: {t1 / t12}")
        print(algorithmType + f"t1: {t1} and t48: {t24} and speedup t1/t24: {t1 / t24}")
        print(algorithmType + f"t1: {t1} and t48: {t48} and speedup t1/t48: {t1 / t48}")
    
    speedupAlgorithm("SHUN_ZHAO")
    speedupAlgorithm("BERKMAN_VISHKIN")

printSpeedup(Es)