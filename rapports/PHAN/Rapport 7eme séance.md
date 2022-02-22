Phan Damien

# Compte rendu séance 7

## Traitement des données

Le début de la séance a été consacrée à l'interprétation des données obtenues grâce au module GY-521.

### Résultats précédents

Nous avons vu, la séance dernière, que chaque direction sera représentée par un chiffre allant de 0 à 9 afin de déterminer le mouvement de poignée.

### Réinterprétation des données

Jusqu'ici nous obtenions des chiffre s'affichant dans la console via la commande `Serial.print`. 
Nous allons maintenant ajouter des booléens comme par exemple : `bool top = false` qui passe en *True* si la manette est dirigée vers le haut.

Donc si l'utilisateur dirige la manette vers le haut, cette condition va être solicitée : 
```php

if ((ypr[2] * 180 / M_PI) <= -20) {
      bottom = true;

```


## Mise en place du Bluetooth

La fin de la séance permettra la mise en place du Bluetooth et à la communication des données entre le l'écran et la manette.

De plus, suite sûrement à une mauvaise manipulation, nous avons désappareillés les deux module Bluetooth qui avaient été fourni par M.Masson, ce qui a rendu la tâche plus ardue.

### Reconnexion des deux appareils

--> Voir Rapport Edgar 

### Communication entre appareils

Donc maintenant avec nos deux appareils connectés, je n'avais plus qu'à envoyer les données obtenues sous forme de nombre afin que Edgar puisse l'interpréter et donc effectuer le mouvement.

Pour cela, on regarde si une ou plusieures valeurs sont *True* puis on envoi grâce à la commande `BlueT.write()` la position (nombre) correspondant au mouvement.

Exemple :     Mouvement diagonale droite = top & right sont True --> BlueT.write(2)

Ces données sont ensuite récupérées par la puce de liée à l'écran.

```php
//Envoi des données de position

//Diagonale sup droite
    if (top == true && right == true ) {
      BlueT.write('2');
    }

//Diagonale sup gauche
    else if (top == true && left == true ) {
      BlueT.write('0');
    }

//Diagonale inf droite
    else if (bottom == true && right == true ) {
      BlueT.write('8');
    }

//Diagonale inf gauche
    else if (bottom == true && left == true ) {
      BlueT.write('6');
    }

//Mouvement vers la droite
    else if (right == true) {
      BlueT.write('5');
    }

//Mouvement vers la gauche
    else if (left == true) {
      BlueT.write('3');
    }

//Mouvement vers le haut
    else if (top == true ) {
      BlueT.write('1');
    }

//Mouvement vers le bas
    else if (bottom == true ) {
      BlueT.write('7');
    }

//Position par défaut
    else {
      BlueT.write('4');
    }

```

### Les légers problèmes 

On a une déconnexion partielle lors des mouvements des fils de la mannette, que l'on peut régler par souder/scotcher les fils entre eux.

A partir d'un certain temps x, le programme crash et arrête de récolter des données.
Ceci a été réglé en règlant le moniteur série en 9600 baud au lieu de 38400 baud.

