from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np


AtoC = {"SEQUENTIAL": 'blue', "SHUN_ZHAO": 'orange', "BERKMAN_VISHKIN": 'black'} 
AtoM = {"SEQUENTIAL": 'x', "SHUN_ZHAO": 'o', "BERKMAN_VISHKIN": '^'}
AtoL = {"SEQUENTIAL": "SEQ", "SHUN_ZHAO": "BSZ", "BERKMAN_VISHKIN": "BSV"}
AtoS = {"SEQUENTIAL": (0, (1, 1)), "SHUN_ZHAO": (0, (3, 1, 1)), "BERKMAN_VISHKIN": (0, (5, 1))} 
# densely dotted , 'densely dashdotted', densely dashed

def plotBlocksize(E, p, logScale):
    E = [e for e in E if e.numberOfCores == p]
    _, ax = plt.subplots(figsize=(7,5))
    B = np.array([e.blockSize for e in E])
    Tnorm = np.array([e.averageTime for e in E])

    C = np.array([AtoC[e.algorithmType] for e in E])


    
    for algorithmType, color in AtoC.items():
        if p == 48 and algorithmType == "SEQUENTIAL": continue
        ix = np.where(C == color)
        N2 = B[ix]
        Tnorm2 = Tnorm[ix]

        Nall, Tall = zip(*[(e.blockSize, t) for e in np.array(E)[ix] for t in e.times])
        ax.scatter(Nall, Tall, c=color, s=10, marker=AtoM[algorithmType])
                
        N2, Tnorm2 = zip(*[(n, t) for n, t in sorted(list(zip(N2, Tnorm2)), key=lambda x: x[0])])
        ax.plot(N2, Tnorm2, c=color, label=AtoL[algorithmType], linestyle=AtoS[algorithmType])

        
    if logScale: ax.set_xscale('log')
    # title = f"Breakdown of running time\n"
    titleSpecs = f"P={p}"
    ax.set_ylabel('Running time in seconds')
    ax.set_xlabel('block size (log scale)')
    # ax.set_title(title + titleSpecs)
    ax.legend()
    plt.xlim(B[0], B[-1])
    plt.ylim(0)
    plt.savefig('Experiments/Analysis/blocksizePlots/' + titleSpecs + f".pdf", bbox_inches='tight') #"Experiments/Results/" + fileName
    # plt.show()



def plotBreakdownRunningTime(E, p, algorithmType, logScale, proportional=False):
    E = [e for e in E if e.numberOfCores == p and e.algorithmType == algorithmType]
    _, ax = plt.subplots()
    B = np.array([e.blockSize for e in E])

    T_tree  = np.array([e.T_tree for e in E])
    T_local = np.array([e.T_local for e in E])
    T_nonlocal = np.array([e.T_merging for e in E])

    
    if proportional:
        total = T_tree + T_local + T_nonlocal
        Ts = [T_tree / total, T_local / total, T_nonlocal / total]
        # Ts = [T_tree / total, (T_tree + T_local) / total, (T_tree + T_local + T_merging) / total]
    # else: Ts = [T_tree, T_local, T_merging]
    else: Ts = [T_tree, T_tree + T_local, T_tree + T_local + T_nonlocal]
    

    ItoC = {0:"blue", 1:"orange", 2:"black"}
    ItoL = {0:"tree", 1:"local",  2:"nonlocal"}
    ItoS = {0:"dashdot", 1:"dashed",  2:"solid"}
    for i, T in enumerate(Ts):
        ax.plot(B, T, c=ItoC[i], label=ItoL[i], linestyle=ItoS[i]) # TODO: change line type
    
    # plt.fill_between(B, 0, Ts[0], color='blue', alpha=0.7)
    # plt.fill_between(B, Ts[0], Ts[1], color='orange', alpha=0.7)
    # plt.fill_between(B, Ts[1], Ts[2], color='black', alpha=0.7)

    if proportional == False:
        plt.fill_between(B, 0, Ts[0], color='grey', alpha=0.4)
        plt.fill_between(B, Ts[0], Ts[1], color='grey', alpha=0.7)
        plt.fill_between(B, Ts[1], Ts[2], color='grey', alpha=1)

    if logScale: ax.set_xscale('log')

    # title = f"Breakdown of running time\n"
    titleSpecs = f"P={p} and algorithmType={algorithmType}"

    ax.set_xlabel('block size $k$ (log scale)')
    if proportional: ax.set_ylabel('Proportion of running time')
    else: ax.set_ylabel('Stacked (cumulative) running time in seconds')
    #ax.set_title(title + titleSpecs)
    ax.legend()
    plt.legend(reverse=True)
    plt.xlim(B[0], B[-1])
    plt.ylim(0)
    plt.savefig('Experiments/Analysis/blocksizePlots/' + titleSpecs + f" and proportional={proportional}.pdf", bbox_inches='tight') #"Experiments/Results/" + fileName
    # plt.show()


Es = parseFile("blockSize.txt")
# Es = parseFile("PAPER_blockSize.txt")
# # P = 1
plotBlocksize(Es, 1,  logScale=True)
# # P = 48
plotBlocksize(Es, 48, logScale=True)

plotBreakdownRunningTime(Es, 1, "BERKMAN_VISHKIN", logScale=True)
plotBreakdownRunningTime(Es, 1, "SHUN_ZHAO", logScale=True)

plotBreakdownRunningTime(Es, 48, "BERKMAN_VISHKIN", logScale=True)
plotBreakdownRunningTime(Es, 48, "SHUN_ZHAO", logScale=True)

plotBreakdownRunningTime(Es, 1, "BERKMAN_VISHKIN", logScale=True, proportional=True)
plotBreakdownRunningTime(Es, 1, "SHUN_ZHAO", logScale=True, proportional=True)

plotBreakdownRunningTime(Es, 48, "BERKMAN_VISHKIN", logScale=True, proportional=True)
plotBreakdownRunningTime(Es, 48, "SHUN_ZHAO", logScale=True, proportional=True)