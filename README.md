miniCASys
=========

Minicas, projet d'ALinéA (Algèbre Linéaire), L2S4, Université de Strasbourg. Mini interpréteur de commandes correspondant à des opérations classiques d'algèbre linéaire.

Télécharger et compiler « Chasseur de Prim »
--------------------------------------------
### Pré-requis ###
Tout d'abord, il vous faudra les outils standards de développement GNU, ainsi que git. Ce programme tire également parti de ```gnuplot```.

Pour Ubuntu :
````bash
$ apt-get install build-essentials git-core gnuplot
````

Pour Fedora :
````bash
$ yum groupinstall "Development Tools"
$ yum install git-all gnuplot
````

### Récupérer le projet ###
Pour récupérer le projet dans le dossier de votre choix :
````bash
$ git clone git://github.com/remove/miniCASys.git [dossier]
````
Ensuite, pour récupérer les changements :
````bash
$ git pull
````

### Compiler ###
Un makefile est fourni, il vous suffit de vous placer à la racine du projet et de lancer make :
````bash
$ make
````

Lancer Minicas
-----------------------
### Mode interactif ###
Une fois le programme compilé, il suffit de lancer le binaire disponible dans ```bin``` :
````bash
$ ledit bin/minicas
````
```ledit``` est optionnel, ce programme permet d'obtenir un prompt plus agréable (historique, complétion des noms de fichiers, ...). Pour obtenir de l'aide, entrez la commande ```aide```. Pour quitter le programme, entrez la commande ```quitter``` ou ```q```, puis confirmez votre décision par ```oui```.

### Mode non interactif ###
Il est possible de lancer des scripts :
````bash
$ bin/minicas <fichier>
````
Ceux-ci doivent contenir une commande par ligne. Les commandes valides sont toutes celles qui sont disponibles dans le mode interactif.

### Version ###
Pour connaître la version de ```minicas``` que vous utilisez :
````bash
$ bin/minicas --version
````

Branches
--------
Les versions stables se trouvent dans la branche ````master````, la branche ````dev```` contient la version de développement du projet. Pour passer d'une branche à l'autre :
````bash
$ git checkout <branche>
````

License
-------
Copyright © 2013 Harenome RAZANAJATO, Jérémy MEYER

Ce projet est libre. Vous pouvez le redistribuer ou le modifier selon les termes de la license « Do What The Fuck You Want To Public License », Version 2, comme publiée par Sam Hocevar. Pour de plus amples informations, veuillez vous référer au fichier COPYING, ou bien http://www.wtfpl.net/.
