def parse_graph(lines):
    graph = {}
    for line in lines:
        if not line.strip():
            continue

        left, right = line.split(':', 1)
        left = left.strip()
        right = right.strip()

        graph[left] = [x for x in right.split()]
    return graph


def count_paths(graph, start, goal):
    memo = {}

    def dfs(node, visited):
        if node == goal:
            return 1

        if node in memo:
            return memo[node]

        visited.add(node)
        total = 0

        for nxt in graph.get(node, []):
            if nxt not in visited:
                total += dfs(nxt, visited)

        visited.remove(node)
        memo[node] = total
        return total

    return dfs(start, set())

with open("input.txt", "r", encoding="utf-8") as f:
    graph = parse_graph(f.readlines())

    svr_fft = count_paths(graph, "svr", "fft")
    svr_dac = count_paths(graph, "svr", "dac")

    fft_out = count_paths(graph, "fft", "out")
    dac_out = count_paths(graph, "dac", "out")

    fft_dac = count_paths(graph, "fft", "dac")
    dac_fft = count_paths(graph, "dac", "fft")

    print(  svr_fft * fft_dac * dac_out +
        svr_dac * dac_fft * fft_out)
