CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
FILES=main Objet Batiment ObjetMobile Unite MoteurPhysique Bouton BoutonImage BoutonTexte Serveur Client Interface EtreVivant Animal Plante
OBJECTS=$(FILES:%=bin/%.o)
EXECUTABLE=bin/moteurPhysique
vpath %.cpp source:source/Objet:source/Bouton:source/Reseau:source/Interface:source/EtreVivant
vpath %.h source:source/Objet:source/Bouton:source/Reseau:source/Interface:source/EtreVivant

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) Makefile
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

# à améliorer...
bin/%.o : %.cpp bin/empty Makefile
	$(CC) -c -DSFML_DYNAMIC $(CFLAGS) $< -o $@
	
bin/empty:
	mkdir -p bin
	touch bin/empty

#gcc -MM
Bouton.o: source/Bouton/Bouton.cpp source/Bouton/Bouton.h
BoutonImage.o: source/Bouton/BoutonImage.cpp source/Bouton/BoutonImage.h \
 source/Bouton/Bouton.h source/Bouton/../Conversion.h
BoutonTexte.o: source/Bouton/BoutonTexte.cpp source/Bouton/BoutonTexte.h \
 source/Bouton/Bouton.h
Conversion.o: source/Conversion.cpp source/Conversion.h
Animal.o: source/EtreVivant/Animal.cpp source/EtreVivant/Animal.h \
 source/EtreVivant/EtreVivant.h source/EtreVivant/../Objet/Objet.h \
 source/EtreVivant/../Objet/../Conversion.h \
 source/EtreVivant/../Objet/ObjetMobile.h \
 source/EtreVivant/../Objet/Objet.h
EtreVivant.o: source/EtreVivant/EtreVivant.cpp \
 source/EtreVivant/EtreVivant.h source/EtreVivant/../Objet/Objet.h \
 source/EtreVivant/../Objet/../Conversion.h
Plante.o: source/EtreVivant/Plante.cpp source/EtreVivant/Plante.h \
 source/EtreVivant/EtreVivant.h source/EtreVivant/../Objet/Objet.h \
 source/EtreVivant/../Objet/../Conversion.h
Gestionnaire.o: source/Gestionnaire/Gestionnaire.cpp \
 source/Gestionnaire/Gestionnaire.h
Interface.o: source/Interface/Interface.cpp source/Interface/Interface.h \
 source/Interface/../Bouton/BoutonImage.h \
 source/Interface/../Bouton/Bouton.h \
 source/Interface/../Bouton/../Conversion.h \
 source/Interface/../Bouton/BoutonTexte.h \
 source/Interface/../Objet/Objet.h \
 source/Interface/../Objet/../Conversion.h \
 source/Interface/../Objet/ObjetMobile.h \
 source/Interface/../Objet/Objet.h
main.o: source/main.cpp source/MoteurPhysique.h source/Objet/Unite.h \
 source/Objet/ObjetMobile.h source/Objet/Objet.h \
 source/Objet/../Conversion.h source/Objet/Batiment.h \
 source/Objet/Unite.h source/Objet/Batiment.h source/Bouton/BoutonTexte.h \
 source/Bouton/Bouton.h source/Bouton/BoutonImage.h \
 source/Bouton/../Conversion.h source/Interface/Interface.h \
 source/Interface/../Bouton/BoutonImage.h \
 source/Interface/../Bouton/BoutonTexte.h \
 source/Interface/../Objet/Objet.h \
 source/Interface/../Objet/ObjetMobile.h source/EtreVivant/Animal.h \
 source/EtreVivant/EtreVivant.h source/EtreVivant/../Objet/Objet.h \
 source/EtreVivant/../Objet/ObjetMobile.h source/EtreVivant/Plante.h \
 source/Reseau/Serveur.h source/Reseau/Client.h \
 source/Reseau/../Objet/Objet.h source/Reseau/../Objet/ObjetMobile.h \
 source/Reseau/../Objet/Batiment.h
MoteurPhysique.o: source/MoteurPhysique.cpp source/MoteurPhysique.h \
 source/Objet/Unite.h source/Objet/ObjetMobile.h source/Objet/Objet.h \
 source/Objet/../Conversion.h source/Objet/Batiment.h \
 source/Objet/Unite.h source/Objet/Batiment.h source/Bouton/BoutonTexte.h \
 source/Bouton/Bouton.h source/Bouton/BoutonImage.h \
 source/Bouton/../Conversion.h source/Interface/Interface.h \
 source/Interface/../Bouton/BoutonImage.h \
 source/Interface/../Bouton/BoutonTexte.h \
 source/Interface/../Objet/Objet.h \
 source/Interface/../Objet/ObjetMobile.h source/EtreVivant/Animal.h \
 source/EtreVivant/EtreVivant.h source/EtreVivant/../Objet/Objet.h \
 source/EtreVivant/../Objet/ObjetMobile.h source/EtreVivant/Plante.h \
 source/Reseau/Serveur.h source/Reseau/Client.h \
 source/Reseau/../Objet/Objet.h source/Reseau/../Objet/ObjetMobile.h \
 source/Reseau/../Objet/Batiment.h
Batiment.o: source/Objet/Batiment.cpp source/Objet/Batiment.h \
 source/Objet/Objet.h source/Objet/../Conversion.h source/Objet/Unite.h \
 source/Objet/ObjetMobile.h
Objet.o: source/Objet/Objet.cpp source/Objet/Objet.h \
 source/Objet/../Conversion.h
ObjetMobile.o: source/Objet/ObjetMobile.cpp source/Objet/ObjetMobile.h \
 source/Objet/Objet.h source/Objet/../Conversion.h
Objets.o: source/Objet/Objets.cpp source/Objet/Objets.h \
 source/Objet/Objet.h source/Objet/../Conversion.h \
 source/Objet/ObjetMobile.h source/Objet/Batiment.h source/Objet/Unite.h
Unite.o: source/Objet/Unite.cpp source/Objet/Unite.h \
 source/Objet/ObjetMobile.h source/Objet/Objet.h \
 source/Objet/../Conversion.h source/Objet/Batiment.h
Client.o: source/Reseau/Client.cpp source/Reseau/Client.h \
 source/Reseau/../Objet/Objet.h source/Reseau/../Objet/../Conversion.h \
 source/Reseau/../Objet/ObjetMobile.h source/Reseau/../Objet/Objet.h \
 source/Reseau/../Objet/Batiment.h source/Reseau/../Objet/Unite.h \
 source/Reseau/../Objet/ObjetMobile.h source/Reseau/../Objet/Batiment.h
Serveur.o: source/Reseau/Serveur.cpp source/Reseau/Serveur.h


run: $(EXECUTABLE)
	$(EXECUTABLE)

clean:
	rm -rf bin
