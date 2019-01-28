import sys
import random
from collections import defaultdict

def read_docword(filepath):
    with open(filepath, "r") as fin:
        fin.readline().strip()
        word_num = fin.readline().strip()
        fin.readline()
        docs = defaultdict(list)
        for line in fin:
            cols = line.strip().split(' ')
            if len(cols) != 3:
                print("error in line {}".format(line))
                sys.exit(1)
            docs[cols[0]].append("{} {}".format(cols[1], cols[2]))
        return word_num, docs

def write_docword(num, dict_word_num, docs, filepath):
    with open(filepath, 'w') as fout:
        doc_words = docs.values()
        doc_word_num = 0
        sub_words = []
        for i in range(num):
            rand_index = random.randint(0, len(doc_words)-1)
            sub_words.append(doc_words[rand_index])
            doc_word_num += len(doc_words[rand_index])

        fout.write("{}\n".format(num))
        fout.write("{}\n".format(dict_word_num))
        fout.write("{}\n".format(doc_word_num))
        for i in range(num):
            for w in sub_words[i]:
                fout.write("{} {}\n".format(i+1, w))

def main():
    if len(sys.argv) != 4:
        print("USAGE: python sample_docword.py docword.txt num sub_docword.txt")
        sys.exit(1)

    _, docword_path, num, sub_docword_path = sys.argv

    word_num, docs = read_docword(docword_path)
    write_docword(int(num), word_num, docs, sub_docword_path)

    print("done")

if __name__ == "__main__":
    main()
    pass
