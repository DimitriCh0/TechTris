# TechTris
Projet Tech-Tris – Préing1 MI1-F


Technologie utilisée :
   -Langage C.
   -Utilisation du terminale.
   -Makefile pour la compilation du jeu.

Bienvenue sur TechTris :

![image](https://github.com/user-attachments/assets/1db7f7d0-5507-482e-941f-4968fc3da19f)

Notre projet est un jeu vidéo inspiré du jeu Tetris pouvant être affiché dans le terminal.
 
 - Installation
   Téléchargez le projet au format `.zip`.
    Extrayez les fichiers.
    Ouvrez un terminal dans le dossier extrait.
    Exécutez la commande suivante pour compiler :
   ```bash
   make 

Voici le resultat attendu :

![image](https://github.com/user-attachments/assets/f573d0f7-e3be-4be7-aecc-4181dbcba482)


- Utilisation :

Lancez une partie en entrant votre pseudo (50 caractères maximum et sans espace) et la difficulté (comprise entre 1 et 4), puis utilisez les touches Q (pour aller à gauche), S (pour descendre la pièce plus rapidement), D (pour aller à droite), E (pour tourner la pièce de 90° vers la droite), A (pour tourner la pièce de 90° vers la gauche) et Espace (pour faire descendre la pièce directement) afin de déplacer le tétromino.

![image](https://github.com/user-attachments/assets/066fe468-3a04-48f4-ae94-41eb9353066b)


La grille est de 20 par 10 pour permettre une meilleure expérience utilisateur.

Fonctionnalités : 

- L'Atelier :
Cet atelier vous permet de modifier les pièces directement dans le jeu, sans avoir à éditer manuellement les fichiers texte.
L'ensemble des règles vis-à-vis de la création des pièces sont présentés à l'accès de l'atelier (Max 5 blocs par pièces...).
La modification d’une pièce doit commencer depuis le centre, car celui-ci sert de point de référence pour sa construction.

 ![image](https://github.com/user-attachments/assets/754c8adb-9a95-4f0d-a3df-91c7c6b6c5c8)

- La fonction "Pause" :
Un menu pause a été ajouté pour permettre de sauvegarder la partie et la reprendre plus tard.
Pour cela, appuyer sur Echap en partie pour y accéder.
 
![image](https://github.com/user-attachments/assets/aba4002b-42ae-41ba-a8cb-13bafefc46c6)

- L'affichage des pièces :
Une interface permet de visualiser les pièces avec lesquelles vous allez jouer.

![image](https://github.com/user-attachments/assets/6bfce215-61d4-4d38-a7ed-7bb40d4ed81f)

- La fonction "Rejouer" :
Accessible depuis le menu principal, cette fonction permet de reprendre la dernière partie sauvegardée.

Voici ci-dessous la représentation des fichiers texte dans notre code qu'il faut respecter pour avoir un jeu fonctionnel:

- Le scoreboard : le nombre de joueurs répertorié dans le scoreboard, puis leurs données (pseudo marqué par le #, le score par & et la difficulté par /)

     ![image](https://github.com/user-attachments/assets/e269eb6a-0496-41e0-8798-72c7b600c093)

   En cas de problème, le fichier par défaut doit ressembler à cela : 

     ![image](https://github.com/user-attachments/assets/55e744eb-428f-49e3-99e0-9a65d4246cc0)

  
- Les pièces modifiées : 0 pour le vide, 1 pour les blocs, # comme séparateur ; une pièce tient dans un carré de 5*5

     ![image](https://github.com/user-attachments/assets/da1e8df5-1c9e-410f-9a2c-7f42dc43d658)

- Les pièces par défaut : 0 pour le vide, 1 pour les blocs, # comme séparateur ; une pièce tient dans un carré de 5*5

     ![image](https://github.com/user-attachments/assets/59d313e4-b1e0-403f-aaa7-8b484723b10a)

- La sauvegarde : La grille de jeu composée de valeurs entre 0 et 7, @ en séparateur, puis les données du joueur
  
     ![image](https://github.com/user-attachments/assets/48f2772b-e286-48ff-880c-689b1189be75)

**En cas de souci avec le jeu, formatez les fichiers textes "piecesmodifiees.txt" et "sauvegardes.txt"; Mettre par défaut le fichier "scoreboard.txt" (voir image).**

Erreurs :
Le programme, en cas de mauvaise lecture d'un fichier texte ou un pointeur mal initialisé par exemple, peut cesser de fonctionner et peut renvoyer une valeur exit comprise entre 10 et 79.
La dizaine de la valeur correspond au fichier lié à cette erreur.
Les indices sont les suivants :
- menu.c = 10
- piecesetrotation.c = 20
- atelier.c = 30
- scoreboard.c = 40
- tetromino.c = 50
- tetris.c = 60
- draw.c = 70
