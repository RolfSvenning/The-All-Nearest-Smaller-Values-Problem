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
    plt.xlim(B[0], B[-1])
    plt.show()


Es = parseFile("blockSize.txt")
# # P = 1
plotBlocksize(Es, 1, "Block Size vs. Average Running Time (n = xxx, P = 1)", logScale=True)
# # P = 48
# plotBlocksize(Es, 12, "Block Size vs. Average Running Time (n = xxx, P = 48)", logScale=True)


def plotBreakdownRunningTime(E, p, algorithmType, title, logScale):
    E = [e for e in E if e.numberOfCores == p and e.algorithmType == algorithmType]
    _, ax = plt.subplots()
    B = np.array([e.blockSize for e in E])

    T_tree  = np.array([e.T_tree / e.n for e in E])
    T_local = np.array([e.T_local / e.n for e in E])
    T_merging = np.array([e.T_merging / e.n for e in E])

    Ts = [T_tree, T_tree + T_local, T_tree + T_local + T_merging]

    ItoC = {0:"blue", 1:"orange", 2:"black"}
    ItoL = {0:"tree", 1:"local",  2:"global"}
    for i, T in enumerate(Ts):
        ax.plot(B, T, c=ItoC[i], label=ItoL[i]) # TODO: change line type
    
    # plt.fill_between(B, 0, Ts[0], color='blue', alpha=0.7)
    # plt.fill_between(B, Ts[0], Ts[1], color='orange', alpha=0.7)
    # plt.fill_between(B, Ts[1], Ts[2], color='black', alpha=0.7)

    plt.fill_between(B, 0, Ts[0], color='grey', alpha=0.4)
    plt.fill_between(B, Ts[0], Ts[1], color='grey', alpha=0.7)
    plt.fill_between(B, Ts[1], Ts[2], color='grey', alpha=1)

    if logScale: ax.set_xscale('log')
    ax.set_xlabel('block size')
    ax.set_ylabel('Running time in seconds')
    ax.set_title(title + " algorithmType=" + algorithmType + " P=" + str(p))
    ax.legend()
    plt.xlim(B[0], B[-1])
    plt.ylim(0)
    plt.show()

plotBreakdownRunningTime(Es, 1, "BERKMAN_VISHKIN", "breakdown... n=xxx...", logScale=True)
plotBreakdownRunningTime(Es, 1, "SHUN_ZHAO", "breakdown... n=xxx...", logScale=True)

plotBreakdownRunningTime(Es, 12, "BERKMAN_VISHKIN", "breakdown... n=xxx...", logScale=True)
plotBreakdownRunningTime(Es, 12, "SHUN_ZHAO", "breakdown... n=xxx...", logScale=True)