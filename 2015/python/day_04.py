import hashlib

def solve(s, search_for):
    for i in range(10**9):
        full = s + str(i)
        val = hashlib.md5(full.encode()).hexdigest()
        if val.startswith(search_for):
            return i
    return None

if __name__ == '__main__':
    print(solve("bgvyzdsv", "00000"))
    print(solve("bgvyzdsv", "000000"))