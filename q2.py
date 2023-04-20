from collections import defaultdict

def preprocess(data_path):
    trie = defaultdict(list)
    with open(data_path, "r") as f:
        for line in f:
            # all the other elements except the first one, are phonemes
            phonemes = line.split()[1:]
            # appending first word from dataset as word
            trie[tuple(phonemes)].append(line.split()[0])
    return trie

def find_word_combos_with_pronunciation(input_phonemes):
    # reading the dataset from file and preprocess it
    phonemes_to_word = preprocess("prons.txt")
    
    # Base case
    # If no phonemes left in the input, return
    if not input_phonemes:
        return [[]]
    
    combinations = []
    for i in range(1, len(input_phonemes) + 1):
        # Check if the set of phonemes correspond to a word in our dictionary
        if tuple(input_phonemes[:i]) in phonemes_to_word:
            # Iterate over found words: dict items
            for word in phonemes_to_word[tuple(input_phonemes[:i])]:
                # Check the rest of the phonemes in the input
                for rest in find_word_combos_with_pronunciation(input_phonemes[i:]):
                    combinations.append([word] + rest)
                    
    return combinations


# Test input
input_phonemes = ["DH", "EH", "R", "DH", "EH", "R"]
print(find_word_combos_with_pronunciation(input_phonemes))