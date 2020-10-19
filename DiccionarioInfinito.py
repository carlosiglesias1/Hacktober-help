print("Diccionario Infinito (introdicir termo a buscar en mínusculas)")
sentence = input()
total = sentence.count('q')+sentence.count('w')+sentence.count('e')+sentence.count('r')+sentence.count('t')+sentence.count('y')+sentence.count('u')+sentence.count('i')+sentence.count('o')+sentence.count('p')+sentence.count('a')+sentence.count('s')+sentence.count('d')+sentence.count('f')+sentence.count('g')+sentence.count(
    'h')+sentence.count('j')+sentence.count('k')+sentence.count('l')+sentence.count('ñ')+sentence.count('z')+sentence.count('x')+sentence.count('c')+sentence.count('v')+sentence.count('b')+sentence.count('n')+sentence.count('m')+sentence.count("á")+sentence.count("é")+sentence.count("í")+sentence.count("ó")+sentence.count("ú")
if len(sentence) == total:
    print(sentence + " está no diccionario infinito")
else:
    print(sentence + " non está no diccionario infinito")
