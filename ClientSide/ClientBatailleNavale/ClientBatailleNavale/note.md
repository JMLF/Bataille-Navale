# Client de jeu : Bataille Naval
Ce client permet de se conencter a un serveur de jeu pour affronter un autre
� la bataille navale.
## Fonctionnement
Tout le jeu se fait server side, le serveur ne fait que renvoyer les trames au second
client de jeu.
## Fonctionnement du client:
Le client se connecte au serveur, il attend de recevoir une trame (en attente du second joueur), on attend la trame pour savoir si on doit parler 
ou la trame qui dit que l'on doit parler ou la trame qui dit que l'autre joueur place ses bateaux,
on place ses bateaux puis on envoi une trame qui dit que l'on a fini d'installer les bateaux. 

## Les trames
+ En attente du joueur 2 = trame envoyer par le serveur au premier client connect� pour lui signifier qu'il attend un second joueur.
+ A vous de jouer = trame envoy� depuis le serveur a l'un au l'autre client qui 
 signifie que le serveur est pr�s a recevoir une trame du client.
+   