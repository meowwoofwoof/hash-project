import os
import re

def is_code_line(line):
    line = line.strip()
    if not line:
        return False
    if line.startswith('//') or line.startswith('/*') or line.startswith('*') or line.startswith('#'):
        return False
    if re.match(r'^\s*(using\s+namespace|#include|template|typedef|extern)', line):
        return False
    return True

def collect_unique_code_lines(root_path):
    seen = set()
    count = 0
    for dirpath, dirnames, filenames in os.walk(root_path):
        if 'build' in dirpath.split(os.sep):
            continue
        if 'include' in dirpath.split(os.sep):
            continue
        if 'tests' in dirpath.split(os.sep):
            continue
        for fname in filenames:
            if fname.endswith(('.cpp', '.h')):
                with open(os.path.join(dirpath, fname), encoding='utf-8', errors='ignore') as f:
                    in_block_comment = False
                    for line in f:
                        raw = line.strip()
                        if '/*' in raw:
                            in_block_comment = True
                        if '*/' in raw:
                            in_block_comment = False
                            continue
                        if in_block_comment:
                            continue
                        if is_code_line(raw):
                            normalized = re.sub(r'\s+', ' ', raw) 
                            if normalized not in seen:
                                seen.add(normalized)
                                count += 1
    return count

if __name__ == "__main__":
    path = "." 
    total = collect_unique_code_lines(path)
    print(f"total relevant c++ code lines: {total}")