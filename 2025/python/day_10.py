import re
from typing import Dict
from z3 import *

def solve_buttons_z3(A, b):
    n_buttons = len(A)
    n_joltages = len(A[0])
    opt = Optimize()
    x = [Int(f"x{j}") for j in range(n_buttons)]
    for var in x:
        opt.add(var >= 0)
    for c in range(n_joltages):
        opt.add(Sum(A[bj][c] * x[bj] for bj in range(n_buttons)) == b[c])
    opt.minimize(Sum(x))
    if opt.check() == sat:
        m = opt.model()
        for j in range(n_buttons):
            print(f"x[{j}] =", m[x[j]])
        return sum(m[x[j]].as_long() for j in range(n_buttons))
    return None


def parse_line(line: str) -> Dict[str, Any]:
    line = line.strip()
    if not line:
        return None
    button_groups = re.findall(r"\((.*?)\)", line)
    b_match = re.search(r"\{(.*?)\}", line)
    B = [int(x) for x in b_match.group(1).split(",")]
    num_counters = len(B)
    A = []
    for group in button_groups:
        if group.strip() == "":
            A.append([0] * num_counters)
        else:
            idxs = [int(x) for x in group.split(",")]
            row = [1 if i in idxs else 0 for i in range(num_counters)]
            A.append(row)

    return {"A": A, "B": B}


def parse_file(path: str):
    instances = []
    with open(path, "r") as f:
        for line in f:
            if line.strip():
                inst = parse_line(line)
                if inst:
                    instances.append(inst)
    return instances

if __name__ == "__main__":
    instances = parse_file("../cpp/input.txt")
    ans = 0
    for i, inst in enumerate(instances):
        A = inst["A"]
        B = inst["B"]
        ans += solve_buttons_z3(A, B)
    print(ans)


