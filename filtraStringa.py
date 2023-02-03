import unidecode

def remove_spaces_and_lowercase(s):
    s = s.replace(" ", "") # rimuove gli spazi
    s = ''.join(filter(str.isalpha, s)) # rimuove i numeri e i caratteri speciali
    s = unidecode.unidecode(s) # rimuovi i char accentati
    s = s.upper() # converte in maiuscolo
    return s

input_string = input("Inserisci la stringa: ")
output_string = remove_spaces_and_lowercase(input_string)
print(output_string)
