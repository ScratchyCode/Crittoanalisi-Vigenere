import matplotlib.pyplot as plt
import numpy as np
from collections import Counter

SENTENCE = input("Inserisci il testo da analizzare: ")

SENTENCE = sorted(SENTENCE)
SENTENCE = ''.join(SENTENCE) # list to string

# generate histogram
letters_hist = Counter(SENTENCE.lower().replace('\n',''))
counts = letters_hist.values()
letters = letters_hist.keys()

# graph data
bar_x_locations = np.arange(len(counts))
plt.bar(bar_x_locations, counts, align = 'center')
plt.xticks(bar_x_locations, letters)
plt.grid()
plt.show()
