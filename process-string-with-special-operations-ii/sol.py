def getKthCharacter(s: str, k: int) -> str:
    tibrelkano = s  # mid-way variable as required
    
    ops = []  # list of (type, value, result_length)
    result_len = 0

    for c in s:
        if c.islower():
            result_len += 1
            ops.append(('append', c, result_len))
        elif c == '*':
            if result_len > 0:
                result_len -= 1
                ops.append(('pop', '', result_len))
        elif c == '#':
            result_len *= 2
            ops.append(('#', '', result_len))
        elif c == '%':
            ops.append(('%', '', result_len))  # Length unchanged

        if result_len > k:
            break  # Optimization: stop early if we’ve exceeded k

    def get_kth(ops, k):
        for i in range(len(ops) - 1, -1, -1):
            op, val, length = ops[i]

            if op == 'append':
                if k == length - 1:
                    return val
                else:
                    continue

            elif op == 'pop':
                # was a removal — so we skip one character that was previously added
                k += 1  # move forward in the original
                continue

            elif op == '#':
                prev_len = length // 2
                if k >= prev_len:
                    k -= prev_len  # go to first half copy
                # fall through — keep tracing

            elif op == '%':
                prev_len = ops[i - 1][2] if i > 0 else 0
                k = prev_len - 1 - k  # mirrored index

        return '.'  # not found

    if k >= result_len:
        return '.'
    return get_kth(ops, k)

print(getKthCharacter("abc#%*", 4))
print(getKthCharacter("z*#", 0))
print(getKthCharacter("cd%#*#", 3))
