Phan Damien

# Compte rendu séance 4

## Modélisation du sabre

Décision de faire la modélisation du sabre sur le site [onshape](https://www.onshape.com/fr/professional-trial?utm_source=google&utm_medium=cpc&utm_campaign=Google_Search_EMEA&mostrecentleadsource=google-cpc--20309) afin d'obtenir un objet tenable en main et pouvant être manié facilement.

La puce Uno R3 étant trop grande pour être facilement incorporée dans le sabre, nous devons donc opter pour une plus petite qui peut tout autant garder les fonctionnalitées de base.

## Position du sabre

Donc grâce au code du site [suivant](http://gilles.thebault.free.fr/spip.php?article32) (Mesurer l’angle en combinant le gyropode et l’accéléromètre avec un "filtre complémentaire"), je peux mesurer un certain angle. 

Cependant, pour pouvoir trouver la position de notre objet que l'on va utiliser pour donner des coups, on va devoir aussi pouvoir calculer les autres angles (pitch, roll, yaw).

Pour cela, il suffit de remplacer dans : 
angle=0.98*(angle+float(gy)*0.01/131) + 0.02*atan2((double)ax,(double)az)*180/PI;

les différentes variables afin d'obtenir l'angle désiré.
