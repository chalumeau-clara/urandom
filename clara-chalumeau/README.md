# WLKOM project: Epirandom

--- 

## Présentation d'epirandom

---

Epirandom (```/dev/epirandom```) sort des octets aléatoires similaires à ```/dev/urandom``` si aucun alphabet n'est donné en paramètre.  
Si un alphabet est passé en argument epirandom sort des éléments de cet alphabet aléatoirement. 

## Compiler le module

---

```bash
make
```

Le module est compilé sur epidriver.ko  

Note : je n'ai pu que tester avec -std=gnu89

## Installer / Désinstaller

---

Pour installer le fichier device **sans** paramètre :

```bash
# La major number devrais s'afficher
make load

# Print la commande qu'il faut executer en remplaçant major par le nombre correspondant 
make nod
```

Pour installer le fichier device **avec** paramètre :

```bash
# Ajouter votre alphabet avec ou sans ""
# La major number devrai s'afficher
make load_param

# Print la commande qu'il faut executer en remplaçant major par le nombre correspondant 
make nod
```

Pour désinstaller le fichier object :

```bash
make unload
```

Pour effacer le répertoire : 

```bash
make clean
```

## Tips

---

Liste les modules

```bash
lsmod
```

Montre les infos du module

```bash
modinfo epidriver.ko
```

Have fun ! :)