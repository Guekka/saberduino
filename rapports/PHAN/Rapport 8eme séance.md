Phan Damien

# Compte rendu séance 8

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