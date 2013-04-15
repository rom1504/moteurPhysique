CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
FILES=main Objet Batiment ObjetMobile MoteurPhysique Conversion Bouton BoutonImage BoutonTexte Serveur Client Interface
OBJECTS=$(FILES:%=bin/%.o)
EXECUTABLE=bin/moteurPhysique
vpath %.cpp source:source/Objet:source/Bouton:source/Reseau:source/Interface

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

bin/%.o : %.cpp bin/empty
	$(CC) -c -DSFML_DYNAMIC $(CFLAGS) $< -o $@
	
bin/empty:
	mkdir -p bin
	touch bin/empty


run: $(EXECUTABLE)
	$(EXECUTABLE)

clean:
	rm -rf bin