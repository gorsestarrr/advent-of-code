def dfs1(graph, current, visited, path):
    if len(visited) == len(graph):
        return path
    best = float('inf')
    for neighbor, weight in graph[current]:
        if neighbor not in visited:
            best = min(best,
                       dfs1(graph, neighbor, visited | {neighbor}, path + weight)
                       )
    return best

def dfs2(graph, current, visited, path):
    if len(visited) == len(graph):
        return path
    best = 0
    for neighbor, weight in graph[current]:
        if neighbor not in visited:
            best = max(best,
                       dfs2(graph, neighbor, visited | {neighbor}, path + weight)
                       )
    return best

def part1(graph):
    answer = min(
        dfs1(graph, start, {start}, 0)
        for start in graph
    )
    return answer;

def part2(graph):
    answer = max(
        dfs2(graph, start, {start}, 0)
        for start in graph
    )
    return answer;

if __name__ == '__main__':
    with open('input.txt') as f:
        lines = f.readlines()
        graph = {}
        for line in lines:
            sp = line.split("=")
            fr, to = sp[0].split(" to ")
            dist = int(sp[1].strip())
            fr = fr.strip()
            to = to.strip()
            if fr not in graph:
                graph[fr] = []
            graph[fr].append((to, dist))
            if to not in graph:
                graph[to] = []
            graph[to].append((fr, dist))

    print(part1(graph))
    print(part2(graph))