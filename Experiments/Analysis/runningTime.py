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

    fig, ax = plt.subplots(figsize=(7,5))
    # N = np.array([e.n for e in NTs])
    # T = np.array([e.times for e in NTs])
    N = np.array([e.n for e in E])
    Tnorm = np.array([e.averageTime / (e.n)for e in E])

    # Tavg = np.array([e.averageTime for e in E])
    # Ttimes = np.array([e.times for e in E])
    # Terr = np.hstack([[max(0, (e.averageTime - e.minTimes) / e.n), max(0, (e.maxTime - e.averageTime) / e.n)] for e in E])
    C = np.array([Cmap[e.algorithmType] for e in E])

    for algorithmType, color in Cmap.items():
        if p == 48 and algorithmType == "SEQUENTIAL": continue  
        ix = np.where(C == color)
        N2 = N[ix]
        Tnorm2 = Tnorm[ix]

        Nall, Tall = zip(*[(e.n, t / e.n) for e in np.array(E)[ix] for t in e.times])
        ax.scatter(Nall, Tall, c=color, s=10, marker=Mmap[algorithmType])
        
        # ax.scatter(N2, Tnorm2, c=color, label=algorithmType + " " + inputType, s=20, marker=Mmap[algorithmType])
        
        N2, Tnorm2 = zip(*[(n, t) for n, t in sorted(list(zip(N2, Tnorm2)), key=lambda x: x[0])])
        ax.plot(N2, Tnorm2, c=color, label=algorithmType + " " + inputType)



        
    if logScale: ax.set_xscale('log')
    ax.set_xlabel('Input size $n$ (log scale)')
    ax.set_ylabel('Running time in seconds divided by $n$')
    # ax.set_title(title)
    ax.legend()
    fig.set_size_inches(7, 5)
    plt.savefig('Experiments/Analysis/runningTimePlots/' + inputType + f"_{p}.pdf", bbox_inches='tight') #"Experiments/Results/" + fileName
    # plt.show()


def getLastRunningTimes(E):
    s = ""
    nMax = max(e.n for e in E)
    # print("nMax: ", nMax)
    for p in [1, 48]:
        for inputType in ["MERGE", "SHUFFLED_MERGE", "RANDOM", "SORTED"]:
            for algorithmType in ["SEQUENTIAL", "SHUN_ZHAO", "BERKMAN_VISHKIN"]:
                Es = [e for e in E if (e.inputType == inputType and e.algorithmType == algorithmType and e.numberOfCores == p and e.n == nMax)] 
                assert(len(Es) == 1)
                e1 = Es[0]
                s += " ".join([inputType, algorithmType, str(p), str(e1.averageTime)]) + "\n"
    return s


def generate_latex_table(input_data):
    latex_code = """

\\sisetup{round-mode=places, round-precision=2}

\\begin{table}
    \\centering
    \\begin{tabular}{l|S|S|S|S|S|S}
        \\multicolumn{1}{c}{} & \\multicolumn{3}{c}{P=1} & \\multicolumn{3}{c}{P=48} \\\\
        \\hline
         & {SEC} & {BSZ} & {BSV} & {SEC} & {BSZ} & {BSV} \\\\
        \\hline
"""
    def stringOfInputType(s):
        match inputType:
                        case "SORTED": return "Sorted"
                        case "RANDOM": return "Random"
                        case "MERGE": return "Merge"
                        case "SHUFFLED_MERGE": return "RandomMerge"
             
    for inputType in ["SORTED", "RANDOM", "MERGE", "SHUFFLED_MERGE"]:
        
        latex_code += stringOfInputType(inputType) + " & "
        for p in [1, 48]:
            S_Z_B_times = [-1, -1, -1]
            for line in input_data.split('\n'):
                if line.strip() == '' or line.split()[0] != inputType or line.split()[2] != str(p): continue
                parts = line.split()
                algorithm = parts[1]
                time_value = round(float(parts[3]), 4)
                match algorithm:
                    case "SEQUENTIAL": S_Z_B_times[0] = time_value
                    case "SHUN_ZHAO": S_Z_B_times[1] = time_value
                    case "BERKMAN_VISHKIN": S_Z_B_times[2] = time_value
                    case _: assert(0 == 1)
            latex_code += " & ".join([str(t) for t in S_Z_B_times]) + (" & " if p == 1 else "")
        latex_code += " \\\\ "


    latex_code += """
    \\end{tabular}
    \\caption{Running times in seconds for different algorithms and input types with $n=2^{27}$ and block size $k=256\log{n}$.}
    \\label{tab:execution_times}
\\end{table}

"""
    # print(latex_code)
    return latex_code


Es = parseFile("PAPER_runningTime.txt")
data = getLastRunningTimes(Es)
latexCode = generate_latex_table(data)
print(latexCode)
plotRunningTimeAllInputTypes(Es, 1, True)
plotRunningTimeAllInputTypes(Es, 48, True)

# Without sequential for P = 48
# Es = [e for e in parseFile("runningTime.txt") if e.algorithmType != "SEQUENTIAL"]
# plotRunningTimeAllInputTypes(Es, 48, True)