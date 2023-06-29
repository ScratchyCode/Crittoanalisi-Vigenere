# Frequency Attack
Analisi della sicurezza del cifrario Vigenere usato come cifrario Vernam, basato sull'analisi delle frequenze.

Come si vede dagli istogrammi, il cifrario di Cesare (cioè con una chiave Vigenere tutta uguale) non fa altro che spostare le frequenze del testo in chiaro, mentre usando una chiave Vernam la distribuzione delle frequenze diventa uniforme, sinonimo di casualità.

# Crittoanalisi attraverso test del χ quadro
Si va ad analizzare il caso intermedio, cioè quello in cui la chiave Vigenere non è tutta uguale ma si usa una chiave con lettere tutte diverse;

Il primo passo è quello di determinare la lunghezza N della chiave; si provano diverse ipotesi per N, da 1 ad un valore massimo, per ogni valore il testo viene distribuito su N colonne che sono possibili testi cifrati con il cifrario di Cesare, si calcola lo scarto tra il numero di presenze osservato e quello atteso per la data lingua e si sceglie come lunghezza della chiave il valore che ha dato il chi quadro minore.


Una volta individuato il valore di N il messaggio cifrato risulta spezzato su N testi cifrati con il cifrario di Cesare, dunque ci sono solo 26 ipotesi possibili; queste ipotesi vengono analizzate una ad una e anche qui per ognuna viene calcolato il chi quadro.


Alla fine si individua l'ipotesi per la quale il chi quadro è minimo e quindi la lettera della chiave.


Questo lavoro viene ripetuto per ogni colonna e alla fine si ottiene un'ipotesi completa per la chiave; se essa è una parola o frase riconoscibile della lingua si è certi di aver forzato il messaggio.


Se il messaggio ha senso compiuto il gioco è fatto, altrimenti si prova con un altro valore di N.
