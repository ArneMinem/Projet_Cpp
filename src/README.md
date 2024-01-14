## Projet_Cpp

# Exécuter le code :
Copiez puis décompressez le zipfile à l'endroit voulu
Allez dans votre terminal puis :
1. Entrez "cd Nom_du_dossier"
2. Entrez "./build.sh
3. Si "bash: ./build.sh: Permission denied", entrez d'abord "chmod +x build.sh"
4. Entrez "/build/create_raster "Chemin_vers_file.txt_a_représenter" nombre_de_pixel"

Attention : dans le main nous avons à la ligne 33 :
    fileName = "../" + fileName;
J'ai du remplacer par "/home/arne/Projet_Cpp/" + fileName puisqu'autrement j'avais "segmentation error" pour une raison que j'ignore.
Donc si cela vous arrive changez le par le chemin d'accès vers l'endroit où vous avez mis les données .

# La documentation :

Dans votre terminal rentrez "doxygen Doxyfile"
Cela créera les dossiers html et latex dans le dossier doc

Pour voir la documentation en ligne cherchez doc/html/index.html

Pour l'avoir au format pdf il faut encore éxecuter : 
1. "cd doc/latex/"
2. "pdflatex refman.tex"
Ainsi vous pouvez trouver refman.pdf sous doc/latex/